// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "core/common/common.h"
#include "core/framework/op_kernel.h"
#include "core/framework/tensor.h"

namespace onnxruntime {

class ReverseSequenceOp : public OpKernel {
 public:
  explicit ReverseSequenceOp(const OpKernelInfo& info) : OpKernel(info) {
    int64_t batch_axis;
    int64_t time_axis;
    ORT_ENFORCE(info.GetAttr<int64_t>("batch_axis", &batch_axis).IsOK());
    ORT_ENFORCE(info.GetAttr<int64_t>("time_axis", &time_axis).IsOK());

    ORT_ENFORCE(batch_axis < 2, "Invalid batch_axis of ", batch_axis, ". Must be 0 or 1");
    ORT_ENFORCE(time_axis < 2, "Invalid time_axis of ", time_axis, ". Must be 0 or 1");

    ORT_ENFORCE(batch_axis != time_axis,
                "time_axis and batch_axis must have different values but both are ", time_axis);

    time_major_ = time_axis == 0;
  }

  Status Compute(OpKernelContext* context) const override;

 private:
  bool time_major_;
};

}  // namespace onnxruntime
