#include "Colleague.h"
#include "Mediator.h"


Colleague::Colleague(std::shared_ptr<Mediator> mediator)
  : mediator_(mediator)
{
}

Colleague::~Colleague()
{
}

void Colleague::send(NotifyState notify, int integer)
{
  mediator_->send(notify, integer, this);
}
