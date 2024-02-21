/*
 * Copyright (c) 2024 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ONERT_MICRO_TEST_MODELS_CONCATENATION_KERNEL_FLOAT_H
#define ONERT_MICRO_TEST_MODELS_CONCATENATION_KERNEL_FLOAT_H

#include "TestDataConcatenationBase.h"

namespace onert_micro
{
namespace test_model
{
namespace concatenation_float
{

/*
 * Concatenation Kernel:
 *
 * Input_1(1, 4, 4, 1)   Input_2(1, 4, 4, 2)
 *       \             /
 *         Concatenation
 *              |
 *       Output(1, 4, 4, 3)
 */
const unsigned char test_kernel_model_circle[] = {
  0x18, 0x00, 0x00, 0x00, 0x43, 0x49, 0x52, 0x30, 0x00, 0x00, 0x0e, 0x00, 0x14, 0x00, 0x00, 0x00,
  0x0c, 0x00, 0x08, 0x00, 0x10, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x34, 0x00, 0x00, 0x00, 0x78, 0x01, 0x00, 0x00, 0x94, 0x01, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x20, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0xf4, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0x04, 0x00, 0x04, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00,
  0x18, 0x00, 0x14, 0x00, 0x10, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00,
  0x14, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x6c, 0x00, 0x00, 0x00,
  0x74, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x16, 0x00, 0x00, 0x00,
  0x10, 0x00, 0x0c, 0x00, 0x07, 0x00, 0x08, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a,
  0x14, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00,
  0x08, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x74, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0xa4, 0xff, 0xff, 0xff, 0x0c, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x0c, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x6f, 0x66, 0x6d, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0xd0, 0xff, 0xff, 0xff, 0x0c, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x69, 0x66, 0x6d, 0x32, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x0c, 0x00, 0x10, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x08, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00,
  0x0c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x69, 0x66, 0x6d, 0x31, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x10, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
  0x0c, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, 0x00, 0x00, 0x00,
  0x4f, 0x4e, 0x45, 0x2d, 0x74, 0x66, 0x6c, 0x69, 0x74, 0x65, 0x32, 0x63, 0x69, 0x72, 0x63, 0x6c,
  0x65, 0x00, 0x00, 0x00};

const std::vector<float> input1_data = {
  -2.0978436, -25.836285, 7.9663463,  -52.951416, -9.174321, -10.963295, 1.4337301,  -39.000927,
  -11.76153,  -24.070623, -21.426125, -32.041714, -2.29292,  -7.595441,  -15.297459, -20.068735};
const std::vector<float> input2_data = {
  -23.881905, -8.470397,  -52.49611,  -21.756306, 1.581161,   -26.177217, -39.463478, -2.172443,
  -30.588694, -7.90017,   -17.604687, -27.376356, -26.49272,  -15.772057, 8.418157,   -36.710365,
  -35.77088,  -27.592611, -5.0617495, -7.8632812, 10.318075,  -33.451294, -53.1594,   -33.312737,
  -6.132754,  -21.647987, -38.427383, -41.75349,  -22.417152, -1.243468,  -19.772722, -55.897236};
const std::vector<float> reference_output_data = {
  -2.0978436, -23.881905, -8.470397,  -25.836285, -52.49611,  -21.756306, 7.9663463,  1.581161,
  -26.177217, -52.951416, -39.463478, -2.172443,  -9.174321,  -30.588694, -7.90017,   -10.963295,
  -17.604687, -27.376356, 1.4337301,  -26.49272,  -15.772057, -39.000927, 8.418157,   -36.710365,
  -11.76153,  -35.77088,  -27.592611, -24.070623, -5.0617495, -7.8632812, -21.426125, 10.318075,
  -33.451294, -32.041714, -53.1594,   -33.312737, -2.29292,   -6.132754,  -21.647987, -7.595441,
  -38.427383, -41.75349,  -15.297459, -22.417152, -1.243468,  -20.068735, -19.772722, -55.897236};

} // namespace concatenation_float

class TestDataFloatConcatenation : public TestDataConcatenationBase<float>
{
public:
  TestDataFloatConcatenation()
  {
    _input1_data = concatenation_float::input1_data;
    _input2_data = concatenation_float::input2_data;
    _reference_output_data = concatenation_float::reference_output_data;
    _test_kernel_model_circle = concatenation_float::test_kernel_model_circle;
  }

  ~TestDataFloatConcatenation() override = default;
};

} // namespace test_model
} // namespace onert_micro

#endif // ONERT_MICRO_TEST_MODELS_CONCATENATION_KERNEL_FLOAT_H
