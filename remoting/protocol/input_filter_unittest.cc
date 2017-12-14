// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "remoting/protocol/input_filter.h"

#include "remoting/proto/event.pb.h"
#include "remoting/protocol/protocol_mock_objects.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

using ::testing::_;

namespace remoting {
namespace protocol {

MATCHER_P2(EqualsKeyEvent, usb_keycode, pressed, "") {
  return arg.usb_keycode() == static_cast<uint32>(usb_keycode) &&
         arg.pressed() == pressed;
}

MATCHER_P2(EqualsMouseMoveEvent, x, y, "") {
  return arg.x() == x && arg.y() == y;
}

static KeyEvent NewKeyEvent(uint32 usb_keycode, bool pressed) {
  KeyEvent event;
  event.set_usb_keycode(usb_keycode);
  event.set_pressed(pressed);
  return event;
}

static MouseEvent MouseMoveEvent(int x, int y) {
  MouseEvent event;
  event.set_x(x);
  event.set_y(y);
  return event;
}

static void InjectTestSequence(protocol::InputStub* input_stub) {
  // Inject a key event.
  input_stub->InjectKeyEvent(NewKeyEvent(0, true));
  input_stub->InjectKeyEvent(NewKeyEvent(0, false));

  // Inject mouse movemement.
  input_stub->InjectMouseEvent(MouseMoveEvent(10, 20));
}

// Verify that the filter passes events on correctly to a configured stub.
TEST(InputFilterTest, EventsPassThroughFilter) {
  MockInputStub input_stub;
  InputFilter input_filter(&input_stub);

  EXPECT_CALL(input_stub, InjectKeyEvent(EqualsKeyEvent(0, true)));
  EXPECT_CALL(input_stub, InjectKeyEvent(EqualsKeyEvent(0, false)));
  EXPECT_CALL(input_stub, InjectMouseEvent(EqualsMouseMoveEvent(10, 20)));

  InjectTestSequence(&input_filter);
}

// Verify that the filter ignores events if disabled.
TEST(InputFilterTest, IgnoreEventsIfDisabled) {
  MockInputStub input_stub;
  InputFilter input_filter(&input_stub);

  input_filter.set_enabled(false);

  EXPECT_CALL(input_stub, InjectKeyEvent(_)).Times(0);
  EXPECT_CALL(input_stub, InjectMouseEvent(_)).Times(0);

  InjectTestSequence(&input_filter);
}

// Verify that the filter ignores events if not configured.
TEST(InputFilterTest, IgnoreEventsIfNotConfigured) {
  InputFilter input_filter;

  InjectTestSequence(&input_filter);
}

} // namespace protocol
} // namespace remoting
