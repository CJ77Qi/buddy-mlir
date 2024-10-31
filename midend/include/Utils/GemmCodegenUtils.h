//===- GemmCodegenUtils.h -------------------------------------------------===//
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

#ifndef PIPELINES_GPU_UTILS_H
#define PIPELINES_GPU_UTILS_H

#include "mlir/IR/OperationSupport.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Pass/PassRegistry.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/StringRef.h"
#include <mlir/Dialect/SCF/IR/SCF.h>
#include <optional>

namespace mlir {
class ModuleOp;

namespace func {
class FuncOp;
} // namespace func

namespace buddy {

bool isLinalgMatmul(Operation *op);

void setMarker(mlir::Operation *op, llvm::StringRef marker);

bool hasMarker(Operation *op, StringRef marker);

bool hasAnyMarker(Operation *op, ArrayRef<StringRef> markers);

ArrayRef<StringRef> getSharedMemCopyMarkers();

static constexpr StringRef getVectorizeMarkerAttrName() {
  return "__linalg_transform_vectorize__";
}

static constexpr StringRef getGemmMarkerAttrName() { return "__buddy_gemm__"; }

static constexpr StringRef getGemmTileMConfigAttrName() {
  return "__buddy_gemm_tile_config__M";
}

static constexpr StringRef getGemmTileNConfigAttrName() {
  return "__buddy_gemm_tile_config__N";
}

static constexpr StringRef getGemmTileKConfigAttrName() {
  return "__buddy_gemm_tile_config__K";
}

static constexpr StringRef getGemmBlockXSizeAttrName() {
  return "__buddy_gemm_block_size__X";
}

static constexpr StringRef getGemmBlockYSizeAttrName() {
  return "__buddy_gemm_block_size__Y";
}

static constexpr StringRef getGemmBlockZSizeAttrName() {
  return "__buddy_gemm_block_size__Z";
}

static constexpr StringRef getGemmPipelineStageAttrName() {
  return "__buddy_gemm_pipeline_stage__";
}

static constexpr StringRef getMatmulKMainLoopMarker() {
  return "__buddy_gemm_main_loopk__";
}

static constexpr StringRef getLinalgMMALevelAttrName() {
  return "__buddy_mma_level__";
}

static constexpr StringRef getMMAPatternAttrName() { return "__buddy_mma__"; }

static constexpr StringRef getAllocSharedMemoryAMarker() {
  return "__buddy_smem_matrix_a__";
};

static constexpr StringRef getAllocSharedMemoryBMarker() {
  return "__buddy_smem_matrix_b__";
};

static constexpr StringRef getAllocSharedMemoryAccMarker() {
  return "__buddy_smem_accumulator__";
};

static constexpr StringRef getCopyToSharedMemoryAMarker() {
  return "__buddy_load_matrix_a__";
};

static constexpr StringRef getCopyToSharedMemoryBMarker() {
  return "__buddy_load_matrix_b__";
};

static constexpr StringRef getCopyFromSharedMemoryAccMarker() {
  return "__buddy_store_matrix_c__";
};

std::optional<SmallVector<int64_t, 3>> getGemmTileSize(func::FuncOp funcOp);

std::optional<SmallVector<int64_t, 3>> getGemmBlockSize(func::FuncOp funcOp);

std::optional<int64_t> getGemmPipelineStages(func::FuncOp funcOp);

bool funcHasGemm(func::FuncOp funcOp);

bool isMappedToGPUBlock(scf::ForallOp forallOp);

std::optional<scf::ForallOp> getForallOpMappedToBlock(func::FuncOp funcOp);

} // namespace buddy
} // namespace mlir

#endif