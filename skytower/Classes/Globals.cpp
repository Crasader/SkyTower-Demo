#include "Globals.h"
#include "Spawner.h"

USING_NS_CC;

const bool Globals::DebugDrawColliders{ true };

const Size Globals::designResoluton = Size(640, 960);
const int Globals::framesPerSecond = 60;
const int Globals::framesPerSecondFixedUpdate = 30;

const cocos2d::Vec2 Globals::Gravity = cocos2d::Vec2(0, -9.0f);


const std::string Globals::fileNameSpriteSheet  { "sprites.plist" };

const std::string Globals::fileNameBackEarth  { "back_earth.png" };
const std::string Globals::fileNameBackSky    { "back_sky.png" };
const std::string Globals::fileNameBackSpace  { "back_space.png" };
const std::string Globals::fileNameBackSun    { "back_sun.png" };

const std::string Globals::fileNameElementStandGrass    { "elements_grass.png" };
const std::string Globals::fileNameElementBalconBlue    { "elements_balcon-blue.png" };
const std::string Globals::fileNameElementBalconGreen   { "elements_balcon-green.png" };
const std::string Globals::fileNameElementBalconOrange  { "elements_balcon-oragne.png" };
const std::string Globals::fileNameElementDoorBlue      { "elements_door-blue.png" };
const std::string Globals::fileNameElementDoorGreen     { "elements_door-green.png" };
const std::string Globals::fileNameElementDoorOrange    { "elements_door-orange.png" };
const std::string Globals::fileNameElementTopBlue       { "elements_top-blue.png" };
const std::string Globals::fileNameElementTopGreen      { "elements_top-green.png" };
const std::string Globals::fileNameElementTopOrange     { "elements_top-orange.png" };
const std::string Globals::fileNameElementWindow        { "elements_window.png" };
const std::string Globals::fileNameElementHat           { "elements_hat.png" };

const std::string Globals::fileNameScreenTitle      { "menu_screen-title.png" };
const std::string Globals::fileNameScreenHighScores { "menu_screen-high-scores.png" };
const std::string Globals::fileNameScreenHowToPlay  { "menu_screen-how-to-play.png" };

const std::string Globals::fileNameButtonHighScores { "menu_button-high-scores.png" };
const std::string Globals::fileNameButtonHowToPlay  { "menu_button-how-to-play.png" };
const std::string Globals::fileNameButtonPlay       { "menu_button-play.png" };


const std::string Globals::backEarth { "back-earth" };
const std::string Globals::backSky   { "back-sky" };
const std::string Globals::backSpace { "back-space" };
const std::string Globals::backSun   { "back-sun" };

const std::string Globals::elementStandGrass   { "element-grass" };
const std::string Globals::elementBalconBlue   { "element-balcon-blue" };
const std::string Globals::elementBalconGreen  { "element-balcon-green" };
const std::string Globals::elementBalconOrange { "element-balcon-orange" };
const std::string Globals::elementDoorBlue     { "element-door-blue" };
const std::string Globals::elementDoorGreen    { "element-door-green" };
const std::string Globals::elementDoorOrange   { "element-door-orange" };
const std::string Globals::elementTopBlue      { "element-top-blue" };
const std::string Globals::elementTopGreen     { "element-top-green" };
const std::string Globals::elementTopOrange    { "element-top-orange" };
const std::string Globals::elementWindow       { "element-window" };
const std::string Globals::elementHat          { "element-hat" };

const std::string Globals::screenTitle       { "screen-title" };
const std::string Globals::screenHighScores  { "screen-highscores" };
const std::string Globals::screenHowToPlay   { "screen-howtoplay" };

const std::string Globals::buttonHighScores  { "button-highscores" };
const std::string Globals::buttonHowToPlay   { "button-howtoplay" };
const std::string Globals::buttonPlay        { "button-play" };
const std::string Globals::buttonResume      { "button-resume" };
const std::string Globals::buttonPause       { "button-pause" };



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
