#include "Piece.h"
#include "Config.h"
#include "cocos2d.h"
USING_NS_CC;

using namespace std;

int Piece::pieceSize = 320 / MaxPieceX;
int Piece::pieceDeleteArray[MaxPieceX][MaxPieceY];
Piece* Piece::pieceInstanceArray[MaxPieceX][MaxPieceY];

bool Piece::init()
{
    return true;
}

//初期のパズルを作成
void Piece::makePazzle(GameScene *gameScene)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    int i = 0;
    for (int y = 0; y < MaxPieceY; y++)
    {
        for (int x = 0; x < MaxPieceX; x++)
        {
			int nextColor = Random;
            Piece *piece = Piece::generatePieceWithImage(nextColor);
            piece->setPos(x, y);
            piece->setTag(i);
            piece->setContentSize(CCSize(pieceSize, pieceSize));
            Piece::setInstanceToPieceInstanceArray(x, y, piece);
			Piece::pieceDeleteArray[x][y] = 0;
            piece->setPosition(ccp(
                                   winSize.width * 0.5 + (x - MaxPieceX/2) * Piece::getPieceSize(),
                                   winSize.height * 0.5 + (MaxPieceY/2 - y) * Piece::pieceSize));
            gameScene->addChild(piece);
            i++;
        }
    }
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
        default:
            break;
    }
    return piece;
}

//デリートマップから1のものを削除
void Piece::deletePiece(GameScene *gameScene)
{
    Piece *piece;
    for (int y =0; y < MaxPieceY; y++) {
        for (int x = 0; x < MaxPieceX; x++) {
            if(Piece::pieceDeleteArray[x][y] == DeleteFlag) {
                piece = (Piece*)gameScene->getChildByTag(Piece::pieceInstanceArray[x][y]->getTag());
                gameScene->removeChild(piece);
                Piece::pieceDeleteArray[x][y] =0;
            }
        }
    }
}

//（途中）
//ピースを移動させる
void Piece::movePiece()
{
    for (int y =0; y < MaxPieceY; y++) {
        for (int x = 0; x < MaxPieceX; x++) {
            if(Piece::pieceDeleteArray[x][y] == DeleteFlag) {
                Piece::pieceDeleteArray[x][y] =0;
            }
        }
    }
}

//パズルを描画
void Piece::drawPazzle(GameScene* gameScene)
{
    int i =0;
    for (int y = 0; y < MaxPieceY; y++) {
        for (int x = 0; x < MaxPieceX; x++) {
            Piece::pieceInstanceArray[x][y]->setTag(i);
            gameScene->addChild(Piece::pieceInstanceArray[x][y]);
            ++i;
        }
    }
}

//現在のパズルをコンソールに表示
void Piece::showPuzzle()
{
	for (int y = 0; y < MaxPieceY; y++) {
		for (int x = 0; x < MaxPieceX; x++) {
			printf("%2d",Piece::pieceInstanceArray[x][y]->getType());
		}
		printf("\n");
	}
}

//現在の削除するパズルをコンソールに取得
void Piece::showDeleteMap()
{
    for (int y = 0; y < MaxPieceY; y++) {
		for (int x = 0; x < MaxPieceX; x++) {
			printf("%2d",Piece::pieceDeleteArray[x][y]);
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

//void Piece::setNextPos(int nextX, int nextY)
//{
//    this->nextX = nextX;
//    this->nextY = nextY;
//}
//
//void Piece::initNextPos()
//{
//    this->nextX = NoMove;
//    this->nextY = NoMove;
//}

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

//int Piece::getNextX()
//{
//    return this->nextX;
//}
//
//int Piece::getNextY()
//{
//    return this->nextY;
//}

int Piece::getType()
{
    return this->type;
}

// 配列のインスタンスを取得
Piece* Piece::getInstanceOfPieceInstanceArray(int x, int y)
{
    return Piece::pieceInstanceArray[x][y];
}