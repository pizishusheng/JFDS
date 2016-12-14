//
//  DrawSector.cpp
//  BattleDemo
//
//  Created by Tao on 2016/11/17.
//
//

#include "DrawSector.hpp"

void DrawSector::drawSolidSector(const Vec2 &orign,const Vec2 &beginVec, const float radius1, const float radius2, const float radian, const int segments, const cocos2d::Color4F &color)
{
    float angle = atanf(beginVec.x / beginVec.y);
    angle = beginVec.y<0? angle+M_PI: angle;
    float coef = radian/segments;
    Vec2 *vertices1 = new (std::nothrow) Vec2[segments+1];
    if( ! vertices1 )
        return;
    
    Vec2 *vertices2 = new (std::nothrow) Vec2[segments+1];
    if( ! vertices2 )
        return;
    
    for(unsigned int i = 0;i <= segments; i++)
    {
        float rads = i*coef;
        GLfloat j = radius1 * cosf(rads + angle) + orign.y;
        GLfloat k = radius1 * sinf(rads + angle) + orign.x;
        
        vertices1[i].x = k;
        vertices1[i].y = j;
        
        GLfloat l = radius2 * cosf(rads + angle) + orign.y;
        GLfloat m = radius2 * sinf(rads + angle) + orign.x;
        
        vertices2[i].x = m;
        vertices2[i].y = l;
    }
    
    V2F_C4B_T2F_Triangle *triangles = new V2F_C4B_T2F_Triangle[segments*2];
    
    int triCount = 0;
    for (int i=0; i<segments; i++) {
        triangles[triCount].a.vertices = vertices1[i];
        triangles[triCount].b.vertices = vertices2[i];
        triangles[triCount++].c.vertices = vertices2[i+1];
        
        triangles[triCount].a.vertices = vertices1[i];
        triangles[triCount].b.vertices = vertices1[i+1];
        triangles[triCount++].c.vertices = vertices2[i+1];
    }
    
    for (int i=0; i<segments*2; i++) {
        drawTriangle(triangles[i].a.vertices, triangles[i].b.vertices, triangles[i].c.vertices, color);
    }
    
    CC_SAFE_DELETE_ARRAY(vertices1);
    CC_SAFE_DELETE_ARRAY(vertices2);
    CC_SAFE_DELETE_ARRAY(triangles);
}
