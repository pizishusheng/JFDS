//
//  LoadConfigManager.cpp
//  JFDS
//
//  Created by Tao on 2016/12/6.
//
//

#include "LoadConfigManager.hpp"
#include "json/rapidjson.h"
#include "json/document.h"
#include "Guard.hpp"

static LoadConfigManager *s_LoadConfigManager = nullptr;

LoadConfigManager* LoadConfigManager::getInstance()
{
    if (!s_LoadConfigManager) {
        s_LoadConfigManager = new (std::nothrow) LoadConfigManager();
        CCASSERT(s_LoadConfigManager, "FATAL: Not enough memory");
        s_LoadConfigManager->init();
    }
    return s_LoadConfigManager;
}

bool LoadConfigManager::init()
{
    
    return true;
}

void LoadConfigManager::loadChapterConfig(const std::string &pFile)
{
    string content = FileUtils::getInstance()->getStringFromFile(pFile);
    log("path =========%s", content.c_str());
    rapidjson::Document doc;
    doc.Parse<0>(content.c_str());
    
    if(doc.HasParseError()) {
        log("parse json error!");
        return;
    }
    
    if (doc.IsObject() && doc.HasMember("guard")) {
        const rapidjson::Value& guardJson = doc["guard"];
        if (guardJson.IsArray()) {
            for (rapidjson::SizeType i = 0; i < guardJson.Size(); i++) {
                const rapidjson::Value& guard = guardJson[i];
                uint type = guard["type"].GetUint();
                float speed = guard["speed"].GetDouble();
                log("type=%d-----speed=%f", type, speed);
                const rapidjson::Value& visonJson = guard["vison"];
                Vec2 vison = Vec2(visonJson["l"].GetDouble(), visonJson["r"].GetDouble());
                log("vison======x=%f, y=%f", vison.x, vison.y);
                const rapidjson::Value& bornJson = guard["born"];
                Vec2 born = Vec2(bornJson["x"].GetDouble(), bornJson["y"].GetDouble());
                log("born======x=%f, y=%f", born.x, born.y);
                const rapidjson::Value& pathJson = guard["path"];
                if (pathJson.IsArray()) {
                    for (rapidjson::SizeType i = 0; i < pathJson.Size(); i++) {
                        const rapidjson::Value& path = pathJson[i];
                        const rapidjson::Value& faceJson = path["faceDirection"];
                        Vec2 faceDirection = Vec2(faceJson["x"].GetDouble(), faceJson["y"].GetDouble());
                        float stayTime = path["staytime"].GetDouble();
                        log("faceDirection====x=%f, y=%f--------staytime=%f", faceDirection.x, faceDirection.y, stayTime);
                    }
                }
            }
        }
    }
        
        
        
        
        
        
}
