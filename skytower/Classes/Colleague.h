#pragma once
#include <string>
#include <memory>
#include "Enums.h"

class Mediator;

class Colleague
{
public:
  Colleague(std::shared_ptr<Mediator> mediator);
  virtual ~Colleague();

  virtual void send(NotifyState notify, int integer = 0);
  virtual void notify(NotifyState notify, int integer, Colleague* sender) = 0;

protected:
  std::shared_ptr<Mediator> mediator_;
};

