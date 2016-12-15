//
//  Guard.hpp
//  JFDS
//
//  Created by Tao on 2016/12/5.
//
//

#ifndef Guard_hpp
#define Guard_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "LoadConfigManager.hpp"

USING_NS_CC;

class Path : public Ref
{
public:
    
    ~Path();
    friend class LoadConfigManager;
    CREATE_FUNC(Path);
    bool init();
    Vec2 getFaceDirection();
private:
    Vec2 m_faceDirection;
    float m_staytime;
};

class Guard : public Ref
{
public:
    ~Guard();
    friend class LoadConfigManager;
    CREATE_FUNC(Guard);
    bool init();
    uint getType();
    float getSpeed();
    Vec2 getBorn();
    float getVisonL();
    float getVisonR();
    float getVisonA();
    std::vector<Path*> getPath();
protected:
    uint m_type;
    float m_speed;
    Vec2 m_born;
    float m_visonL;
    float m_visonR;
    float m_visonA;
    std::vector<Path*> m_path;
};

#endif /* Guard_hpp */
