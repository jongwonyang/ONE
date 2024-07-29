/*
 * Copyright (c) 2020 Samsung Electronics Co., Ltd. All Rights Reserved
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

#include "Optimizer.h"

#include <AclSubTensorAnalyzer.h>

#include <compiler/LoweredGraph.h>
#include <util/logging.h>

#include <cassert>

namespace onert
{
namespace backend
{
namespace acl_cl
{

Optimizer::Optimizer(BackendContext *context)
  : _context{context},
    _tensor_builder{std::dynamic_pointer_cast<TensorBuilder>(context->tensor_builder)}
{
  assert(context);
}

void Optimizer::optimize()
{
  // Concat elimination (build subtensor info)
  {
    acl_common::AclSubTensorAnalyzer sa{*_context->graph()};
    sa.setUsePadding();
    _context->graph()->operations().iterate(
      [&](const ir::OperationIndex &, const ir::IOperation &op) { op.accept(sa); });

    _tensor_builder->parent_map(sa.releaseParentMap());
  }
}

} // namespace acl_cl
} // namespace backend
} // namespace onert
