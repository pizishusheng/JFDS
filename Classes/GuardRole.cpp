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
    setScale(0.5f);
    m_guard = pGuard;
    
    initAnimationWithType(GuardType::GUARD_TWO);
    playAnimation(GuardActionType::ACTION_WALK);
    return true;
}

void GuardRole::initAnimationWithType(GuardType pType)
{
    string sfName = "";
    int animationFrameNum[5] ={4, 4, 4, 2, 4};
    int animationFrameNum2[5] ={3, 3, 3, 2, 0};
    
    switch (pType) {
        case GuardType::GUARD_ONE:
            sfName = "player1-1-1.png";
            m_name = "player1";
            m_animationNum = 5;
            m_animationFrameNum.assign(animationFrameNum, animationFrameNum + 5);
            break;
        case GuardType::GUARD_TWO:
            sfName = "enemy1-1-1.png";
            m_name = "enemy1";
            m_animationNum = 4;
            m_animationFrameNum.assign(animationFrameNum2, animationFrameNum2 + 5);
            break;
        case GuardType::GUARD_THREE:
            sfName = "enemy2-1-1.png";
            m_name = "enemy2";
            m_animationNum = 4;
            m_animationFrameNum.assign(animationFrameNum2, animationFrameNum2 + 5);
            break;
    }
    this->initWithSpriteFrameName(sfName);
    auto animation = Animation::create();
    animation->setDelayPerUnit(0.2f);
    animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(sfName));
    AnimationCache::getInstance()->addAnimation(animation, "enemy1-walk");
}

void GuardRole::walkTo(cocos2d::Vec2 pDest)
{
    this->stopAllActions();
    auto curPos = this->getPosition();
    
    if (curPos.x > pDest.x) {
        this->setFlippedX(true);
    }else{
        this->setFlippedX(false);
    }
    
    auto diff = pDest - curPos;
    auto time = diff.getLength()/60;
    auto move = MoveTo::create(time, pDest);
    //lambda function
    auto func = [&]()
    {
        this->stopAllActions();
    };
    
    
    auto callback = CallFunc::create(func);
    auto _seq = Sequence::create(move, callback, nullptr);
    
    this->runAction(_seq);
}

void GuardRole::playAnimation(GuardActionType pType)
{
    if (pType == GuardActionType::ACTION_WALK) {
        auto animation = AnimationCache::getInstance()->getAnimation("enemy1-walk");
        auto animate = Animate::create(animation);
        
        auto sp = Spawn::create(animate, nullptr);
        auto ac = RepeatForever::create(sp);
        this->runAction(ac);
    }
}











