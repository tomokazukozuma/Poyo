#ifndef __Poyo__ScoreManeger__
#define __Poyo__ScoreManeger__

#include "Config.h"

using namespace std;

class ScoreManeger: public cocos2d::CCSprite
{
private:
    
public:
    virtual bool init();
    CREATE_FUNC(ScoreManeger);
    
    //スコア
    static int score;
    
    /*** setter ***/
    
    //スコアをセット
    void setIncrementScore();
    
    
    
    /*** getter ***/
    
    //スコアを取得
    static int getScore();
    
};

#endif /* defined(__Poyo__ScoreManeger__) */
