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

enum class GuardType
{
    GUARD_ONE,
    GUARD_TWO,
    GUARD_THREE
};

class Guard;

class GuardRole : public Sprite
{
public:
    GuardRole* creatWithGuard(Guard &pGuard);
    bool initWithGuard(Guard &pGuard);
    void initAnimationWithType(GuardType pType);
private:
    Guard *m_guard;
    string m_name;
    int m_animationNum;
    std::vector<int> m_animationFrameNum;
};

#endif /* GuardRole_hpp */
