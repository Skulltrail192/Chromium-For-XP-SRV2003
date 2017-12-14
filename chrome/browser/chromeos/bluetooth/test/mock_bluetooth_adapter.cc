// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/chromeos/bluetooth/test/mock_bluetooth_adapter.h"

namespace chromeos {

MockBluetoothAdapter::Observer::Observer() {}
MockBluetoothAdapter::Observer::~Observer() {}

MockBluetoothAdapter::MockBluetoothAdapter(const std::string& address,
                                           const std::string& name) {
  address_ = address;
  name_ = name;
}

MockBluetoothAdapter::~MockBluetoothAdapter() {}

}  // namespace chromeos
