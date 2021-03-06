#pragma once

#include <memory>
#include "cocos2d.h"
#include "GameObject.h"


class HowToPlayScene : public cocos2d::Layer
{
public:
  static cocos2d::Scene* createScene();
  virtual bool init();
  CREATE_FUNC(HowToPlayScene);



private:
  cocos2d::Size    screenSize_;

  std::unique_ptr<GameObject>  title_;

};
