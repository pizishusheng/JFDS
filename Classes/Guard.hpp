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
#include "Chapter.hpp"

USING_NS_CC;

class Path : public Ref
{
public:
    friend class Guard;
    CREATE_FUNC(Path);
    bool init();
private:
    Vec2 m_faceDirection;
    float m_staytime;
};

class Guard : public Ref
{
public:
    friend class Chapter;
    CREATE_FUNC(Guard);
    bool init();
protected:
    uint m_type;
    float m_speed;
    Vec2 m_born;
    float m_visonL;
    float m_visonR;
    std::vector<Path> m_path;
};

#endif /* Guard_hpp */
