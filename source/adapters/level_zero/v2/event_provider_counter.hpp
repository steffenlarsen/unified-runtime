//===--------- event_provider_counter.hpp - Level Zero Adapter ------------===//
//
// Copyright (C) 2024 Intel Corporation
//
// Part of the Unified-Runtime Project, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
#pragma once

#include <deque>
#include <memory>
#include <mutex>
#include <stack>

#include <unordered_map>
#include <ur/ur.hpp>
#include <ur_api.h>
#include <ze_api.h>

#include "../device.hpp"
#include "common.hpp"
#include "event.hpp"
#include "event_provider.hpp"

namespace v2 {

typedef ze_result_t (*zexCounterBasedEventCreate)(
    ze_context_handle_t hContext, ze_device_handle_t hDevice,
    uint64_t *deviceAddress, uint64_t *hostAddress, uint64_t completionValue,
    const ze_event_desc_t *desc, ze_event_handle_t *phEvent);

class provider_counter : public event_provider {
public:
  provider_counter(ur_platform_handle_t platform, ur_context_handle_t,
                   ur_device_handle_t);
  ~provider_counter() override;

  event_allocation allocate() override;
  ur_device_handle_t device() override;

private:
  ur_device_handle_t urDevice;

  ze_context_handle_t translatedContext;
  ze_device_handle_t translatedDevice;

  zexCounterBasedEventCreate eventCreateFunc;

  std::vector<ze_event_handle_t> freelist;
};

} // namespace v2
