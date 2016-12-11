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
    if(m_loadedFileMap[pFile]){
        log("该文件已经加载过了");
        return ;
    }
    
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
                Guard* guardModel = Guard::create();
                guardModel->retain();
                const rapidjson::Value& guard = guardJson[i];
                guardModel->m_type = guard["type"].GetUint();
                guardModel->m_speed = guard["speed"].GetDouble();
                
                const rapidjson::Value& visonJson = guard["vison"];
                guardModel->m_visonL = visonJson["l"].GetDouble();
                guardModel->m_visonR = visonJson["r"].GetDouble();
                
                const rapidjson::Value& bornJson = guard["born"];
                guardModel->m_born = Vec2(bornJson["x"].GetDouble(), bornJson["y"].GetDouble());
                
                const rapidjson::Value& pathJson = guard["path"];
                if (pathJson.IsArray()) {
                    for (rapidjson::SizeType i = 0; i < pathJson.Size(); i++) {
                        Path* pathModel = Path::create();
                        pathModel->retain();
                        const rapidjson::Value& path = pathJson[i];
                        const rapidjson::Value& faceJson = path["faceDirection"];
                        Vec2 faceDirection = Vec2(faceJson["x"].GetDouble(), faceJson["y"].GetDouble());
                        float stayTime = path["staytime"].GetDouble();
                        pathModel->m_faceDirection = faceDirection;
                        pathModel->m_staytime = stayTime;
                        guardModel->m_path.push_back(pathModel);
                    }
                }
                m_chapterVector.push_back(guardModel);
            }
        }
    }
    m_loadedFileMap[pFile] = true;
}

vector<Guard*> LoadConfigManager::getChapterConfig()
{
    return m_chapterVector;
}












