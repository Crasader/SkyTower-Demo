#include "AppDelegate.h"
#include "Globals.h"
#include "TitleScene.h"
#include "Spawner.h"
#include "Enums.h"
#include "Components\BoxCollider.h"


// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;


//static cocos2d::Size designResolutionSize = cocos2d::Size(320, 480);
//static cocos2d::Size smallResolutionSize = cocos2d::Size(320, 480);
//static cocos2d::Size mediumResolutionSize = cocos2d::Size(768, 1024);
//static cocos2d::Size largeResolutionSize = cocos2d::Size(1536, 2048);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("skytower", cocos2d::Rect(0, 0, Globals::designResoluton.width, Globals::designResoluton.height));
#else
        glview = GLViewImpl::create("skytower");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    director->setContentScaleFactor(0.5f);
/*
    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }
    */

    register_all_packages();


    initGlobalSprites();

    auto scene = TitleScene::createScene();
    director->runWithScene(scene);

    return true;
}


// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}


// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}


void AppDelegate::initGlobalSprites()
{
  auto spriteCache = SpriteFrameCache::getInstance();
  spriteCache->addSpriteFramesWithFile(Globals::fileNameSpriteSheet);

  GraphicComponent*  graphic;
  PhysicComponent*   physic;
  ColliderComponent* collider;
  //InputComponent*    input;
  GameObject*        gameObject;
  cocos2d::Rect      colliderRect;

  //Add title screens to spawner
  graphic = new GraphicComponent(Globals::fileNameScreenTitle);
  graphic->setAnchorPoint(Vec2::ZERO);
  gameObject = new GameObject(graphic);
  Globals::spawner.addPrototype(gameObject, Globals::screenTitle);

  graphic = new GraphicComponent(Globals::fileNameScreenHowToPlay);
  graphic->setAnchorPoint(Vec2::ZERO);
  gameObject = new GameObject(graphic);
  Globals::spawner.addPrototype(gameObject, Globals::screenHowToPlay);

  graphic = new GraphicComponent(Globals::fileNameScreenHighScores);
  graphic->setAnchorPoint(Vec2::ZERO);
  gameObject = new GameObject(graphic);
  Globals::spawner.addPrototype(gameObject, Globals::screenHighScores);


  //Add backgrounds to spawner
  graphic = new GraphicComponent(Globals::fileNameBackSky);
  graphic->setAnchorPoint(Vec2::ZERO);
  gameObject = new GameObject(graphic);
  Globals::spawner.addPrototype(gameObject, Globals::backSky);

  graphic = new GraphicComponent(Globals::fileNameBackEarth);
  graphic->setAnchorPoint(Vec2::ZERO);
  gameObject = new GameObject(graphic);
  Globals::spawner.addPrototype(gameObject, Globals::backEarth);


  //Add game elements to spawner
  float baseElementHeight = 95.0f;
  float baseElementWidth;
  float colliderWidthSubtracton = 10;
  //Base Window
  physic = new PhysicComponent(Globals::Gravity);
  graphic = new GraphicComponent(Globals::fileNameElementWindow);
  cocos2d::Vec2 anchorBottomCenter{ Vec2(0.5f, 0.0f) };
  graphic->setAnchorPoint(anchorBottomCenter);
  baseElementWidth = graphic->getNode()->getContentSize().width - colliderWidthSubtracton;
  colliderRect = Rect( colliderWidthSubtracton / 2, 0, baseElementWidth, baseElementHeight );
  collider = new BoxCollider(colliderRect, graphic->getNode());
  gameObject = new GameObject(graphic, physic, collider);
  gameObject->setTag(ELEMENT_FREE);
  Globals::spawner.addPrototype(gameObject, Globals::elementWindow);

  //Balcons
  gameObject = Globals::spawner.spawn(Globals::elementWindow); //using "element-window" as prototype
  graphic = new GraphicComponent(Globals::fileNameElementBalconBlue);
  graphic->setAnchorPoint(anchorBottomCenter);
  gameObject->setGraphic(graphic);
  Globals::spawner.addPrototype(gameObject, Globals::elementBalconBlue);

  gameObject = Globals::spawner.spawn(Globals::elementWindow); //using "element-window" as prototype
  graphic = new GraphicComponent(Globals::fileNameElementBalconGreen);
  graphic->setAnchorPoint(anchorBottomCenter);
  gameObject->setGraphic(graphic);
  Globals::spawner.addPrototype(gameObject, Globals::elementBalconGreen);

  gameObject = Globals::spawner.spawn(Globals::elementWindow); //using "element-window" as prototype
  graphic = new GraphicComponent(Globals::fileNameElementBalconOrange);
  graphic->setAnchorPoint(anchorBottomCenter);
  gameObject->setGraphic(graphic);
  Globals::spawner.addPrototype(gameObject, Globals::elementBalconOrange);

  //Doors
  gameObject = Globals::spawner.spawn(Globals::elementWindow); //using "element-window" as prototype
  graphic = new GraphicComponent(Globals::fileNameElementDoorBlue);
  graphic->setAnchorPoint(anchorBottomCenter);
  gameObject->setGraphic(graphic);
  Globals::spawner.addPrototype(gameObject, Globals::elementDoorBlue);

  gameObject = Globals::spawner.spawn(Globals::elementWindow); //using "element-window" as prototype
  graphic = new GraphicComponent(Globals::fileNameElementDoorGreen);
  graphic->setAnchorPoint(anchorBottomCenter);
  gameObject->setGraphic(graphic);
  Globals::spawner.addPrototype(gameObject, Globals::elementDoorGreen);

  gameObject = Globals::spawner.spawn(Globals::elementWindow); //using "element-window" as prototype
  graphic = new GraphicComponent(Globals::fileNameElementDoorOrange);
  graphic->setAnchorPoint(anchorBottomCenter);
  gameObject->setGraphic(graphic);
  Globals::spawner.addPrototype(gameObject, Globals::elementDoorOrange);

  //Tops
  gameObject = Globals::spawner.spawn(Globals::elementWindow); //using "element-window" as prototype

  graphic = new GraphicComponent(Globals::fileNameElementTopBlue);
  graphic->setAnchorPoint(anchorBottomCenter);
  gameObject->setGraphic(graphic);

  colliderRect = Rect((graphic->getNode()->getContentSize().width - baseElementWidth) / 2, 0, baseElementWidth, 95.0f); //create new collider for Tops
  collider = new BoxCollider(colliderRect, graphic->getNode());
  gameObject->setCollider(collider);
  Globals::spawner.addPrototype(gameObject, Globals::elementTopBlue);

  gameObject = Globals::spawner.spawn(Globals::elementTopBlue); //using "element-top-blue" as prototype
  graphic = new GraphicComponent(Globals::fileNameElementTopGreen);
  graphic->setAnchorPoint(anchorBottomCenter);
  gameObject->setGraphic(graphic);
  Globals::spawner.addPrototype(gameObject, Globals::elementTopGreen);

  gameObject = Globals::spawner.spawn(Globals::elementTopBlue); //using "element-top-blue" as prototype
  graphic = new GraphicComponent(Globals::fileNameElementTopOrange);
  graphic->setAnchorPoint(anchorBottomCenter);
  gameObject->setGraphic(graphic);
  Globals::spawner.addPrototype(gameObject, Globals::elementTopOrange);



  ////Add grass
  graphic = new GraphicComponent(Globals::fileNameElementStandGrass);
  colliderRect = Rect(0, 0, graphic->getNode()->getContentSize().width, 50.0f);
  collider = new BoxCollider(colliderRect, graphic->getNode());
  graphic->setAnchorPoint(anchorBottomCenter);
  gameObject = new GameObject(graphic, nullptr, collider);
  gameObject->setTag(ELEMENT_FREE);
  Globals::spawner.addPrototype(gameObject, Globals::elementStandGrass);

  //Add hat

  ////
  graphic = new GraphicComponent(Globals::fileNameElementHat);
  graphic->setAnchorPoint(Vec2(0.5f, 1.0f));
  gameObject = new GameObject(graphic);
  gameObject->setTag(ROPE);
  Globals::spawner.addPrototype(gameObject, Globals::elementHat);

}
