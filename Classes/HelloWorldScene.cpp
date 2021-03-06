#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "LoadConfigManager.hpp"
#include "GuardRole.hpp"

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
    m_fastMap = experimental::TMXTiledMap::create("res/text1-1.tmx");//TMXTiledMap::create("res/text1-1.tmx");
    m_fastMap->setAnchorPoint(Vec2(0.5f, 0.5f));
    m_fastMap->setPosition(center);
    this->addChild(m_fastMap, 0);
    
    m_begin = Vec2(0, 0);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile
    ("res/Guard.plist", "res/Guard.pvr.ccz");
    
    MenuItemImage* closeItem = MenuItemImage::create("CloseNormal.png", "CloseNormal.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    auto loadItem = MenuItemFont::create("加载数据", CC_CALLBACK_1(HelloWorld::loadBtnCallback, this));
    loadItem->setPosition(center - Vec2(100, 0));

    auto readItem = MenuItemFont::create("创建守卫", CC_CALLBACK_1(HelloWorld::readBtnCallback, this));
    readItem->setPosition(center + Vec2(100, 0));
    
    auto menu = Menu::create(closeItem, loadItem, readItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
//    auto test = Sprite::create("CloseNormal.png");
//    Size mapSize = m_fastMap->getMapSize();
//    Size tileSize = m_fastMap->getTileSize();
//    Size contentSize = m_fastMap->getContentSize();
//    log("mapSize -----x=%f, y=%f", mapSize.width, mapSize.height);
//    log("tileSize ----x=%f, y=%f", tileSize.width, tileSize.height);
//    log("contentSize -----x=%f, y=%F", contentSize.width, contentSize.height);
//    test->setPosition(Vec2(436, 914));
//    m_fastMap->addChild(test, 2);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

bool HelloWorld::onTouchBegan(Touch *pTouch, Event *pEvent)
{
    Vec2 begin = pTouch->getLocation();
    return true;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *unused_event)
{
    auto diff = touch->getDelta();
    // 地图之前的坐标
    Vec2 preMap = m_fastMap->getPosition();
    Vec2 curMap = preMap + diff;
    m_fastMap->setPosition(curMap);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::loadBtnCallback(cocos2d::Ref *pSender)
{
    LoadConfigManager::getInstance()->loadChapterConfig("chapter/chaper_1.json");
}

void HelloWorld::readBtnCallback(Ref* pSender)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 center = Vec2(visibleSize.width*0.5 + origin.x, visibleSize.height*0.5 + origin.y);
    vector<Guard*> guardVector = LoadConfigManager::getInstance()->getChapterConfig();
    int i = 1;
    for (auto itr = guardVector.begin(); itr != guardVector.end(); itr++) {
        Guard *guard = *itr;
        log("type=%u\n", guard->getType());
        GuardRole *role = GuardRole::creatWithGuard(guard);
        role->setTag(i++);
        m_fastMap->addChild(role, 99);
    }
}
