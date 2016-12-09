#ifndef __MainScene__
#define __MainScene__

#include "cocos2d.h"
#include "Player.h"
#include "StartScene.h"
USING_NS_CC;
class CustomSprite;
class MainScene : public cocos2d::Layer
{
public:
    
    enum class KControllDirection
    {
        KNormalDirection,
        kPlayerControllDirection,        
    };
    
    MainScene();
    virtual ~MainScene();
    static cocos2d::Scene* createScene();

  
    virtual bool init();  
    
    
    CREATE_FUNC(MainScene);
    
    void initControler();
    
    bool onTouchBegan(Touch* touch, Event* event);
    
    void walk(Touch *touch, Event *event);
    
    void attack(Touch *touch, Event *event);
    
    void hit(Touch *touch, Event *event);
    
    void skill(Touch *touch, Event *event);

    void back(Touch *touch, Event *event);
    
    void moveControl(Touch *touch, Event *event);




    

private:
    EventListenerTouchOneByOne *m_listener_touch;
    
    
    KControllDirection m_dirType;
    Node *m_controller;    
    CustomSprite *m_playerHead;
    Player *m_player;
    bool m_isEnable;
};

#endif




