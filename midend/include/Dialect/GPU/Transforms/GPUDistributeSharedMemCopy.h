#ifndef DIALECT_GPU_TRANSFORMS_GPUDISTRIBUTESHAREDMEMCOPY_H
#define DIALECT_GPU_TRANSFORMS_GPUDISTRIBUTESHAREDMEMCOPY_H

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Pass/Pass.h"
#include <memory>
namespace mlir {

std::unique_ptr<OperationPass<func::FuncOp>>
createGPUDistributeSharedMemCopyPass();

} // namespace mlir
#endif