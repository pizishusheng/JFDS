//
//  GuardRole.cpp
//  JFDS
//
//  Created by Tao on 2016/12/8.
//
//

#include "GuardRole.hpp"


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
   // setScale(0.5f);
    m_guard = pGuard;
    
    initAnimationWithType(GuardType::GUARD_TWO);
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











