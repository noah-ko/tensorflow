/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef TENSORFLOW_LITE_DELEGATES_GPU_CL_KERNELS_ELEMENTWISE_H_
#define TENSORFLOW_LITE_DELEGATES_GPU_CL_KERNELS_ELEMENTWISE_H_

#include <string>

#include "tensorflow/lite/delegates/gpu/cl/kernels/gpu_operation.h"
#include "tensorflow/lite/delegates/gpu/common/operations.h"
#include "tensorflow/lite/delegates/gpu/common/status.h"

namespace tflite {
namespace gpu {
namespace cl {

// Class for simple one input operations without any parameters, for example
// log, sin, cos and etc.
class ElementwiseOneInput : public ElementwiseOperation {
 public:
  ElementwiseOneInput(const OperationDef& definition,
                      const OperationType& op_type);

  // Move only
  ElementwiseOneInput(ElementwiseOneInput&& operation);
  ElementwiseOneInput& operator=(ElementwiseOneInput&& operation);
  ElementwiseOneInput(const ElementwiseOneInput&) = delete;
  ElementwiseOneInput& operator=(const ElementwiseOneInput&) = delete;
};

ElementwiseOneInput CreateElementwiseOneInput(const OperationDef& definition,
                                              const OperationType& op_type);

// Class for simple two input (first input is runtime tensor and second input is
// scalar argument) operations without any parameters, for example sub, div and
// etc.
class ElementwiseOneRuntimeOneScalar : public ElementwiseOperation {
 public:
  ElementwiseOneRuntimeOneScalar(const OperationDef& definition,
                                 const OperationType& op_type,
                                 float scalar_parameter,
                                 CalculationsPrecision scalar_precision);

  // Move only
  ElementwiseOneRuntimeOneScalar(ElementwiseOneRuntimeOneScalar&& operation);
  ElementwiseOneRuntimeOneScalar& operator=(
      ElementwiseOneRuntimeOneScalar&& operation);
  ElementwiseOneRuntimeOneScalar(const ElementwiseOneRuntimeOneScalar&) =
      delete;
  ElementwiseOneRuntimeOneScalar& operator=(
      const ElementwiseOneRuntimeOneScalar&) = delete;
};

ElementwiseOneRuntimeOneScalar CreateElementwiseOneRuntimeOneScalar(
    const CreationContext& creation_context, const OperationDef& definition,
    const OperationType& op_type, float scalar_parameter);

struct BroadcastSettings {
  bool width;
  bool height;
  bool channels;
};

// Class for simple two input(first input is runtime tensor and second input is
// runtime or constant tensor) operations without any parameters, for example
// sub, div and etc.
class ElementwiseTwoInput : public ElementwiseOperation {
 public:
  ElementwiseTwoInput() = default;
  ElementwiseTwoInput(const OperationDef& definition,
                      const OperationType& op_type,
                      const BroadcastSettings& broadcast);

  ElementwiseTwoInput(const OperationDef& definition,
                      const OperationType& op_type,
                      const BroadcastSettings& broadcast,
                      Tensor&& constant_tensor);

  // Move only
  ElementwiseTwoInput(ElementwiseTwoInput&& operation);
  ElementwiseTwoInput& operator=(ElementwiseTwoInput&& operation);
  ElementwiseTwoInput(const ElementwiseTwoInput&) = delete;
  ElementwiseTwoInput& operator=(const ElementwiseTwoInput&) = delete;

 private:
  BroadcastSettings broadcast_;
};

absl::Status CreateElementwiseTwoInput(
    const CreationContext& creation_context, const OperationDef& definition,
    const OperationType& op_type,
    const tflite::gpu::Tensor<Linear, DataType::FLOAT32>& constant_tensor,
    ElementwiseTwoInput* result);

absl::Status CreateElementwiseTwoInput(
    const CreationContext& creation_context, const OperationDef& definition,
    const OperationType& op_type,
    const tflite::gpu::Tensor<HWC, DataType::FLOAT32>& constant_tensor,
    ElementwiseTwoInput* result);

ElementwiseTwoInput CreateElementwiseTwoInput(const OperationDef& definition,
                                              const OperationType& op_type,
                                              const BHWC& shape);

}  // namespace cl
}  // namespace gpu
}  // namespace tflite

#endif  // TENSORFLOW_LITE_DELEGATES_GPU_CL_KERNELS_ELEMENTWISE_H_
