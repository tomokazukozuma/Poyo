#ifndef __Colors__Piece__
#define __Colors__Piece__

#include "cocos2d.h"
#include "GameScene.h"
#include "map.h"
#include "vector.h"
#include "Config.h"

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
    
//    CC_SYNTHESIZE_READONLY(int, nextX, NextN);
    
//    //ピースの次の位置x
//    int nextX;
//    
//    //ピースの次の位置y
//    int nextY;
    
    //ピースのタイプ（red, blue, green, yellow）
    int type;
    
    //ピースのタイプを格納する配列
    static int pieceTypeArray[MaxPieceX][MaxPieceY];
	
	// 削除するピースを格納する配列
    static int pieceDeleteArray[MaxPieceX][MaxPieceY];
    
    //Pieceクラスのインスタンスを格納する配列
    static Piece* pieceInstanceArray[MaxPieceX][MaxPieceY];
    
    
    /*** static method ***/
    
    //開始時のパズルを作成
    static void makePazzle(GameScene *gameScene);
    
    //imageを生成
    static Piece* generatePieceWithImage(int colorType);
    
    //ピースの削除
    static bool deletePiece(GameScene *gameScene);
    
    // Puzzleの表示
	static void showPuzzle();
    
    //削除マップの表示
    static void showDeleteMap();
    
    //pieceの移動
    static void movePiece();
    
    // パズルの描画
    static void drawPazzle(GameScene* gameScene);
    
    // アニメーションの実行
    static void executeDeleteAnimation();

    
    
    /*** setter ***/
    
    //インスタンスに位置をセット
    void setPos(int x, int y);
    
    //インスタンスに次の位置をセット
    void setNextPos(int nextX, int nextY);
    
    //nextX, nextYの初期化
    void initNextPos();
    
    //インスタンスにタイプをセット
    void setType(int type);
    
    //インスタンスをセット
    static void setInstanceToPieceInstanceArray(int x, int y, Piece *piece);
    

    
    /*** getter ***/
    
    //要素の取得
    static Piece* getInstanceOfPieceInstanceArray(int x, int y);
    
    int getX();
    
    int getY();
    
    int getNextX();
    
    int getNextY();
    
    int getType();
    
    //ピースの幅を取得
    static int getPieceSize();
	
	static Piece* emptyPiece;
	static Piece* getEmptyOfPiece();
};

#endif /* defined(__Poyo__Piece__) */
