#pragma once

enum {
  BACKGROUND = -1,
  MIDDLEGROUND = 0,
  FOREGROUND = 1
};


enum {
  NONE,
  ELEMENT_FREE,
  ELEMENT_FALLING,
  ELEMENT_BUILDING,
  BUILDING,
  ROPE,
  FLYINGTHING
};


enum class NotifyState {
  EmptyQueue,
  EmptyQueueAndRope,
  ElementAdded,
  AddScore
};