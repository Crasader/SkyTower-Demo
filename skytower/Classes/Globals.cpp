#include "Globals.h"
#include "Spawner.h"

USING_NS_CC;


const Size Globals::designResoluton = Size(1024, 768);
const int Globals::framesPerSecond = 60;
const int Globals::framesPerSecondFixedUpdate = 30;

const float Globals::Gravity = -2.5f;


const std::string Globals::fileNameSpriteSheet  { "sprites.plist" };

const std::string Globals::fileNameBackEarth  { "back_earth.png" };
const std::string Globals::fileNameBackSky    { "back_sky.png" };
const std::string Globals::fileNameBackSpace  { "back_space.png" };
const std::string Globals::fileNameBackSun    { "back_sun.png" };

const std::string Globals::fileNameElementStandGrass    { "elements_grass.png" };
const std::string Globals::fileNameElementBalconBlue    { "elements_balcon-blue.png" };
const std::string Globals::fileNameElementBalconGreen   { "elements_balcon-green.png" };
const std::string Globals::fileNameElementBalconOrange  { "elements_balcon-orange.png" };
const std::string Globals::fileNameElementDoorBlue      { "elements_door-balcon.png" };
const std::string Globals::fileNameElementDoorGreen     { "elements_door-green.png" };
const std::string Globals::fileNameElementDoorOrange    { "elements_door-orange.png" };
const std::string Globals::fileNameElementTopBlue       { "elements_top-blue.png" };
const std::string Globals::fileNameElementTopGreen      { "elements_top-green.png" };
const std::string Globals::fileNameElementTopOrange     { "elements_top-orange.png" };
const std::string Globals::fileNameElementWindow        { "elements_window.png" };

const std::string Globals::fileNameScreenTitle      { "menu_screen-title.png" };
const std::string Globals::fileNameScreenHighScores { "menu_screen-high-scores.png" };
const std::string Globals::fileNameScreenHowToPlay  { "menu_screen-how-to-play.png" };

const std::string Globals::fileNameButtonHighScores { "menu_button-high-scores.png" };
const std::string Globals::fileNameButtonHowToPlay  { "menu_button-how-to-play.png" };
const std::string Globals::fileNameButtonPlay       { "menu_button-play.png" };


Spawner<GameObject> Globals::spawner;


Globals::Globals()
{
}

Globals::~Globals()
{
}

int Globals::random(int min, int max)
{
  return rand() % (max - min + 1) + min;
}
