#include "cocos2d.h"
#include "ScoreManeger.h"
USING_NS_CC;

using namespace std;

int ScoreManeger::score = 0;

bool ScoreManeger::init()
{
    return true;
}

/*** setter ***/

//スコアをセット
void ScoreManeger::setIncrementScore()
{
    ScoreManeger::score ++;
}



/*** getter ***/

//スコアを取得
int ScoreManeger::getScore()
{
    return ScoreManeger::score;
}

#include "ScoreManeger.h"
