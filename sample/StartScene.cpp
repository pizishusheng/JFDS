//
//  StartScene.cpp
//  MyBrave
//
//  Created by Mr Gan on 12/12/14.
//
//

#include "StartScene.h"
#include "VisibleRect.h"
#include "CustomTool.h"
#include "MainScene.h"
#include "CustomSprite.h"


StartScene::StartScene(){}
StartScene::~StartScene(){
    
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile
    ("ui.plist");
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile
    ("role.plist");
    
}

Scene* StartScene::createScene()
{
    
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("C14.mp3", true);
    

    auto scene = Scene::create();
    auto layer = StartScene::create();
    
    
    scene->addChild(layer);
    
    return scene;
    
    
}

bool StartScene::init()
{
    
    if (!Layer::init()) {
        return  false;
        
    }
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile
    ("ui.plist", "ui.pvr.ccz");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile
    ("role.plist", "role.pvr.ccz");
    
    
    
    auto bg = Sprite::create("start-bg.jpg");
    
    bg->setPosition(VisibleRect::center());
    addChild(bg);
    
    
    auto start = CustomSprite::createWithFrameName("start1.png");
    start->setPosition(Vec2(480, 200));
    start->onTouchEnded = CC_CALLBACK_2(StartScene::onStart,this);
    addChild(start);
    
    return true;
    
}
void StartScene::onStart(Touch *touch, Event *event)
{
	log("StartLayer::onStart");
	auto scene = MainScene::createScene();
	Director::getInstance()->replaceScene(scene);
}



