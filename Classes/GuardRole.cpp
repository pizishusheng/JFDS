//
//  GuardRole.cpp
//  JFDS
//
//  Created by Tao on 2016/12/8.
//
//

#include "GuardRole.hpp"
#include "DrawSector.hpp"
#include "editor-support/cocostudio/CCArmatureDataManager.h"

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
    if(pGuard == nullptr)
        return false;
    
    m_guard = pGuard;
    this->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->setPosition(m_guard->getBorn());
    initAnimationWithType(GuardType::GUARD_TWO);
    initSector(m_guard->getVisonL(), m_guard->getVisonR(), m_guard->getVisonA());
    initWalkAction();
    //autoWalk();
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
            sfName = "monster1_f1.png";
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
        animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("monster1_f%d.png", i)->getCString()));
    }
    AnimationCache::getInstance()->addAnimation(animation, "enemy1-walk");
}

void GuardRole::initSector(float pL, float pR, float pA)
{
    auto drawNode = DrawSector::create();
    drawNode->setAnchorPoint(Vec2(0, 0));
    float radian = pL;    // 扇形弧度
    float RADIUS = pR;   //扇形半径
    float beginVec = pA * M_PI / 180.0f;  //  角度

    drawNode->drawSolidSector(Vec2(0, -15), Vec2(sin(beginVec), cosf(beginVec)), RADIUS, 0, radian * M_PI / 180.0f, 200, Color4F(118, 274, 120, 0.5));
    drawNode->setPosition(this->getContentSize() * 0.5);
    this->addChild(drawNode, 88);
}

void GuardRole::initWalkAction()
{
    vector<Path*> pathVec = m_guard->getPath();
    
    for (auto itr = pathVec.begin(); itr != pathVec.end(); ++itr) {
        Path *path = *itr;
        log("x=%f ------ y=%f", path->getFaceDirection().x, path->getFaceDirection().y);
        auto callback = CallFunc::create(CC_CALLBACK_0(GuardRole::walkTo, this, path->getFaceDirection()));
        m_walkAction.pushBack(callback);
        this->m_stayTime = path->getStayTime();
    }
    Sequence* squeue = Sequence::create(m_walkAction);
    this->runAction(squeue);
}

void GuardRole::walkTo(cocos2d::Vec2 pDest)
{
    log("walk to (%f, %f)", pDest.x, pDest.y);
    this->stopAllActions();
    auto curPos = this->getPosition();
    
    if (curPos.x > pDest.x) {
        this->setFlippedX(true);
    }else{
        this->setFlippedX(false);
    }
    
    auto diff = pDest - curPos;
    auto speed = m_guard->getSpeed();
    auto time = diff.getLength() / speed;
    auto move = MoveTo::create(time, pDest);
    
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












