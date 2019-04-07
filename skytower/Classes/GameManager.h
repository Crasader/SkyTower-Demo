#pragma once

#include <memory>
#include "Mediator.h"
#include "Rope.h"
#include "Building.h"

class GameManager : public Mediator
{
public:
  GameManager();
  virtual ~GameManager();

  void setRope(std::shared_ptr<Rope> rope);
  void setBuilding(std::shared_ptr<Building> building);

  virtual void send(NotifyState notify, int integer, Colleague* colleague) override;

protected:
  std::shared_ptr<Rope> rope_;
  std::shared_ptr<Building> building_;
};

