#include "Pipelines/LinalgMemrefOpt.h"
#include "GPU/Transforms/GPUDistributeSharedMemCopy.h"
#include "GPU/Transforms/GPUDistributeToWarp.h"
#include "GPU/Transforms/RemoveReduntantLoops.h"
#include "GPU/Transforms/TensorCoreVectorization.h"
#include "Linalg/Transforms/LinalgPromotion.h"
#include "Utils/PipelineUtils.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/MemRef/Transforms/Passes.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Pass/PassRegistry.h"
#include "mlir/Transforms/Passes.h"
#include <string>

using namespace mlir;

namespace {

void addGemmLinalgMemrefOptPipeline(OpPassManager &pm) {
  // TODO : use funcAnchor to nest the specific matmul func
  pm.addNestedPass<func::FuncOp>(createLinalgPromotionPass());
  pm.addNestedPass<func::FuncOp>(createCanonicalizerPass());
  pm.addNestedPass<func::FuncOp>(createCSEPass());
  pm.addNestedPass<func::FuncOp>(createCanonicalizerPass());
  pm.addNestedPass<func::FuncOp>(createGPUDistributeToWarpPass());
  pm.addNestedPass<func::FuncOp>(createRemoveReduntantLoops());
  pm.addNestedPass<func::FuncOp>(createTensorCoreVectorizationPass());
  pm.addNestedPass<func::FuncOp>(memref::createFoldMemRefAliasOpsPass());
  pm.addNestedPass<func::FuncOp>(createCanonicalizerPass());
  pm.addNestedPass<func::FuncOp>(createCSEPass());
  pm.addNestedPass<func::FuncOp>(createGPUDistributeSharedMemCopyPass());
}

void createLinalgMemrefOptPipelineImpl(OpPassManager &pm,
                                       const std::string target) {
  addGemmLinalgMemrefOptPipeline(pm);
}

} // namespace

void mlir::buddy::createLinalgMemrefOptPipeline(
    OpPassManager &pm, const LinalgMemrefOptPipelineOptions &options) {
  invokeOpPassPipelineBuilder(createLinalgMemrefOptPipelineImpl, pm,
                              options.target);
}

void mlir::buddy::registerLinalgMemrefOptPipeline() {
  PassPipelineRegistration<LinalgMemrefOptPipelineOptions>(
      "linalg-memref-opt", "Linalg Opt Pipeline with Memref",
      createLinalgMemrefOptPipeline);
}
