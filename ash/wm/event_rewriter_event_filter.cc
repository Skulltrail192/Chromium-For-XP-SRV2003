// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ash/wm/event_rewriter_event_filter.h"

#include "ash/event_rewriter_delegate.h"
#include "base/logging.h"
#include "ui/base/events/event.h"

namespace ash {
namespace internal {

EventRewriterEventFilter::EventRewriterEventFilter() {}

EventRewriterEventFilter::~EventRewriterEventFilter() {}

void EventRewriterEventFilter::SetEventRewriterDelegate(
    scoped_ptr<EventRewriterDelegate> delegate) {
  delegate_.swap(delegate);
}

bool EventRewriterEventFilter::PreHandleKeyEvent(
    aura::Window* target, ui::KeyEvent* event) {
  if (!delegate_.get())
    return false;

  // Do not consume a translated key event which is generated by an IME.
  if (event->type() == ui::ET_TRANSLATED_KEY_PRESS ||
      event->type() == ui::ET_TRANSLATED_KEY_RELEASE) {
    return false;
  }

  switch (delegate_->RewriteOrFilterKeyEvent(event)) {
    case EventRewriterDelegate::ACTION_REWRITE_EVENT:
      return false;
    case EventRewriterDelegate::ACTION_DROP_EVENT:
      return true;
  }

  NOTREACHED();
  return false;
}

bool EventRewriterEventFilter::PreHandleMouseEvent(
    aura::Window* target, ui::MouseEvent* event) {
  if (!delegate_.get())
    return false;

  switch (delegate_->RewriteOrFilterLocatedEvent(event)) {
    case EventRewriterDelegate::ACTION_REWRITE_EVENT:
      return false;
    case EventRewriterDelegate::ACTION_DROP_EVENT:
      return true;
  }

  NOTREACHED();
  return false;
}

ui::TouchStatus EventRewriterEventFilter::PreHandleTouchEvent(
    aura::Window* target, ui::TouchEvent* event) {
  return ui::TOUCH_STATUS_UNKNOWN;  // Not handled.
}

ui::EventResult EventRewriterEventFilter::PreHandleGestureEvent(
    aura::Window* target, ui::GestureEvent* event) {
  return ui::ER_UNHANDLED;  // Not handled.
}

}  // namespace internal
}  // namespace ash
