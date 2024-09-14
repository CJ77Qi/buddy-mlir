#map = affine_map<(d0, d1, d2) -> (d0, d2)>
#map1 = affine_map<(d0, d1, d2) -> (d2, d1)>
#map2 = affine_map<(d0, d1, d2) -> (d0, d1)>
module attributes {} {
  func.func private @Matmul(%arg0: tensor<1024x512xf16>, %arg1: tensor<512x1024xf16>) -> tensor<1024x1024xf16> attributes {} {
    %cst = arith.constant 0.000000e+00 : f16
    %0 = tensor.empty() : tensor<1024x1024xf16>
    %1 = linalg.fill ins(%cst : f16) outs(%0 : tensor<1024x1024xf16>) -> tensor<1024x1024xf16>
    %2 = linalg.generic {indexing_maps = [#map, #map1, #map2], iterator_types = ["parallel", "parallel", "reduction"]} ins(%arg0, %arg1 : tensor<1024x512xf16>, tensor<512x1024xf16>) outs(%1 : tensor<1024x1024xf16>) {
    ^bb0(%in: f16, %in_0: f16, %out: f16):
      %3 = arith.mulf %in, %in_0 : f16
      %4 = arith.addf %out, %3 : f16
      linalg.yield %4 : f16
    } -> tensor<1024x1024xf16>
    return %2 : tensor<1024x1024xf16>
  }
  func.func @forward(%arg0: tensor<1024x512xf16>, %arg1: tensor<512x1024xf16>) -> tensor<1024x1024xf16> {
    %0 = call @Matmul(%arg0, %arg1) : (tensor<1024x512xf16>, tensor<512x1024xf16>) -> tensor<1024x1024xf16>
    return %0 : tensor<1024x1024xf16>
  }
}
