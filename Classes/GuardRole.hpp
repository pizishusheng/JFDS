//
//  GuardRole.hpp
//  JFDS
//
//  Created by Tao on 2016/12/8.
//
//

#ifndef GuardRole_hpp
#define GuardRole_hpp

#include <stdio.h>
#include "Guard.hpp"
#include "editor-support/cocostudio/CCArmature.h"

using namespace cocostudio;

enum class GuardType
{
    GUARD_ONE,
    GUARD_TWO,
    GUARD_THREE
};

enum class GuardActionType
{
    ACTION_IDLE,
    ACTION_WALK
};

class Guard;

class GuardRole : public Sprite
{
public:
    static GuardRole* creatWithGuard(Guard *pGuard);
    bool initWithGuard(Guard *pGuard);
    void initAnimationWithType(GuardType pType);
    void initSector(float pL, float pR, float pA);
    void initWalkAction();
    void initFrameAnimation();
    
    void autoWalk();
    void walkTo(Vec2 pDest);
    Animate* getAnimationWithType(GuardActionType pType);
private:
    Guard *m_guard;
    string m_name;
    int m_animationNum;
    std::vector<int> m_animationFrameNum;
    float m_stayTime;
    Vector<FiniteTimeAction*> m_walkAction;
};

#endif /* GuardRole_hpp */
