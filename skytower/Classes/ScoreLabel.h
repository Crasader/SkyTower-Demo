#pragma once
#include "GameObject.h"
#include "Colleague.h"
#include <memory>

class ScoreLabel : public GameObject, public Colleague
{
public:
  ScoreLabel(std::shared_ptr<Mediator> mediator);
  virtual ~ScoreLabel();

  virtual ScoreLabel* clone() override;
  virtual void notify(NotifyState notify, int integer, Colleague* sender) override;

  void addScore(int score);
  void setScore(int score);
  int  getScore();
  void spawnGhostLabel(cocos2d::Node* layer, cocos2d::Vec2 position, int score);

private:
  void updateLabel();

  int              score_{ 0 };
  cocos2d::Label*  label_;
};

