#pragma once
#include <string>
#include "Mediator.h"

class Colleague
{
public:
  Colleague(Mediator* mediator);
  virtual ~Colleague();

  virtual void send(std::string string, int integer);
  virtual void notify(std::string, int integer) = 0;

protected:
  Mediator* mediator_;
};

