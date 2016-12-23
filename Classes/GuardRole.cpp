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
    
    m_isAnimation = true;
    m_currentPathIndex = 0;
    m_guard = pGuard;
    this->setPosition(m_guard->getBorn() + Vec2(0, 25));
    initAnimationWithType(GuardType::GUARD_TWO);
    initSector(m_guard->getVisonL(), m_guard->getVisonR(), m_guard->getVisonA());
    this->scheduleOnce(schedule_selector(GuardRole::updateNextPostion), 3.0f);
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

void GuardRole::updateNextPostion(float delta)
{
    vector<Path*> pathVec = m_guard->getPath();
    if (m_currentPathIndex < pathVec.size()) {
        m_nextPosition = pathVec.at(m_currentPathIndex)->getFaceDirection();
        m_stayTime = pathVec.at(m_currentPathIndex)->getStayTime();
        m_isAnimation = false;
    }else{
        m_currentPathIndex--;
        m_isAnimation = true;
    }
}

void GuardRole::walkTo(float delta)
{
    this->stopAllActions();
    auto curPos = this->getPosition();
    auto pDest = Vec2(m_nextPosition.x, 1800 - m_nextPosition.y);
    log("walk to (%f, %f)", pDest.x, pDest.y);
    
    auto diff = pDest - curPos;
    auto speed = m_guard->getSpeed();
    auto time = diff.getLength() / speed;
    auto move = MoveTo::create(time, pDest);
    
    auto func = [&]()
    {
        this->stopAllActions();
        m_isAnimation = false;
        updateNextPostion(1.0f);
    };
    
    auto callback = CallFunc::create(func);
    auto seq = Sequence::create(move, callback, nullptr);
    
    auto animate = getAnimationWithType(GuardActionType::ACTION_WALK);
    if(animate == nullptr)
        return;
    animate->retain();
    auto sp = Spawn::create(animate, nullptr);
    auto ac = RepeatForever::create(sp);
    
    this->runAction(seq);
    this->runAction(ac);
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

void GuardRole::update(float delta)
{
    if (!m_isAnimation) {
        this->scheduleOnce(schedule_selector(GuardRole::walkTo), m_stayTime);
        m_isAnimation = true;
        m_currentPathIndex++;
    }
}

void GuardRole::onEnter()
{
    Sprite::onEnter();
    this->scheduleUpdate();
}

void GuardRole::onExit()
{
    this->unscheduleUpdate();
    Sprite::onExit();
}









