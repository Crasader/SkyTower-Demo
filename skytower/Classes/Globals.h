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

  //File Names
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
  const static std::string fileNameElementHat;

  const static std::string fileNameScreenTitle;
  const static std::string fileNameScreenHighScores;
  const static std::string fileNameScreenHowToPlay;

  const static std::string fileNameButtonHighScores;
  const static std::string fileNameButtonHowToPlay;
  const static std::string fileNameButtonPlay;
  const static std::string fileNameButtonResume;
  const static std::string fileNameButtonPause;

  //Name of objects
  const static std::string backEarth;
  const static std::string backSky;
  const static std::string backSpace;
  const static std::string backSun;

  const static std::string elementStandGrass;
  const static std::string elementBalconBlue;
  const static std::string elementBalconGreen;
  const static std::string elementBalconOrange;
  const static std::string elementDoorBlue;
  const static std::string elementDoorGreen;
  const static std::string elementDoorOrange;
  const static std::string elementTopBlue;
  const static std::string elementTopGreen;
  const static std::string elementTopOrange;
  const static std::string elementWindow;
  const static std::string elementHat;

  const static std::string screenTitle;
  const static std::string screenHighScores;
  const static std::string screenHowToPlay;

  const static std::string buttonHighScores;
  const static std::string buttonHowToPlay;
  const static std::string buttonPlay;
  const static std::string buttonResume;
  const static std::string buttonPause;


  //Spawner of objects
  static Spawner<GameObject> spawner;

};

