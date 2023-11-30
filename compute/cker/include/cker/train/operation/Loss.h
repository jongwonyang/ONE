/*
 * Copyright (c) 2023 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __NNFW_CKER_TRAIN_OPERATION_LOSS_H__
#define __NNFW_CKER_TRAIN_OPERATION_LOSS_H__

#include <numeric>

#include "cker/Shape.h"
#include "cker/eigen/Utils.h"

namespace nnfw
{
namespace cker
{
namespace train
{

template <typename T> inline T square(T value) { return value * value; }

template <typename T>
inline void MSE(const Shape &y_pred_shape, const T *y_pred_data, const Shape &y_true_shape,
                const T *y_true_data, const Shape &output_shape, T *output_data)
{
  if (output_shape.DimensionsCount() != 1)
    throw std::runtime_error("cker::MSE: output dimension count should be 1");
  if (output_shape.Dims(0) != y_pred_shape.Dims(0))
    throw std::runtime_error("cker::MSE: output and y_pred do not have the same batch");
  if (y_pred_shape != y_true_shape)
    throw std::runtime_error("cker::MSE: y_pred_shape != y_true_shape");

  const auto batch = y_pred_shape.Dims(0);
  const auto size = FlatSizeSkipDim(y_pred_shape, 0);

  for (int b = 0; b < batch; ++b)
  {
    float sum = 0.f;
    for (int i = 0; i < size; ++i)
    {
      sum += square(y_pred_data[b * size + i] - y_true_data[b * size + i]);
    }
    output_data[b] = static_cast<T>(sum / size);
  }
}

template <typename T>
inline void MSEGrad(const Shape &y_pred_shape, const T *y_pred_data, const Shape &y_true_shape,
                    const T *y_true_data, const Shape &grad_shape, T *grad_data)
{
  if (y_pred_shape != y_true_shape)
    throw std::runtime_error("cker::MSEGrad: y_pred_shape != y_true_shape");
  if (y_pred_shape != grad_shape)
    throw std::runtime_error("cker::MSEGrad: y_pred_shape != grad_shape");

  const int size = grad_shape.FlatSize();
  for (int i = 0; i < size; ++i)
  {
    grad_data[i] = static_cast<T>(-2 * (y_true_data[i] - y_pred_data[i]) / size);
  }
}

template <typename T> bool checkValue(const T *data, int size, T min, T max)
{
  for (int i = 0; i < size; ++i)
  {
    if (data[i] > max || data[i] < min)
      return false;
  }
  return true;
}

template <typename T>
inline void CategoricalCrossEntropy(const T *y_pred_data, const T *y_true_data, T *output_data,
                                    const int batch_size, const int input_size)
{
  const T *y_prob_data = y_pred_data;

  if (!checkValue(y_pred_data, input_size * batch_size, static_cast<T>(0), static_cast<T>(1)))
  {
    throw std::runtime_error("cker::CategoricalCrossEntropy: y_pred data is not logit data.");
  }

  std::vector<T> sum(batch_size, 0.f);
  for (int b = 0; b < batch_size; ++b)
  {
    int b_offset = b * input_size;
    for (int i = 0; i < input_size; ++i)
    {
      if (y_true_data[b_offset + i] != 0)
      {
        sum[b] += -std::log(std::max(y_prob_data[b_offset + i], static_cast<float>(1.0e-20))) *
                  y_true_data[b_offset + i];
      }
    }
  }

  output_data[0] = std::accumulate(sum.begin(), sum.end(), 0.f) / static_cast<float>(batch_size);
}

template <typename T>
inline void CategoricalCrossEntropyGrad(const T *y_pred_data, const T *y_true_data, T *grad_data,
                                        const int batch_size, const int input_size)
{
  if (!checkValue(y_pred_data, input_size * batch_size, static_cast<T>(0), static_cast<T>(1)))
  {
    throw std::runtime_error("cker::CategoricalCrossEntropyGrad: y_pred data is not logit data.");
  }

  for (int b = 0; b < batch_size; ++b)
  {
    int b_offset = b * input_size;
    for (int i = 0; i < input_size; ++i)
    {
      grad_data[b_offset + i] = -(y_true_data[b_offset + i] /
                                  std::max(y_pred_data[b_offset + i], static_cast<float>(1e-20)));
    }
  }
}

} // namespace train
} // namespace cker
} // namespace nnfw

#endif // __NNFW_CKER_TRAIN_OPERATION_LOSS_H__
