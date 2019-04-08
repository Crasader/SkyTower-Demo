
#include "GameOverScene.h"
#include "Globals.h"
#include "GameScene.h"
#include "TitleScene.h"

USING_NS_CC;

int GameOverScene::targetsDestroyed = 0;
int GameOverScene::targetsTotal = 0;


Scene* GameOverScene::createScene()
{
  auto scene = Scene::create();
  auto layer = GameOverScene::create();


  scene->addChild(layer);
  return scene;
}

bool GameOverScene::init()
{
  if (!Layer::init()) {
    return false;
 }

  auto size = Director::getInstance()->getWinSize();
  Director::getInstance()->getOpenGLView()->setCursorVisible(true);

  //Add labels
  std::string title = "Game Over";
  auto labelTitle = Label::createWithTTF(title, "fonts/Marker Felt.ttf", 100);

  labelTitle->setPosition(Vec2(size.width / 2, (size.height / 5) * 4));
  this->addChild(labelTitle);



  auto itemReplay = MenuItemFont::create("Replay", [](Ref* sender) {
    auto scene = GameScene::createScene();
    auto transition = TransitionFade::create(0.5f, scene);
    Director::getInstance()->replaceScene(transition);
  });

  auto itemExit = MenuItemFont::create("Exit", [](Ref* sender) {
    auto scene = TitleScene::createScene();
    auto transition = TransitionFade::create(0.5f, scene);
    Director::getInstance()->replaceScene(transition);
  });

  auto menu = Menu::create(itemReplay, itemExit, nullptr);
  menu->alignItemsVertically();
  menu->setPosition(Vec2(size.width / 2, (size.height / 5) * 1.5f));
  this->addChild(menu);

  return true;
}



