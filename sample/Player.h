#ifndef __Player__
#define __Player__
#include "cocos2d.h"
#include <vector>


USING_NS_CC;

enum class KActionType
{
    kWalk,
    KAttack,
    KDead,
    KHit,
    kSkill,
    KActionTypeCount
};


class Player : public Sprite
{
public:
    enum PlayerType
    {
        PLAYER,
        ENEMY1,
        ENEMY2
    };
    
    
    bool initWithPlayerType(PlayerType type); 
    
    static Player* create(PlayerType type);    
    
    void addAnimation();
    
    void playAnimationForever(KActionType type);
    
    Animate* getAnimation(KActionType type);
    
    void playCompleteAction();

    void walkTo(Vec2 dest);
    
private:
    PlayerType m_type;
    std::string m_name;
    int m_animationNum;
    std::vector<int> m_animationFrameNum;
    std::vector<std::string> m_animationNames;
};

#endif