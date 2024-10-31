//===- Passes.h ----------------------------------------------------------===//
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//===----------------------------------------------------------------------===//
#ifndef DIALECT_TRANSFORM_PASSES_H
#define DIALECT_TRANSFORM_PASSES_H

#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassRegistry.h"

// Include the constructor of passes in Transform Dialect
#include "Transform/Transforms/TransformDialectInterpreter.h"
#include "Transform/Transforms/TransformInsertion.h"

namespace mlir {
class ModuleOp;
// Generate the definition of Transform Passes
#define GEN_PASS_DECL
#include "Transform/Passes.h.inc"

#define GEN_PASS_REGISTRATION
#include "Transform/Passes.h.inc"

} // namespace mlir

#endif
