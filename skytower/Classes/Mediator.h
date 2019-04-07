#pragma once
#include <string>
#include "Colleague.h"
#include "Enums.h"

class Mediator
{
public:
  Mediator();
  virtual ~Mediator();

  virtual void send(NotifyState notify, int integer, Colleague* colleague) = 0;

};

