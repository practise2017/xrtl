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

#ifndef XRTL_GFX_ES3_ES3_QUEUE_FENCE_H_
#define XRTL_GFX_ES3_ES3_QUEUE_FENCE_H_

#include "xrtl/base/threading/event.h"
#include "xrtl/gfx/es3/es3_common.h"
#include "xrtl/gfx/queue_fence.h"

namespace xrtl {
namespace gfx {
namespace es3 {

class ES3QueueFence : public QueueFence {
 public:
  ES3QueueFence();
  ~ES3QueueFence() override;

  ref_ptr<Event> event() const { return event_; }

 private:
  ref_ptr<Event> event_;
};

}  // namespace es3
}  // namespace gfx
}  // namespace xrtl

#endif  // XRTL_GFX_ES3_ES3_QUEUE_FENCE_H_
