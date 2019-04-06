#pragma once
#include <string>
#include "Colleague.h"

class Mediator
{
public:
  Mediator();
  virtual ~Mediator();

  virtual void send(std::string string, int integer, Colleague* colleague) = 0;

};

