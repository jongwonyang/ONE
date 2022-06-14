/*
 * Copyright (c) 2021 Samsung Electronics Co., Ltd. All Rights Reserved
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

#include "luci/ConnectNode.h"

namespace
{

void connect(luci::ConnectNode *cn, const luci::CircleTransposeConv *node)
{
  auto *cloned = loco::must_cast<luci::CircleTransposeConv *>(cn->find_clone(node));

  luci::CircleNode *inputSizes = loco::must_cast<luci::CircleNode *>(node->inputSizes());
  luci::CircleNode *filter = loco::must_cast<luci::CircleNode *>(node->filter());
  luci::CircleNode *outBackprop = loco::must_cast<luci::CircleNode *>(node->outBackprop());
  luci::CircleNode *bias = loco::must_cast<luci::CircleNode *>(node->bias());

  cloned->inputSizes(cn->find_clone(inputSizes));
  cloned->filter(cn->find_clone(filter));
  cloned->outBackprop(cn->find_clone(outBackprop));
  cloned->bias(cn->find_clone(bias));
}

} // namespace

namespace luci
{

void ConnectNode::visit(const luci::CircleTransposeConv *node) { connect(this, node); }

} // namespace luci
