//
//  Guard.cpp
//  JFDS
//
//  Created by Tao on 2016/12/5.
//
//

#include "Guard.hpp"

/*************Path----begin*****************/
Path::~Path()
{
    log("执行path  析构函数！！！");
}

bool Path::init()
{
    return true;
}

Vec2 Path::getFaceDirection()
{
    return m_faceDirection;
}
/*************Path----end*****************/


/*************Guard----begin*****************/
Guard::~Guard()
{
    log("执行guard   析构函数！！！");
}

bool Guard::init()
{
    return true;
}

uint Guard::getType()
{
    return m_type;
}

float Guard::getSpeed()
{
    return m_speed;
}

Vec2 Guard::getBorn()
{
    return m_born;
}

vector<Path*> Guard::getPath()
{
    return m_path;
}

float Guard::getVisonL()
{
    return m_visonL;
}

float Guard::getVisonR()
{
    return m_visonR;
}

float Guard::getVisonA()
{
    return m_visonA;
}

/*************Guard----end*****************/
