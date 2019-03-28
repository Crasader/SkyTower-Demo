#pragma once

#include "cocos2d.h"

class TitleScene : public cocos2d::Layer
{
public:
  static cocos2d::Scene* createScene();
  virtual bool init();
  CREATE_FUNC(TitleScene);



private:
  cocos2d::Size    screenSize_;

};
