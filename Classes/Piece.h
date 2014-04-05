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
    
    /*** parameter ***/
    
    //ピースの位置x
    int x;
    
    //ピースの位置y
    int y;
    
    //ピースのタイプ
    int type;
    
    //ピースのタイプを格納する配列
    static int pieceTypeArray[4][4];
	
	// 削除するピースを格納する配列
    static int pieceDeleteArray[4][4];
    
    //Pieceクラスのインスタンスを格納する配列
    static Piece* pieceInstanceArray[4][4];
    
    
    /*** method ***/
    
    //開始時のパズルを作成
    static void makePazzle(GameScene *gameScene);
    
    //imageを生成
    static Piece* generatePieceWithImage(int colorType);
    
    //ピースの削除
    static void deletePiece(GameScene *gameScene);
    
    // Puzzleの表示
	static void showPuzzle();
    
    //削除マップの表示
    static void showDeleteMap();
    
    
    /*** setter ***/
    
    //インスタンスに位置をセット
    void setPos(int x, int y);
    
    //インスタンスにタイプをセット
    void setType(int type);
    
    //要素の代入
    static void setElementToPieceTypeArray(int x, int y, int tag);
    
    //Pieceのインスタンスを格納
    static void setInstanceToPieceInstanceArray(int x, int y, Piece *piece);

    
    /*** getter ***/
    
    //要素の取得
    static int getElementOfPieceTypeArray(int x, int y);
    
    int getX();
    
    int getY();
    
    int getType();
    
    //ピースの幅を取得
    static int getPieceSize();
};

#endif /* defined(__Poyo__Piece__) */
