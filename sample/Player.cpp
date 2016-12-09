#include "Player.h"


bool Player::initWithPlayerType(PlayerType type)
{
    std::string sfName = "";
    m_type = type;
    int animationFrameNum[5] ={4, 4, 4, 2, 4};
    int animationFrameNum2[5] ={3, 3, 3, 2, 0};
    
    switch(type)
    {
        case PlayerType::PLAYER:
            sfName = "player1-1-1.png";
            m_name = "player1";
            m_animationNum = 5;
            m_animationFrameNum.assign(animationFrameNum, animationFrameNum + 5);
            break;
        case PlayerType::ENEMY1:
            sfName = "enemy1-1-1.png";
            m_name = "enemy1";
            m_animationNum = 4;
            m_animationFrameNum.assign(animationFrameNum2, animationFrameNum2 + 5);
            break;
        case PlayerType::ENEMY2:
            sfName = "enemy2-1-1.png";
            m_name = "enemy2";
            m_animationNum = 4;
            m_animationFrameNum.assign(animationFrameNum2, animationFrameNum2 + 5);
            break;
    }
    this->initWithSpriteFrameName(sfName);
    std::string animationNames[] = {"walk", "attack", "dead", "hit", "skill"};
    m_animationNames.assign(animationNames, animationNames + 5);
    this->addAnimation();
    return true;
}




void Player::playAnimationForever(KActionType type)
{
    if((int)type >= m_animationNum)
    {
        log("illegal animation index!");
        return;
    }
    
    int index = (int)type;
    auto str = String::createWithFormat("%s-%s",m_name.c_str(), m_animationNames[(int)type].c_str())->getCString();
    auto animation = AnimationCache::getInstance()->getAnimation(str);
    if(animation)
    {
        this->stopAllActions();
        
        auto animate = Animate::create(animation);
        auto playEffect  = [=]()
        {
            
            auto path = m_animationNames[index];
            if(type == KActionType::kSkill)
            {
                path = path + (".mp3");
            }
            else
            {
                path = path + ".wav";
            }
            
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(path.c_str());

        };
        
        auto  F = CallFunc::create(playEffect);
        
        auto sp = Spawn::create(animate, F, nullptr);
        auto ac = RepeatForever::create(sp);
        this->runAction(ac);

    }
    
}


void Player::playCompleteAction()
{
    
    Vector<FiniteTimeAction *> animateArray;
    Animate * tem = NULL;
    
    for (int i = 0; i < m_animationNum; ++i) {
        
        
        tem = getAnimation((KActionType)(i));
        if (tem) {
            animateArray.pushBack(tem);
            
        }
    }
    
    
    
    
    this->runAction(RepeatForever::create(Sequence::create(animateArray)));
}



void Player::walkTo(Vec2 dest)
{
    
   this->stopAllActions();
    auto curPos = this->getPosition();
    
    //flip when moving backward
    if(curPos.x > dest.x)
        this->setFlippedX(true);
    else
        this->setFlippedX(false);
    
    //calculate the time needed to move
    auto diff = dest - curPos;
    auto time = diff.getLength()/60;
    auto move = MoveTo::create(time, dest);
    //lambda function
    auto func = [&]()
    {
        this->stopAllActions();
    };
    
    
    auto callback = CallFunc::create(func);
    auto _seq = Sequence::create(move, callback, nullptr);
    
    
    auto animate = getAnimation(KActionType::kWalk);
    auto playEffect  = [=]()
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("walk.wav");
        
    };
    auto  F = CallFunc::create(playEffect);
    auto sp = Spawn::create(animate, F, nullptr);
    auto ac = RepeatForever::create(sp);

    
    this->runAction(ac);
    this->runAction(_seq);
    
    
}

Animate* Player::getAnimation(KActionType type)
{
    
        if((int)type >= m_animationNum)
    {
        log("illegal animation index!");
        return NULL;
    }
    auto str = String::createWithFormat("%s-%s",m_name.c_str(), m_animationNames[(int)type].c_str())->getCString();
    auto animation = AnimationCache::getInstance()->getAnimation(str);
    auto animate = Animate::create(animation);
    
    return  animate;
    
    
}





void Player::addAnimation()
{
        auto animation = AnimationCache::getInstance()->getAnimation(String::createWithFormat("%s-%s",m_name.c_str(),
                                                                                             m_animationNames[0].c_str())->getCString());
        if(animation)
        return;
    
    for(int i1=0; i1 < m_animationNum; i1++)
    {
        auto animation = Animation::create();
        animation->setDelayPerUnit(0.2f);
        for(int j = 0; j <  m_animationFrameNum[i1] ; j++)
        {
            auto sfName =String::createWithFormat("%s-%d-%d.png",m_name.c_str(), i1+1, j+1)->getCString();
            animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(sfName));
        }
        
        
        
        
        
        AnimationCache::getInstance()->addAnimation(animation, String::createWithFormat("%s-%s",m_name.c_str(),
                                                                                        m_animationNames[i1].c_str())->getCString());
    }
}


Player* Player::create(PlayerType type)
{
    Player* player = new Player();
    if(player && player->initWithPlayerType(type))
    {
        player->autorelease();
        return player;
    }
    else
    {
        delete player;
        player = NULL;
        return NULL;
    }
}
