#include "SimpleAudioEngine.h"
#include "MainScene.h"
#include "CustomSprite.h"

MainScene::MainScene()
:m_dirType(KControllDirection::kPlayerControllDirection)
,m_player(nullptr)
,m_playerHead(nullptr)
,m_listener_touch(nullptr)
,m_isEnable(true)
{
    
}

MainScene::~MainScene()
{
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile
    ("ui.plist");
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile
    ("role.plist");

}

Scene* MainScene::createScene()
{
   
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("battlefield.mp3", true);
    

    auto scene = Scene::create();
    auto layer = MainScene::create();
    
    scene->addChild(layer);

    return scene;
}



bool MainScene::onTouchBegan(Touch* touch, Event* event)
{
    
    
    Vec2 pos = this->convertToNodeSpace(touch->getLocation());
    m_player->walkTo(pos);
    return  true;
}

bool MainScene::init()
{
    
    
    if (!Layer::init()) {
        
        return  false;
    }
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile
    ("ui.plist", "ui.pvr.ccz");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile
    ("role.plist", "role.pvr.ccz");

    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite* background = Sprite::create("background.png");
    background->setPosition(origin + visibleSize/2);
    this->addChild(background);
    m_player = Player::create(Player::PlayerType::PLAYER);
    m_player->setPosition(origin.x + m_player->getContentSize().width/2, origin.y + visibleSize.height/2);
    this->addChild(m_player);
    
    m_playerHead = CustomSprite::createWithPath("HearoHead.png");
    auto pos = Vec2(m_playerHead->getContentSize().width / 2, visibleSize.height - m_playerHead->getContentSize().height / 2);
    m_playerHead->setPosition(pos);
    m_playerHead->onTouchEnded = CC_CALLBACK_2(MainScene::moveControl, this);
    addChild(m_playerHead);
    
    m_listener_touch = EventListenerTouchOneByOne::create();
    m_listener_touch->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan,this);

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener_touch, this);
    
    initControler();
    
    
    
    return  true;
}



void MainScene::initControler()
{
    
    auto node = Node::create();
    
    auto up = CustomSprite::createWithPath("Up.jpg");
    up->onTouchEnded = CC_CALLBACK_2(MainScene::hit, this);
    node->addChild(up);
    up->setPosition(Vec2(100, 200));
    auto size = up->getContentSize();

    auto left = CustomSprite::createWithPath("Left.jpg");
    left->onTouchEnded = CC_CALLBACK_2(MainScene::walk, this);
    left->setPosition(Vec2(up->getPosition()- size));
    node->addChild(left);
    
    auto back = CustomSprite::createWithPath("Back.jpg");
    back->onTouchEnded = CC_CALLBACK_2(MainScene::back, this);
    back->setPosition(Vec2(up->getPositionX(), left->getPositionY()));
    node->addChild(back);
    
    
    auto down = CustomSprite::createWithPath("Down.jpg");
    down->onTouchEnded = CC_CALLBACK_2(MainScene::attack, this);
    down->setPosition(Vec2(back->getPositionX(), back->getPositionY() - size.height ));
    node->addChild(down);
    
    auto right = CustomSprite::createWithPath("Right.jpg");
    right->onTouchEnded = CC_CALLBACK_2(MainScene::skill, this);
    right->setPosition(Vec2(left->getPositionX() + 2 * size.width, left->getPositionY()));
    node->addChild(right);
    
    
    //node->setPosition(;
    this->addChild(node);
    m_controller = node;

    
}






void MainScene::walk(Touch *touch, Event *event)
{
    m_player->playAnimationForever(KActionType::kWalk);
}


void MainScene::attack(Touch *touch, Event *event)
{
    m_player->playAnimationForever(KActionType::KAttack);

}

void MainScene::hit(Touch *touch, Event *event)
{
    m_player->playAnimationForever(KActionType::KHit);

}

void MainScene::skill(Touch *touch, Event *event)
{
    m_player->playAnimationForever(KActionType::kSkill);
   // CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("combat41.mp3");


}

void MainScene::back(Touch *touch, Event *event)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    auto scene = StartScene::createScene();
    Director::getInstance()->replaceScene(scene);
}


void MainScene::moveControl(Touch *touch, Event *event)
{
    if(!m_isEnable)
        return;
    m_isEnable = false;
    Vec2 pos;
    CallFunc *f = nullptr;
    if(m_dirType == KControllDirection::KNormalDirection)
    {
        pos = Vec2(0, 0);
         f = CallFunc::create([this](){
            m_dirType = KControllDirection::kPlayerControllDirection;
             m_isEnable = true;

        });
        
    }
    else
    {
        pos = Vec2(-185, 0);
        f = CallFunc::create([this](){
            m_dirType = KControllDirection::KNormalDirection;
            m_isEnable = true;
        });

    }
    
    auto action = MoveTo::create(1.0f, pos);
    auto seq = Sequence::create(action, f, NULL);
    m_controller->runAction(seq);
    
    
}


