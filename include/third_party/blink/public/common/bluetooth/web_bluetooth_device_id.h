// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_PUBLIC_COMMON_BLUETOOTH_WEB_BLUETOOTH_DEVICE_ID_H_
#define THIRD_PARTY_BLINK_PUBLIC_COMMON_BLUETOOTH_WEB_BLUETOOTH_DEVICE_ID_H_

#include <string>

#include "third_party/blink/public/common/common_export.h"

namespace blink {

// Used to uniquely identify a Bluetooth Device for an Origin.
// A WebBluetoothDeviceId is generated by base64-encoding a 128bit
// string.
class BLINK_COMMON_EXPORT WebBluetoothDeviceId {
 public:
  // Default constructor that creates an invalid id. We implement it so that
  // instances of this class in a container, e.g. std::unordered_map, can be
  // accessed through the [] operator. Trying to call any function of the
  // resulting object will DCHECK-fail.
  WebBluetoothDeviceId();

  // CHECKS that |device_id| is valid.
  explicit WebBluetoothDeviceId(std::string device_id);
  ~WebBluetoothDeviceId();

  // Returns the string that represents this WebBluetoothDeviceId.
  const std::string& str() const;

  // The returned WebBluetoothDeviceId is generated by creating a random 128bit
  // string and base64-encoding it.
  static WebBluetoothDeviceId Create();

  // This method will return true. if |device_id| results in a 128bit
  // base64-encoding string. Otherwise returns false.
  static bool IsValid(const std::string& device_id);

  bool IsValid() const;

  bool operator==(const WebBluetoothDeviceId& device_id) const;
  bool operator!=(const WebBluetoothDeviceId& device_id) const;

 private:
  std::string device_id_;
};

// This is required by gtest to print a readable output on test failures.
BLINK_COMMON_EXPORT std::ostream& operator<<(
    std::ostream& out,
    const WebBluetoothDeviceId& device_id);

struct WebBluetoothDeviceIdHash {
  size_t operator()(const WebBluetoothDeviceId& device_id) const {
    return std::hash<std::string>()(device_id.str());
  }
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_PUBLIC_COMMON_BLUETOOTH_WEB_BLUETOOTH_DEVICE_ID_H_