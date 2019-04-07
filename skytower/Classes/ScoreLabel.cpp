#include "ScoreLabel.h"

USING_NS_CC;

ScoreLabel::ScoreLabel(std::shared_ptr<Mediator> mediator)
  : Colleague(mediator)
{
  label_ = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 40);

  auto graphic = new GraphicComponent(label_);
  setGraphic(graphic);
}

ScoreLabel::~ScoreLabel()
{
}

ScoreLabel * ScoreLabel::clone()
{

  return nullptr;
}

void ScoreLabel::notify(NotifyState notify, int integer)
{

}

void ScoreLabel::spawnGhostLabel(cocos2d::Vec2 position, int score)
{
}
