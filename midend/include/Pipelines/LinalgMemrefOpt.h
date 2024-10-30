//===- LinalgMemrefOpt.h --------------------------------------------------===//
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

#ifndef PIPELINES_MEMREFOPT_H
#define PIPELINES_MEMREFOPT_H

#include "mlir/Pass/PassManager.h"
#include "mlir/Pass/PassOptions.h"
#include "mlir/Pass/PassRegistry.h"
#include "llvm/Support/CommandLine.h"
#include <string>

namespace mlir {
namespace buddy {

struct LinalgMemrefOptPipelineOptions
    : public PassPipelineOptions<LinalgMemrefOptPipelineOptions> {
  Option<std::string> target{
      *this,
      "target",
      llvm::cl::desc("An optional attribute to speicify target."),
  };
};

void createLinalgMemrefOptPipeline(
    OpPassManager &pm, const LinalgMemrefOptPipelineOptions &options);

void registerLinalgMemrefOptPipeline();

} // namespace buddy
} // namespace mlir

#endif
