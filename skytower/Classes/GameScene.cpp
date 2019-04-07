
#include "GameScene.h"
#include "Globals.h"
#include "Enums.h"
#include "Spawner.h"
#include "Rope.h"
#include "Building.h"
#include "GameManager.h"
#include <memory>
#include <string>

USING_NS_CC;


Scene* GameScene::createScene()
{
  auto scene = Scene::create();
  auto layer = GameScene::create();

  scene->addChild(layer);
  return scene;
}

bool GameScene::init()
{
  if (!Layer::init()) {
    return false;
 }

  GameObject* gameObject;

  screenSize_ = Director::getInstance()->getWinSize();

  gameLayer_ = Node::create();
  this->addChild(gameLayer_);


  //Spawn Background
  backgroundSky_ = std::unique_ptr<GameObject>(Globals::spawner.spawn(Globals::backSky));
  backgroundSky_->getGraphic()->setParentNode(this, BACKGROUND);

  backgroundEarth_ = std::unique_ptr<GameObject>(Globals::spawner.spawn(Globals::backEarth));
  backgroundEarth_->getGraphic()->setParentNode(gameLayer_, BACKGROUND);

  //Create GameManager (MEdiator) object
  gameManager_ = std::make_shared<GameManager>();

  //Create Score label;
  score_ = std::make_shared<ScoreLabel>(gameManager_);
  score_->setPosition( Vec2(25, screenSize_.height - score_->getCocosNode()->getBoundingBox().size.height + 25));
  this->addChild(score_->getCocosNode());

  //Create building base
  auto initialPosition(Vec2(screenSize_.width / 2, 100));
  building_ = std::make_unique<Building>(initialPosition, gameManager_);
  building_->setTag(BUILDING);
  //Add stand with grass to building
  gameObject = Globals::spawner.spawn(Globals::elementStandGrass);
  gameObject->setPosition(Vec2(screenSize_.width / 2, 150));
  gameLayer_->addChild( gameObject->getCocosNode() );
  building_->addElement( std::shared_ptr<GameObject>(gameObject) );
  //objectsPool_.push_back(building_);

  ////Create rope
  auto input = new PlayerInputComponent(&inputState_);
  rope_ = std::make_shared<Rope>(input, gameLayer_, &objectsPool_, gameManager_);
  rope_->setPosition(Vec2(screenSize_.width / 2, screenSize_.height + 100.0f));
  this->addChild(rope_->getCocosNode());
  objectsPool_.push_back(rope_);

  //Add elements to rope queue
  int numberOfElements = 10;
  std::vector<std::string> buildngElements{ Globals::elementWindow, Globals::elementBalconBlue, Globals::elementBalconGreen, Globals::elementBalconOrange };
  std::vector<std::string> topElements{ Globals::elementTopBlue, Globals::elementTopGreen, Globals::elementTopOrange };
  std::vector<std::string> doorElements{ Globals::elementDoorBlue, Globals::elementDoorGreen, Globals::elementDoorOrange };
  
  // First drop element is door
  gameObject = Globals::spawner.spawn( doorElements[Globals::random(0, doorElements.size()-1)] ); 
  rope_->addElement( std::shared_ptr<GameObject>(gameObject) );
 
  int elementType;
  for (int i = 0; i < numberOfElements; i++) {
    elementType = Globals::random(0, buildngElements.size() - 1);
    gameObject = Globals::spawner.spawn(buildngElements[elementType]);
    rope_->addElement( std::shared_ptr<GameObject>(gameObject) );
  };

  // Last drop element is top
  gameObject = Globals::spawner.spawn( topElements[Globals::random(0, topElements.size() - 1)] ); 
  rope_->addElement(std::shared_ptr<GameObject>(gameObject));


  gameManager_->setRope(rope_);
  gameManager_->setBuilding(building_);

  // Add mouse listeners
  auto touchListener = EventListenerMouse::create();
  touchListener->onMouseMove = CC_CALLBACK_1(GameScene::onMouseMove, this);
  touchListener->onMouseDown = CC_CALLBACK_1(GameScene::onMouseDown, this);
  touchListener->onMouseUp = CC_CALLBACK_1(GameScene::onMouseUp, this);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

  this->scheduleUpdate();
  return true;
}


void GameScene::update(float deltaTime)
{
  //rope_->update(deltaTime);

  //Update or delete objects from pool
  for (auto p = objectsPool_.begin(); p != objectsPool_.end(); p++) {

    if ((*p)->isReadyToDie) {
      p = objectsPool_.erase(p); // remove object from pool

      bool pIsEndIterator = (p == objectsPool_.end());
      if (pIsEndIterator) break;
    }
    else {
      (*p)->update(deltaTime);
    }
  }

  //Perfom Fixed Update for physic events
  fixedTimeCounter += deltaTime;
  float fixedUpdatePeriod = 1.0f / Globals::framesPerSecondFixedUpdate;
  while (fixedTimeCounter > fixedUpdatePeriod ) {
    fixedUpdate(fixedUpdatePeriod);
    fixedTimeCounter -= fixedUpdatePeriod;
  }
}


void GameScene::fixedUpdate(float deltaTime)
{
  //Update view positon
  updateView();

  //Check collisons
  std::shared_ptr<GameObject> topElement = building_->getTopElement();

  for (auto object : objectsPool_) {
    object->fixedUpdate(deltaTime);

    bool objectIsFreeElement = (object->getTag() == ELEMENT_FREE);
    if (objectIsFreeElement) {

      bool intesectBuildingAndElement = topElement->getCollider()->intersectsCollider(object->getCollider());
      if (intesectBuildingAndElement) {
        object->stopMovement();
        building_->addElement(object);

        //// Add squash action
        auto scale = ScaleBy::create(0.1f, 1.2f, 0.8f);
        auto down = EaseOut::create(scale, 2.0f);
        auto up = EaseIn::create(scale->reverse(), 1.5f);
        auto action = Sequence::create(down, up, nullptr);
        object->getCocosNode()->runAction(action);
        ////
      }
    }

  }

}

void GameScene::updateView()
{
  auto elementPosition = building_->getTopElement()->getPosition();

  if ((elementPosition.y + gameLayerPos_.y) > (screenSize_.height / 3)) {
    gameLayerPos_.y -= 5;
    gameLayer_->setPosition(gameLayerPos_);
  }

}

void GameScene::onMouseMove(cocos2d::Event * event)
{
  EventMouse* e = (EventMouse*)event;
  cocos2d::Vec2 newMousePosition;
  newMousePosition.x = e->getCursorX();
  newMousePosition.y = e->getCursorY();
  inputState_.setMousePosition(newMousePosition);
}

void GameScene::onMouseDown(cocos2d::Event * event)
{
  inputState_.setMouseDown(true);
}

void GameScene::onMouseUp(cocos2d::Event * event)
{
  inputState_.setMouseDown(false);
}




