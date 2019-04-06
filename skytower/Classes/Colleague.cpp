#include "Colleague.h"



Colleague::Colleague()
{
}


Colleague::Colleague(Mediator* mediator)
  : mediator_(mediator)
{
}

Colleague::~Colleague()
{
}

void Colleague::send(std::string string, int integer)
{
  mediator_->send(string, integer, this);
}
