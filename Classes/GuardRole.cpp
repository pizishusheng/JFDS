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
    this->setPosition(m_guard->getBorn());
    initAnimationWithType(GuardType::GUARD_TWO);
    initSector(m_guard->getVisonL(), m_guard->getVisonR(), m_guard->getVisonA());
    
    Rect frame = this->getSpriteFrame()->getRect();
    CCLOG("frame=%f-----%f", frame.size.width, frame.size.height);
    log("size = %f-----%f", this->getContentSize().width, this->getContentSize().height);
    log("bounding = %f -------%f", this->getBoundingBox().size.width, this->getBoundingBox().size.height);
    
//    auto test = Sprite::create("CloseNormal.png");
//    test->setPosition(this->getContentSize() * 0.5);
//    this->addChild(test);
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
            sfName = "magician_b_walk_00.png";
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
    for (int i = 0; i < 16; i++) {
        animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("magician_b_walk_%02d.png", i)->getCString()));
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
    auto speed = m_guard->getSpeed();
    auto time = diff.getLength() / speed;
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











