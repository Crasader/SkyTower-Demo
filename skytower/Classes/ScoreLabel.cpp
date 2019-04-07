#include "ScoreLabel.h"

USING_NS_CC;

ScoreLabel::ScoreLabel(std::shared_ptr<Mediator> mediator)
  : Colleague(mediator)
{
  label_ = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 60);

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

void ScoreLabel::notify(NotifyState notify, int integer, Colleague* sender)
{

}

void ScoreLabel::addScore(int score)
{
  score_ += score;
  updateLabel();
}

void ScoreLabel::setScore(int score)
{
  score_ = score;
  updateLabel();
}

int ScoreLabel::getScore()
{
  return score_;
}

void ScoreLabel::spawnGhostLabel(cocos2d::Node* layer, cocos2d::Vec2 position, int score)
{
  auto stringScore = std::to_string(score);
  auto label = Label::createWithTTF(stringScore, "fonts/Marker Felt.ttf", 40);
  auto newPosition = Vec2(position.x, position.y + 50);
  label->setPosition(newPosition);

  //Add Fade action
  const float duration = 1.0f;
  auto fade = FadeOut::create(duration);
  auto move = MoveBy::create(duration, Vec2(0,100));
  auto selfDestroy = CallFuncN::create([](Ref* sender) {
    Label* label = dynamic_cast<Label*>(sender);
    label->removeFromParent();
  });
  auto actions = Spawn::create(fade, move, nullptr);
  auto sequence = Sequence::create(actions, selfDestroy, nullptr);
  label->runAction(sequence);

  layer->addChild(label, FOREGROUND);
}

void ScoreLabel::updateLabel()
{
  auto stringScore = std::to_string(score_);
  label_->setString(stringScore);
}

