//
//  GuardRole.cpp
//  JFDS
//
//  Created by Tao on 2016/12/8.
//
//

#include "GuardRole.hpp"


GuardRole* GuardRole::creatWithGuard(Guard &pGuard)
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

bool GuardRole::initWithGuard(Guard &pGuard)
{
    m_guard = &pGuard;
    
    
    
    
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
}















