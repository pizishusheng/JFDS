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


/*************Guard----end*****************/
