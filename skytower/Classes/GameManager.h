#pragma once

#include <memory>
#include "Mediator.h"
#include "Rope.h"
#include "Building.h"
#include "ScoreLabel.h"

class GameManager : public Mediator
{
public:
  GameManager();
  virtual ~GameManager();

  void setScore(std::shared_ptr<ScoreLabel> score);
  void setRope(std::shared_ptr<Rope> rope);
  void setBuilding(std::shared_ptr<Building> building);

  virtual void send(NotifyState notify, int integer, Colleague* colleague) override;

protected:
  std::shared_ptr<ScoreLabel> score_;
  std::shared_ptr<Rope>       rope_;
  std::shared_ptr<Building>   building_;
};

