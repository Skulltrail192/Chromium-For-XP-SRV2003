// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_EVENTS_EVENT_TARGET_H_
#define UI_BASE_EVENTS_EVENT_TARGET_H_

#include "base/compiler_specific.h"
#include "ui/base/events/event_handler.h"
#include "ui/base/ui_export.h"

namespace ui {

class EventDispatcher;

class UI_EXPORT EventTarget : public EventHandler {
 public:
  typedef std::vector<EventTarget*> EventTargets;

  class TestApi {
   public:
    explicit TestApi(EventTarget* target) : target_(target) {}

    const EventHandlerList& pre_target_handlers() {
      return target_->pre_target_list_;
    }

   private:
    TestApi();
    EventTarget* target_;

    DISALLOW_COPY_AND_ASSIGN(TestApi);
  };

  class DispatcherApi {
   public:
    explicit DispatcherApi(EventTarget* target) : target_(target) {}

    const EventHandlerList& pre_target_list() const {
      return target_->pre_target_list_;
    }

   private:
    DispatcherApi();
    EventTarget* target_;

    DISALLOW_COPY_AND_ASSIGN(DispatcherApi);
  };

  EventTarget();
  virtual ~EventTarget();

  virtual bool CanAcceptEvents() = 0;
  virtual EventTarget* GetParentTarget() = 0;

  // Adds a handler to receive events before the target. The handler must be
  // explicitly removed from the target before the handler is destroyed. The
  // EventTarget does not take ownership of the handler.
  void AddPreTargetHandler(EventHandler* handler);
  void RemovePreTargetHandler(EventHandler* handler);

  // Adds a handler to receive events after the target. The handler must be
  // explicitly removed from the target before the handler is destroyed. The
  // EventTarget does not take ownership of the handler.
  void AddPostTargetHandler(EventHandler* handler);
  void RemovePostTargetHandler(EventHandler* handler);

 protected:
  void set_target_handler(EventHandler* handler) {
    target_handler_ = handler;
  }

 private:
  friend class EventDispatcher;

  // Returns the list of handlers that should receive the event before the
  // target. The handlers from the outermost target are first in the list, and
  // the handlers on |this| are the last in the list.
  void GetPreTargetHandlers(EventHandlerList* list);

  // Returns the list of handlers that should receive the event after the
  // target. The handlers from the outermost target are last in the list, and
  // the handlers on |this| are the first in the list.
  void GetPostTargetHandlers(EventHandlerList* list);

  // Overridden from EventHandler:
  virtual EventResult OnKeyEvent(KeyEvent* event) OVERRIDE;
  virtual EventResult OnMouseEvent(MouseEvent* event) OVERRIDE;
  virtual EventResult OnScrollEvent(ScrollEvent* event) OVERRIDE;
  virtual TouchStatus OnTouchEvent(TouchEvent* event) OVERRIDE;
  virtual EventResult OnGestureEvent(GestureEvent* event) OVERRIDE;

  EventHandlerList pre_target_list_;
  EventHandlerList post_target_list_;
  EventHandler* target_handler_;

  DISALLOW_COPY_AND_ASSIGN(EventTarget);
};

}  // namespace ui

#endif  // UI_BASE_EVENTS_EVENT_TARGET_H_
