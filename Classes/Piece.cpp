#include "Piece.h"
#include "Config.h"
#include "cocos2d.h"
USING_NS_CC;

using namespace std;

int Piece::pieceSize = 320 / MaxPieceX;
int Piece::pieceDeleteArray[MaxPieceX][MaxPieceY];
Piece* Piece::pieceInstanceArray[MaxPieceX][MaxPieceY];
Piece* Piece::emptyPiece;
int Piece::pieceTagNumber = 0;

bool Piece::init()
{
    return true;
}

//初期のパズルを作成
void Piece::makePazzle(GameScene *gameScene)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    for (int y = 0; y < MaxPieceY; y++)
    {
        for (int x = 0; x < MaxPieceX; x++)
        {
			int nextColor = Random;
            Piece *piece = Piece::generatePieceWithImage(nextColor);
            piece->setPos(x, y);
            piece->setTag(Piece::pieceTagNumber);
            Piece::setIncrementPieceTagNumber();
            piece->setContentSize(CCSize(pieceSize, pieceSize));
            Piece::setInstanceToPieceInstanceArray(x, y, piece);
			Piece::pieceDeleteArray[x][y] = 0;
            piece->setPosition(ccp(
                                   winSize.width * 0.5 + (x - MaxPieceX/2) * Piece::getPieceSize(),
                                   winSize.height * 0.5 + (MaxPieceY/2 - y) * Piece::pieceSize));
            gameScene->addChild(piece);
        }
    }
	emptyPiece = Piece::generatePieceWithImage(EMPTY);
	emptyPiece -> retain();
	emptyPiece -> setTag(EMPTY);
	Piece::showPuzzle();
}

//CCSpriteオブジェクトを生成して返す
Piece* Piece::generatePieceWithImage(int colorType)
{
    Piece *piece;
    
	if (colorType == Random) colorType = rand()%PieceCount;
    switch (colorType) {
        case Red:
            piece = (Piece*)CCSprite::create("red.png", CCRectMake(0, 0, 50, 50));
            piece->setType(Red);
            break;
        case Blue:
            piece = (Piece*)CCSprite::create("blue.png", CCRectMake(0, 0, 50, 50));
            piece->setType(Blue);
            break;
        case Green:
            piece = (Piece*)CCSprite::create("green.png", CCRectMake(0, 0, 50, 50));
            piece->setType(Green);
            break;
        case Yellow:
            piece = (Piece*)CCSprite::create("yellow.png", CCRectMake(0, 0, 50, 50));
            piece->setType(Yellow);
            break;
		case EMPTY:
			piece = (Piece*)CCSprite::create("yellow.png", CCRectMake(0, 0, 50, 50));
            piece->setType(EMPTY);
            break;
        default:
            break;
    }
    return piece;
}

//デリートマップから1のものを削除
bool Piece::deletePiece(GameScene *gameScene)
{
    Piece *piece;
	bool isDeletePiece = false;
    for (int y =0; y < MaxPieceY; y++) {
        for (int x = 0; x < MaxPieceX; x++) {
            if(Piece::pieceDeleteArray[x][y] == DeleteFlag) {
                piece = (Piece*)gameScene->getChildByTag(Piece::pieceInstanceArray[x][y]->getTag());
                gameScene->removeChild(piece);
				Piece::pieceInstanceArray[x][y] = emptyPiece;
                Piece::pieceDeleteArray[x][y] =0;
				isDeletePiece = true;
            }
        }
    }
	return isDeletePiece;
}

//パズルを描画
void Piece::drawPazzle(GameScene* gameScene)
{
    //画面サイズ
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    //アニメーションの時間
    int duration = 1.0f;
    
    CCObject* obj;
    CCARRAY_FOREACH_REVERSE(gameScene->getChildren(), obj) {
        Piece* piece = (Piece*)obj;
        for (int y = 0; y < MaxPieceY; y++) {
            for (int x = 0; x < MaxPieceX; x++) {
                if (piece->getTag() == Piece::pieceInstanceArray[x][y]->getTag() && piece->getY() != y) {
                    //移動先の設定
                    CCMoveTo* pieceMove = CCMoveTo::create(duration, ccp(
                                                                          winSize.width * 0.5 + (x - MaxPieceX/2) * Piece::getPieceSize(),
                                                                          winSize.height * 0.5 + (MaxPieceY/2 - y) * Piece::pieceSize));
                    piece->setPos(x, y);
                    Piece::pieceInstanceArray[x][y]->runAction(pieceMove);
                }
            }
        }
    }
}

//空のマスにピースを埋める
void Piece::pushPiece(GameScene* gameScene)
{
    //画面サイズ
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    //アニメーションの時間
    int duration = 1.0f;
    
    Piece* piece;
    for (int y = 0; y < MaxPieceY; y++) {
        for (int x = 0; x < MaxPieceX; x++) {
            if (pieceInstanceArray[x][y]->getType() == EMPTY) {
                piece = (Piece*)Piece::generatePieceWithImage(Random);
                piece->setTag(Piece::getPieceTagNumber());
                Piece::setIncrementPieceTagNumber();
                piece->setPos(x, y);
                piece->setPosition(ccp(
                                       winSize.width * 0.5 + (x - MaxPieceX/2) * Piece::getPieceSize(),
                                       winSize.height + (MaxPieceY - y) * Piece::getPieceSize()));
                Piece::setInstanceToPieceInstanceArray(x, y, piece);
                gameScene->addChild(piece);
                
                //移動先の設定
                CCMoveTo* pieceMove = CCMoveTo::create(duration, ccp(
                                                                     winSize.width * 0.5 + (x - MaxPieceX/2) * Piece::getPieceSize(),
                                                                     winSize.height * 0.5 + (MaxPieceY/2 - y) * Piece::pieceSize));
                piece->runAction(pieceMove);
            }
        }
    }
}

void Piece::setIncrementPieceTagNumber()
{
    Piece::pieceTagNumber++;
}

int Piece::getPieceTagNumber()
{
    return Piece::pieceTagNumber;
}

//現在のパズルをコンソールに表示
void Piece::showPuzzle()
{
	for (int y = 0; y < MaxPieceY; y++) {
		for (int x = 0; x < MaxPieceX; x++) {
			printf("%3d",Piece::pieceInstanceArray[x][y]->getType());
		}
		printf("\n");
	}
}

//現在の削除するパズルをコンソールに取得
void Piece::showDeleteMap()
{
    for (int y = 0; y < MaxPieceY; y++) {
		for (int x = 0; x < MaxPieceX; x++) {
			printf("%3d",Piece::pieceDeleteArray[x][y]);
		}
		printf("\n");
	}
}

/*** setter ***/

void Piece::setPos(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Piece::setType(int type)
{
    this->type = type;
}

void Piece::setInstanceToPieceInstanceArray(int x, int y, Piece *piece)
{
    Piece::pieceInstanceArray[x][y] = piece;
}


/*** getter ***/

//ピースのサイズを取得
int Piece::getPieceSize()
{
    return Piece::pieceSize;
}

int Piece::getX()
{
    return this->x;
}

int Piece::getY()
{
    return this->y;
}

int Piece::getType()
{
    return this->type;
}

// 配列のインスタンスを取得
Piece* Piece::getInstanceOfPieceInstanceArray(int x, int y)
{
    return Piece::pieceInstanceArray[x][y];
}