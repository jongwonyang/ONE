/*
 * Copyright (c) 2024 Samsung Electronics Co., Ltd. All Rights Reserved
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

#ifndef __NNFW_CKER_TRAIN_OPERATION_BINARYARITHMETIC_H__
#define __NNFW_CKER_TRAIN_OPERATION_BINARYARITHMETIC_H__

#include "cker/Shape.h"
#include "cker/eigen/Utils.h"
#include "cker/operation/BroadcastTo.h"

namespace nnfw
{
namespace cker
{
namespace train
{
enum class ArithmeticType
{
  kAdd,
  kSub,
  kMul,
  kDiv,
};

template <typename T>
void BinaryArithmeticGrad(const Shape &incoming_shape, const T *incoming_data,
                          const Shape &lhs_grad_shape, T *lhs_grad_data,
                          const Shape &rhs_grad_shape, T *rhs_grad_data,
                          ArithmeticType arithmetic_type)
{
  switch (arithmetic_type)
  {
    case ArithmeticType::kAdd:
    {
      BroadcastTo(incoming_shape, const_cast<T *>(incoming_data), lhs_grad_shape, lhs_grad_data);
      BroadcastTo(incoming_shape, const_cast<T *>(incoming_data), rhs_grad_shape, rhs_grad_data);
    }
    break;

    case ArithmeticType::kSub:
    case ArithmeticType::kMul:
    case ArithmeticType::kDiv:
    default:
      throw std::runtime_error{"Unsupported Binary Arithmetic Operation"};
  }
}

} // namespace train
} // namespace cker
} // namespace nnfw

#endif // __NNFW_CKER_TRAIN_OPERATION_BINARYARITHMETIC_H__
