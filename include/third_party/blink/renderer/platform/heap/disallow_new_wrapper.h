// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_PLATFORM_HEAP_DISALLOW_NEW_WRAPPER_H_
#define THIRD_PARTY_BLINK_RENDERER_PLATFORM_HEAP_DISALLOW_NEW_WRAPPER_H_

#include "third_party/blink/renderer/platform/heap/garbage_collected.h"

namespace blink {

// DisallowNewWrapper wraps a disallow new type in a GarbageCollected class.
template <typename T>
class DisallowNewWrapper final
    : public GarbageCollected<DisallowNewWrapper<T>> {
 public:
  explicit DisallowNewWrapper(const T& value) : value_(value) {
    static_assert(WTF::IsDisallowNew<T>::value,
                  "T needs to be a disallow new type");
    static_assert(WTF::IsTraceable<T>::value, "T needs to be traceable");
  }

  const T& Value() const { return value_; }

  void Trace(Visitor* visitor) { visitor->Trace(value_); }

 private:
  T value_;
};

// Wraps a disallow new type in a GarbageCollected class, making it possible to
// be referenced off heap from a Persistent.
template <typename T>
DisallowNewWrapper<T>* WrapDisallowNew(const T& value) {
  return MakeGarbageCollected<DisallowNewWrapper<T>>(value);
}

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_PLATFORM_HEAP_DISALLOW_NEW_WRAPPER_H_
