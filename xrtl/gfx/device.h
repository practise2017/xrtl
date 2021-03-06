// Copyright 2017 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef XRTL_GFX_DEVICE_H_
#define XRTL_GFX_DEVICE_H_

#include <cstdint>
#include <string>
#include <vector>

#include "xrtl/base/ref_ptr.h"

namespace xrtl {
namespace gfx {

// The type of the device.
enum class DeviceType : uint32_t {
  // A CPU (either the primary CPU or some CPU-like accelerator).
  kCpu = 1 << 0,
  // A GPU of some kind.
  kGpu = 1 << 1,
  // A virtualized GPU (such as in a virtualization environment).
  kGpuVirtual = kGpu | (1 << 2),
  // A GPU embedded or tightly coupled with the primary CPU.
  kGpuIntegrated = kGpu | (1 << 3),
  // A GPU separate from from the CPU.
  kGpuDiscrete = kGpu | (1 << 4),
  // Something else or unknown.
  kOther = 1 << 5,
};
XRTL_BITMASK(DeviceType);

// A device available for use by the backend graphics API.
// This may represent a physical device in the system or a logical device as
// exposed by the API.
class Device : public RefObject<Device> {
 public:
  virtual ~Device() = default;

  // Describes the limits of the device.
  //
  // Maps to:
  //  https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkPhysicalDeviceLimits.html
  struct Limits {
    // TODO(benvanik): texture sizes, buffer sizes, render-target counts, etc.
  };

  // Describes the features available for use on the device.
  // When passed to CreateContext it is used to enable specific features on the
  // created context.
  //
  // Maps to:
  //  https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkPhysicalDeviceFeatures.html
  struct Features {
    // TODO(benvanik): robust buffer access, full draw index uint32, extensions.
    // TODO(benvanik): render or compute.
  };

  // Describes a queue family available on the device.
  // Each queue family supports one or more capabilities and may have one or
  // more independent queues that can operate in parallel. Each queue within a
  // family can be retrieved from the Context after creation as a Queue object.
  //
  // Maps to:
  //  https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkQueueFamilyProperties.html
  struct QueueFamily {
    // Internal queue family identifier.
    int queue_family_index = 0;
    // True if the queues support render operations.
    bool supports_render = false;
    // True if the queues support compute operations.
    bool supports_compute = false;
    // True if the queues support transfer operations.
    bool supports_transfer = false;
    // Total number of queues that may be created from this family.
    int queue_count = 0;
    // True if the queue supports timing queries.
    bool has_timing_support = false;
  };

  // The type of the device.
  DeviceType type() const { return type_; }
  // Whether the device is a GPU.
  bool is_gpu() const { return (type_ & DeviceType::kGpu) == DeviceType::kGpu; }
  // A vendor-unique identifier (such as '123') or empty string.
  const std::string& vendor_id() const { return vendor_id_; }
  // A vendor name (such as 'NVIDIA') or empty string.
  const std::string& vendor_name() const { return vendor_name_; }
  // A vendor-specific identifier (such as '123') or empty string.
  const std::string& device_id() const { return device_id_; }
  // A vendor-specific device name (such as 'GeForce Blah') or empty string.
  const std::string& device_name() const { return device_name_; }
  // A driver version string (such as '1.2.3') or empty string.
  const std::string& driver_version() const { return driver_version_; }

  // An identifier unique within the ContextFactory that can be used to identify
  // devices that are compatible with each other and can be used to create a
  // multi-device context.
  // For example if device A has ID 1 and device B has ID 2 they are
  // incompatible and cannot be used together. If both devices shared an ID of 1
  // they could be used together but a device C with ID 2 could not be.
  int multi_device_group_id() const { return multi_device_group_id_; }

  // Limits of the device. Attempting to use values out of these ranges will
  // result in failures that are difficult to detect so always check first.
  const Limits& limits() const { return limits_; }

  // Available device features for use by the context.
  const Features& features() const { return features_; }

  // A list of the queue families and capabilities available on the device.
  const std::vector<QueueFamily>& queue_families() const {
    return queue_families_;
  }

  // Returns true if the set of required features is satisfiable from the set
  // of available features on the device.
  bool IsCompatible(const Features& requested_features) const;

 protected:
  Device() = default;

  DeviceType type_ = DeviceType::kOther;
  std::string vendor_id_;
  std::string vendor_name_;
  std::string device_id_;
  std::string device_name_;
  std::string driver_version_;
  int multi_device_group_id_ = 0;
  Limits limits_;
  Features features_;
  std::vector<QueueFamily> queue_families_;
};

}  // namespace gfx
}  // namespace xrtl

#endif  // XRTL_GFX_DEVICE_H_
