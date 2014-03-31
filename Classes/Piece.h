#ifndef __Colors__Piece__
#define __Colors__Piece__

#include "cocos2d.h"
#include "GameScene.h"
#include "map.h"
#include "vector.h"

using namespace std;

class Piece: public cocos2d::CCSprite
{
private:
    static int pieceSize;
    
public:
    virtual bool init();
    CREATE_FUNC(Piece);
    
    int x;
    
    int y;
    
    //ピースのタイプ
    int type;
    
    void setPos(int x, int y);
    
    void setType(int type);
    
    int getX();
    
    int getY();
    
    int getType();
    
    //ピースの幅を取得
    static int getPieceSize();
    
    //開始時のパズルを作成
    static void makePazzle(GameScene *gameScene);
    
    //imageを設定
    static Piece* generatePieceWithImage();
    
    //ピースのタイプを格納する配列
    static int pieceTypeArray[4][4];
    
    //削除するピースのインスタンスを格納
    static vector<Piece*> pieceInstanceArray[];
    
    //要素の代入
    static void setElementToPieceArray(int x, int y, int tag);
    
    //要素の取得
    static int getElementOfPieceArray(int x, int y);
    
    static void setPieceInstanceArray(Piece *piece);

};

#endif /* defined(__Poyo__Piece__) */
