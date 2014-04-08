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
    
    //ピースのタイプ（red, blue, green, yellow）
    int type;
    
    //ピースのタイプを格納する配列
    static int pieceTypeArray[MaxPieceX][MaxPieceY];
	
	// 削除するピースを格納する配列
    static int pieceDeleteArray[MaxPieceX][MaxPieceY];
    
    //Pieceクラスのインスタンスを格納する配列
    static Piece* pieceInstanceArray[MaxPieceX][MaxPieceY];
    
    //空を示すPieceインスタンス
    static Piece* emptyPiece;
    
    //ピースの数をtag用にカウント
    static int pieceTagNumber;
    
    //削除が終わってるかどうか
    static bool deleteFinishFlag;
    
    static bool isAnimation;
    
    
    
    
    /*** static method ***/
    
    //ピースの幅を取得
    static int getPieceSize();
    
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
    
    // パズルの描画
    static void drawPazzle(GameScene* gameScene);
    
    //隙間をピースで埋める
    static void pushPiece(GameScene* gameScene);
    
    //空を示すPieceインスタンスを取得
    static Piece* getEmptyOfPiece();
    
    //タグ用のナンバーをインクリメント
    static void setIncrementPieceTagNumber();
    
    //タグ用のナンバーを取得
    static int getPieceTagNumber();
    
    static void setDeleteFinishFlag(bool deleteFinishFlag);
    
    static bool getDeleteFinishFlag();
    
    static void setIsAnimation(bool isAnimation);
    
    static bool getIsAnimation();

    
    
    
    /*** setter ***/
    
    //インスタンスに位置をセット
    void setPos(int x, int y);
    
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
    
    int getType();
};

#endif /* defined(__Poyo__Piece__) */
