#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    bool onTouchBegan(Touch *pTouch, Event *pEvent);
    void onTouchMoved(Touch *touch, Event *unused_event);
    void menuCloseCallback(cocos2d::Ref* pSender);
    void loadBtnCallback(cocos2d::Ref* pSender);
    void readBtnCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(HelloWorld);
private:
    Vec2 m_begin;
    experimental::TMXTiledMap *m_fastMap;
};

#endif // __HELLOWORLD_SCENE_H__
