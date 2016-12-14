//
//  DrawSector.hpp
//  BattleDemo
//
//  Created by Tao on 2016/11/17.
//
//

#ifndef DrawSector_hpp
#define DrawSector_hpp

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class DrawSector : public cocos2d::DrawNode
{
public:
    /*
     *origin: 起始点左边
     *beginVec: 
     **/
    CREATE_FUNC(DrawSector);
    /*
     * orign : 起点
     * beginVec
     */
    void drawSolidSector(const Vec2 &orign,const Vec2 &beginVec, const float radius1, const float radius2, const float radian, const int segments, const cocos2d::Color4F &color);
};

#endif /* DrawSector_hpp */
