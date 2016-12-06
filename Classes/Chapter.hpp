//
//  Chapter.hpp
//  JFDS
//
//  Created by Tao on 2016/12/6.
//
//

#ifndef Chapter_hpp
#define Chapter_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Guard.hpp"

USING_NS_CC;
using namespace std;

class Guard;

class Chapter : public Ref
{
public:
    CREATE_FUNC(Chapter);
    bool init();
    
private:
    vector<Guard*> m_guardVector;
};

#endif /* Chapter_hpp */
