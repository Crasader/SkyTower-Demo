
#include "TitleScene.h"
#include "GameScene.h"
#include "HighScoresScene.h"
#include "HowToPlayScene.h"
#include "Globals.h"
#include "Enums.h"
#include "Spawner.h"
#include <memory>

USING_NS_CC;


Scene* TitleScene::createScene()
{
  auto scene = Scene::create();
  auto layer = TitleScene::create();


  scene->addChild(layer);
  return scene;
}

bool TitleScene::init()
{
  if (!Layer::init()) {
    return false;
 }

  auto size = Director::getInstance()->getWinSize();


  //Spawn Background
  title_ = std::unique_ptr<GameObject>(Globals::spawner.spawn("title"));
  
  title_->getGraphic()->setParentNode(this, BACKGROUND);


  auto buttonPlay = Sprite::createWithSpriteFrameName(Globals::fileNameButtonPlay);
  auto buttonPlaySelected = Sprite::createWithSpriteFrameName(Globals::fileNameButtonPlay);
  buttonPlaySelected->setColor(Color3B::GRAY);

  auto buttonHighScores = Sprite::createWithSpriteFrameName(Globals::fileNameButtonHighScores);
  auto buttonHighScoresSelected = Sprite::createWithSpriteFrameName(Globals::fileNameButtonHighScores);
  buttonHighScoresSelected->setColor(Color3B::GRAY);

  auto buttonHowToPlay = Sprite::createWithSpriteFrameName(Globals::fileNameButtonHowToPlay);
  auto buttonHowToPlaySelected = Sprite::createWithSpriteFrameName(Globals::fileNameButtonHowToPlay);
  buttonHowToPlaySelected->setColor(Color3B::GRAY);


  auto itemPlay = MenuItemSprite::create(buttonPlay, buttonPlaySelected, [](Ref* sender) {
    auto scene = GameScene::createScene();
    auto transition = TransitionFade::create(0.5f, scene);
    Director::getInstance()->replaceScene(transition);
  });

  auto itemHighScores = MenuItemSprite::create(buttonHighScores, buttonHighScoresSelected, [](Ref* sender) {
    auto scene = HighScoresScene::createScene();
    auto transition = TransitionFade::create(0.5f, scene);
    Director::getInstance()->replaceScene(transition);
  });

  auto itemHowToPlay = MenuItemSprite::create(buttonHowToPlay, buttonHowToPlaySelected, [](Ref* sender) {
    auto scene = HowToPlayScene::createScene();
    auto transition = TransitionFade::create(0.5f, scene);
    Director::getInstance()->replaceScene(transition);
  });

  auto menu = Menu::create(itemPlay, itemHighScores, itemHowToPlay, nullptr);
  menu->alignItemsVertically();
  menu->setPosition( Vec2(size.width / 2, size.height / 3) );
  this->addChild(menu);

  return true;
}



