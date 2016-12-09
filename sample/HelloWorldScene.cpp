#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    
    //SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui.plist", "ui.pvr.ccz");
    
    
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("background.png");
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
   this->addChild(sprite, 0);
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" iconad to exit the progress. it's an autorelease object
//    auto startGame = MenuItemImage::create();
//    startGame->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("start1.png"));
//    startGame->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("start2.png"));
//
//    startGame->setCallback(CC_CALLBACK_1(HelloWorld::startGame, this));
//    startGame->setPosition(origin + visibleSize / 2);
                                //, 200));

    // create menu, it's an autorelease object
   // auto menu = Menu::createWithItem(startGame);
//    menu->setPosition(Vec2::ZERO);
//    addChild(menu);
    
   // auto  = MenuItemImage::create(start1.png, NULL, CC_CALLBACK_1(HelloWorld::startGame));
    
    
    
    

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
   // auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    //label->setPosition(Vec2(origin.x + visibleSize.width/2,
                          //  origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
 //   this->addChild(label, 1);

   
    
    return true;
}


void HelloWorld::startGame(cocos2d::Ref *pSender)
{
    
    
    
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
