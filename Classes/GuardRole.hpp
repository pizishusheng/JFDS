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
    virtual void update(float delta);
    virtual void onEnter();
    virtual void onExit();
    
    static GuardRole* creatWithGuard(Guard *pGuard);
    bool initWithGuard(Guard *pGuard);
    void initAnimationWithType(GuardType pType);
    void initSector(float pL, float pR, float pA);
    void updateNextPostion(float delta);
    
    void walkTo(float delta);
    Animate* getAnimationWithType(GuardActionType pType);
private:
    Guard *m_guard;
    string m_name;
    int m_animationNum;
    std::vector<int> m_animationFrameNum;
    float m_stayTime;
    bool m_isAnimation;
    Vec2 m_nextPosition;
    int m_currentPathIndex;
};

#endif /* GuardRole_hpp */
