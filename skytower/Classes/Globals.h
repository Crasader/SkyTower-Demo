#pragma once

#include "cocos2d.h"
#include <string>
#include <stdlib.h>
#include "GameObject.h"

template<typename T> class Spawner;

class Globals
{
public:
  Globals();
  virtual ~Globals();

  static int random(int min, int max);

public:
  const static bool DebugDrawColliders;

  const static cocos2d::Size designResoluton;
  const static int framesPerSecond;
  const static int framesPerSecondFixedUpdate;

  const static cocos2d::Vec2 Gravity;

  const static std::string fileNameSpriteSheet;

  const static std::string fileNameBackEarth;
  const static std::string fileNameBackSky;
  const static std::string fileNameBackSpace;
  const static std::string fileNameBackSun;

  const static std::string fileNameElementStandGrass;
  const static std::string fileNameElementBalconBlue;
  const static std::string fileNameElementBalconGreen;
  const static std::string fileNameElementBalconOrange;
  const static std::string fileNameElementDoorBlue;
  const static std::string fileNameElementDoorGreen;
  const static std::string fileNameElementDoorOrange;
  const static std::string fileNameElementTopBlue;
  const static std::string fileNameElementTopGreen;
  const static std::string fileNameElementTopOrange;
  const static std::string fileNameElementWindow;

  const static std::string fileNameScreenTitle;
  const static std::string fileNameScreenHighScores;
  const static std::string fileNameScreenHowToPlay;

  const static std::string fileNameButtonHighScores;
  const static std::string fileNameButtonHowToPlay;
  const static std::string fileNameButtonPlay;
  const static std::string fileNameButtonResume;
  const static std::string fileNameButtonPause;


  static Spawner<GameObject> spawner;

};

