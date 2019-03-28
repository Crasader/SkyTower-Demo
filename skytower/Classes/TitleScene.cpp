
#include "TitleScene.h"
#include "Globals.h"
#include "Enums.h"
#include "Spawner.h"

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

  //Director::getInstance()->getOpenGLView()->setCursorVisible(true);

  ////Add labels
  //std::string title;
  //bool win = (targetsDestroyed == targetsTotal);
  //if (win) {
  //  title = "Congratulations!";
  //}
  //else {
  //  title = "Game Over";
  //}

  //std::string totals = "Destroyed " + std::to_string(targetsDestroyed) + " targets of " + std::to_string(targetsTotal);

  //auto labelTitle = Label::createWithTTF(title, "fonts/Marker Felt.ttf", 100);

  //labelTitle->setPosition(Vec2(size.width / 2, (size.height / 5) * 4));
  //this->addChild(labelTitle);

  //auto labelDestroyed = Label::createWithTTF(totals, "fonts/Marker Felt.ttf", 50);

  //labelDestroyed->setPosition(Vec2(size.width / 2, (size.height / 5) *3));
  //this->addChild(labelDestroyed);



  //auto itemReplay = MenuItemFont::create("Replay", [](Ref* sender) {
  //  auto scene = GameLayer::createScene();
  //  Director::getInstance()->replaceScene(scene);
  //});

  //auto menu = Menu::create(itemReplay, nullptr);
  ////menu->alignItemsVertically();
  //menu->setPosition(Vec2(size.width / 2, (size.height / 5) * 1.5f));
  //this->addChild(menu);

  return true;
}



