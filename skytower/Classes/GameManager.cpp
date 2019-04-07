#include "GameManager.h"
#include "cocos2d.h"


GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

void GameManager::setScore(std::shared_ptr<ScoreLabel> score)
{
  score_ = score;
}

void GameManager::setRope(std::shared_ptr<Rope> rope)
{
  rope_ = rope;
}

void GameManager::setBuilding(std::shared_ptr<Building> building)
{
  building_ = building;
}

void GameManager::send(NotifyState notify, int integer, Colleague * colleague)
{
  bool senderIsRope = (colleague == (&*rope_));
  if (senderIsRope) {
    cocos2d::log("Rope send something");
  }

  bool senderIsBuilding = (colleague == (&*building_));
  if (senderIsBuilding) {
    cocos2d::log("Building send something");
  }


}
