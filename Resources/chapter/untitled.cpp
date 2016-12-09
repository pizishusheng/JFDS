
vector<Guard*> m_chapterVector;

void A::a()
{
    for (int i = 0; i < 4; ++i)
    {
        Guard* guardModel = Guard::create();
        guardModel->m_type = i;
        guardModel->retain()
        m_chapterVector.push_back(guardModel);
    }
}

class Guard 
{
public:
    Guard();
    ~Guard();
    friend class LoadConfigManager;
private:
    Vec2 m_faceDirection;
    float m_staytime;
    std::vector<Path*> m_path;
};
