/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

/// An Alarm posts the user provided tag to its associated completion queue upon
/// expiry or cancellation.
#ifndef GRPCPP_ALARM_H
#define GRPCPP_ALARM_H

#include <functional>

#include <grpc/grpc.h>
#include <grpcpp/impl/codegen/completion_queue.h>
#include <grpcpp/impl/codegen/completion_queue_tag.h>
#include <grpcpp/impl/codegen/grpc_library.h>
#include <grpcpp/impl/codegen/time.h>
#include <grpcpp/impl/grpc_library.h>

namespace grpc {

/// A thin wrapper around \a grpc_alarm (see / \a / src/core/surface/alarm.h).
class Alarm : private GrpcLibraryCodegen {
 public:
  /// Create an unset completion queue alarm
  Alarm();

  /// Destroy the given completion queue alarm, cancelling it in the process.
  ~Alarm();

  /// DEPRECATED: Create and set a completion queue alarm instance associated to
  /// \a cq.
  /// This form is deprecated because it is inherently racy.
  /// \internal We rely on the presence of \a cq for grpc initialization. If \a
  /// cq were ever to be removed, a reference to a static
  /// internal::GrpcLibraryInitializer instance would need to be introduced
  /// here. \endinternal.
  template <typename T>
  Alarm(CompletionQueue* cq, const T& deadline, void* tag) : Alarm() {
    SetInternal(cq, TimePoint<T>(deadline).raw_time(), tag);
  }

  /// Trigger an alarm instance on completion queue \a cq at the specified time.
  /// Once the alarm expires (at \a deadline) or it's cancelled (see \a Cancel),
  /// an event with tag \a tag will be added to \a cq. If the alarm expired, the
  /// event's success bit will be true, false otherwise (ie, upon cancellation).
  template <typename T>
  void Set(CompletionQueue* cq, const T& deadline, void* tag) {
    SetInternal(cq, TimePoint<T>(deadline).raw_time(), tag);
  }

  /// Alarms aren't copyable.
  Alarm(const Alarm&) = delete;
  Alarm& operator=(const Alarm&) = delete;

  /// Alarms are movable.
  Alarm(Alarm&& rhs) : alarm_(rhs.alarm_) { rhs.alarm_ = nullptr; }
  Alarm& operator=(Alarm&& rhs) {
    alarm_ = rhs.alarm_;
    rhs.alarm_ = nullptr;
    return *this;
  }

  /// <wangfei>
  /// Ignore early check.
  /// </wangfei>
  void IgnoreEarlyCheck();

  /// Cancel a completion queue alarm. Calling this function over an alarm that
  /// has already fired has no effect.
  void Cancel();

  /// NOTE: class experimental_type is not part of the public API of this class
  /// TODO(vjpai): Move these contents to the public API of Alarm when
  ///              they are no longer experimental
  class experimental_type {
   public:
    explicit experimental_type(Alarm* alarm) : alarm_(alarm) {}

    /// Set an alarm to invoke callback \a f. The argument to the callback
    /// states whether the alarm expired at \a deadline (true) or was cancelled
    /// (false)
    template <typename T>
    void Set(const T& deadline, std::function<void(bool)> f) {
      alarm_->SetInternal(TimePoint<T>(deadline).raw_time(), std::move(f));
    }

   private:
    Alarm* alarm_;
  };

  /// NOTE: The function experimental() is not stable public API. It is a view
  /// to the experimental components of this class. It may be changed or removed
  /// at any time.
  experimental_type experimental() { return experimental_type(this); }

 private:
  void SetInternal(CompletionQueue* cq, gpr_timespec deadline, void* tag);
  void SetInternal(gpr_timespec deadline, std::function<void(bool)> f);

  internal::CompletionQueueTag* alarm_;
};

}  // namespace grpc

#endif  // GRPCPP_ALARM_H
