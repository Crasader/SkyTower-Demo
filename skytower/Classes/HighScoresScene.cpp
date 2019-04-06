
#include "HighScoresScene.h"
#include "TitleScene.h"
#include "Globals.h"
#include "Enums.h"
#include "Spawner.h"
#include <memory>

USING_NS_CC;


Scene* HighScoresScene::createScene()
{
  auto scene = Scene::create();
  auto layer = HighScoresScene::create();


  scene->addChild(layer);
  return scene;
}

bool HighScoresScene::init()
{
  if (!Layer::init()) {
    return false;
 }

  auto size = Director::getInstance()->getWinSize();


  //Spawn Background
  title_ = std::unique_ptr<GameObject>(Globals::spawner.spawn(Globals::screenHighScores));
  title_->getGraphic()->setParentNode(this, BACKGROUND);

  //Add mouse event listener
  auto touchListener = EventListenerTouchOneByOne::create();
  touchListener->onTouchBegan = [](Touch* touch, Event* event)->bool {
    auto scene = TitleScene::createScene();
    auto transition = TransitionFade::create(0.5f, scene);
    Director::getInstance()->replaceScene(transition);
    return true;
  };
  this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

  return true;
}



