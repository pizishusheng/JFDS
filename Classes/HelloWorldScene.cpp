#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "LoadConfigManager.hpp"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 center = Vec2(visibleSize.width*0.5 + origin.x, visibleSize.height*0.5 + origin.y);
    
    // 加载地图
    m_map = TMXTiledMap::create("res/text1-1.tmx");
    m_map->setAnchorPoint(Vec2(0.5f, 0.5f));
    m_map->setPosition(center);
    //this->addChild(m_map, 0);
    
   // m_begin = Vec2(0, 0);
    
    MenuItemImage* closeItem = MenuItemImage::create("CloseNormal.png", "CloseNormal.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    MenuItemImage* readItem = MenuItemImage::create("CloseSelected.png", "CloseSelected.png", CC_CALLBACK_1(HelloWorld::readBtnCallback, this));
    readItem->setPosition(center);
    
    auto menu = Menu::create(closeItem, readItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

bool HelloWorld::onTouchBegan(Touch *pTouch, Event *pEvent)
{
    m_begin = pTouch->getLocationInView();
    return false;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *unused_event)
{
    float prePosX = m_begin.x;
    float prePosY = m_begin.y;
    
    // 当前触摸点坐标
    float curPosX = touch->getLocationInView().x;
    float curPosY = touch->getLocationInView().y;
    
    // 计算触摸点与开始触摸时的差值
    float distanceX = curPosX - prePosX;
    float distanceY = curPosY - prePosY;
    // 地图之前的坐标
    Vec2 preMap = m_map->getPosition();
    Vec2 curMap = Vec2(preMap.x + distanceX, preMap.y);
    
    if (curMap.x > Director::getInstance()->getVisibleSize().width) {
        return;
    }
   
    if(std::abs(distanceX) > 1){
        m_map->setPosition(curMap);
        m_begin = curMap;
    }
    
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    LoadConfigManager::getInstance()->loadChapterConfig("chapter/chaper_1.json");
}

void HelloWorld::readBtnCallback(Ref* pSender)
{
    vector<Guard*> guardVector = LoadConfigManager::getInstance()->getChapterConfig();
    for (auto itr = guardVector.begin(); itr != guardVector.end(); itr++) {
        Guard *guard = *itr;
        log("type=%u\n", guard->getType());
    }
}
