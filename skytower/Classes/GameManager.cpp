#include "GameManager.h"
#include "Globals.h"
#include "GameOverScene.h"
#include "cocos2d.h"

USING_NS_CC;

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
    //Empty queue and rope - game over
    if (notify == NotifyState::EmptyQueueAndRope) {
      auto scene = GameOverScene::createScene();
      auto transition = TransitionFade::create(0.5f, scene);
      Director::getInstance()->replaceScene(transition);
    };
  }

  bool senderIsBuilding = (colleague == (&*building_));
  if (senderIsBuilding) {

    //Added new element
    if (notify == NotifyState::ElementAdded) {
      auto balance = building_->computeBalance();
      building_->setStagger(balance);
    }

    //Score is updating
    if (notify == NotifyState::AddScore) {
      score_->addScore(integer);

      auto buildingObject = dynamic_cast<Building*>(colleague);
      if (buildingObject) {
        auto gameObject = buildingObject->getTopElement();
        auto ghostPositon = gameObject->getPosition();

        //Calculate position of Ghost Score
        auto locatedRightSide = ((Globals::screenSize.width / 2) - ghostPositon.x) > 0;
        if (locatedRightSide) {
          ghostPositon.x += gameObject->getCocosNode()->getBoundingBox().size.width;
        }
        else {
          ghostPositon.x -= gameObject->getCocosNode()->getBoundingBox().size.width;
        }
        auto spawnLayer = gameObject->getCocosNode()->getParent();
        score_->spawnGhostLabel(spawnLayer, ghostPositon, integer);
      }

    }

  }

}
