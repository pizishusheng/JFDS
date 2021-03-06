//
//  LoadConfigManager.hpp
//  JFDS
//
//  Created by Tao on 2016/12/6.
//
//

#ifndef LoadConfigManager_hpp
#define LoadConfigManager_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Guard.hpp"

USING_NS_CC;
using namespace std;

class Guard;

class LoadConfigManager
{
public:
    static LoadConfigManager* getInstance();
    bool init();
    void loadChapterConfig(const std::string& pFile);
    vector<Guard*> getChapterConfig();
private:
    vector<Guard*> m_chapterVector;
    map<string, bool> m_loadedFileMap;
};

#endif /* LoadConfigManager_hpp */
