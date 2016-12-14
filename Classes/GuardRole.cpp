//
//  GuardRole.cpp
//  JFDS
//
//  Created by Tao on 2016/12/8.
//
//

#include "GuardRole.hpp"
#include "DrawSector.hpp"


GuardRole* GuardRole::creatWithGuard(Guard *pGuard)
{
    GuardRole *pRet = new GuardRole();
    if (pRet && pRet->initWithGuard(pGuard)) {
        pRet->autorelease();
        return pRet;
    }
    delete pRet;
    pRet = nullptr;
    return nullptr;
}

bool GuardRole::initWithGuard(Guard *pGuard)
{
    //setScale(0.7f);
    m_guard = pGuard;
    this->setAnchorPoint(Vec2(0.5f, 0.5f));
    initAnimationWithType(GuardType::GUARD_TWO);
    //initSector();
    
    auto test = Sprite::create("CloseNormal.png");
    test->setPosition(this->getContentSize() * 0.5);
    this->addChild(test);
    return true;
}

void GuardRole::initAnimationWithType(GuardType pType)
{
    string sfName = "";
    
    switch (pType) {
        case GuardType::GUARD_ONE:
            sfName = "player1-1-1.png";
            m_name = "player1";
            break;
        case GuardType::GUARD_TWO:
            sfName = "enemy1-1-1.png";
            m_name = "enemy1";
            break;
        case GuardType::GUARD_THREE:
            sfName = "enemy2-1-1.png";
            m_name = "enemy2";
            break;
    }
    this->initWithSpriteFrameName(sfName);
    auto animation = Animation::create();
    animation->setDelayPerUnit(0.2f);
    for (int i = 1; i < 4; i++) {
        animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("enemy1-1-%d.png", i)->getCString()));
    }
    AnimationCache::getInstance()->addAnimation(animation, "enemy1-walk");
}

void GuardRole::initSector()
{
    auto drawNode = DrawSector::create();
    drawNode->setAnchorPoint(Vec2(0, 0));
    float radian = 60.0f;
    //扇形半径
    float RADIUS = 100.0f;
    //坐标偏移量
    float beginVec = 0.0f;
    //颜色
    float r = rand_0_1();
    float g = rand_0_1();
    float b = rand_0_1();
    
    drawNode->drawSolidSector(Vec2(100, 100), Vec2(sin(beginVec), cosf(beginVec)), RADIUS, 0, radian * M_PI / 180.0f, 200, Color4F(r, g, b, 1));
    //drawNode->setPosition(this->getContentSize());
    this->addChild(drawNode, 88);
}

void GuardRole::walkTo(cocos2d::Vec2 pDest)
{
    this->stopAllActions();
    auto curPos = this->getPosition();
    
    if (curPos.x > pDest.x) {
       // this->setFlippedX(true);
        this->setScaleX(this->getScaleX() * -1);
    }else{
        this->setFlippedX(false);
    }
    
    auto diff = pDest - curPos;
    auto time = diff.getLength()/6;
    auto move = MoveTo::create(time, pDest);
    //lambda function
    auto func = [&]()
    {
        this->stopAllActions();
    };
    
    auto callback = CallFunc::create(func);
    auto seq = Sequence::create(move, callback, nullptr);
    
    auto animate = getAnimationWithType(GuardActionType::ACTION_WALK);
    if(animate == nullptr)
        return;
    animate->retain();
    auto sp = Spawn::create(animate, nullptr);
    auto ac = RepeatForever::create(sp);
    this->runAction(ac);
    this->runAction(seq);
}

Animate* GuardRole::getAnimationWithType(GuardActionType pType)
{
    Animation* animation = nullptr;
    Animate* animate = nullptr;
    if (pType == GuardActionType::ACTION_WALK){
        animation = AnimationCache::getInstance()->getAnimation("enemy1-walk");
        animate = Animate::create(animation);
    }
    return animate;
}











