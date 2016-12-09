//
//  StartScene.h
//  MyBrave
//
//  Created by Mr Gan on 12/12/14.
//
//

#ifndef __MyBrave__StartScene__
#define __MyBrave__StartScene__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class StartScene : public Layer
{
    
public:
    StartScene();
    virtual ~StartScene();
    static Scene* createScene();
    CREATE_FUNC(StartScene);
    virtual bool init();
    
    void onStart(Touch *touch, Event *event);
    
   // void onStart(Touch *touch,  Event *event);
    
};






#endif /* defined(__MyBrave__StartScene__) */
