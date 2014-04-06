#include "Piece.h"
#include "Config.h"
#include "cocos2d.h"
USING_NS_CC;

using namespace std;

int Piece::pieceSize = 100;
int Piece::pieceDeleteArray[4][4];
Piece* Piece::pieceInstanceArray[4][4];

bool Piece::init()
{
    return true;
}

//初期のパズルを作成
void Piece::makePazzle(GameScene *gameScene)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    int i = 0;
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
			int nextColor = Random;
            Piece *piece = Piece::generatePieceWithImage(nextColor);
            piece->setPos(x, y);
            piece->setTag(i);
            piece->setContentSize(CCSize(pieceSize, pieceSize));
            Piece::setInstanceToPieceInstanceArray(x, y, piece);
			Piece::pieceDeleteArray[x][y] = 0;
            piece->setPosition(ccp(
                                   winSize.width * 0.5 + (x - 1.5) * Piece::pieceSize,
                                   winSize.height * 0.5 + (1.5 - y) * Piece::pieceSize));
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
    
	if (colorType == Random) colorType = rand()%4;
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
    for (int y =0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if(Piece::pieceDeleteArray[x][y] == DeleteFlag) {
                piece = (Piece*)gameScene->getChildByTag(Piece::pieceInstanceArray[x][y]->getTag());
                gameScene->removeChild(piece);
                Piece::pieceDeleteArray[x][y] =0;
            }
        }
    }
}

//ピースを移動させる
void Piece::movePiece()
{
    for (int y =0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if(Piece::pieceDeleteArray[x][y] == DeleteFlag) {
                Piece::pieceDeleteArray[x][y] =0;
            }
        }
    }
}

//パズルを描画
void Piece::drawPazzle()
{
    
}

void Piece::showPuzzle()
{
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			printf("%2d",Piece::pieceInstanceArray[x][y]->getType());
		}
		printf("\n");
	}
}

void Piece::showDeleteMap()
{
    for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%2d",Piece::pieceDeleteArray[j][i]);
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

void Piece::setNextPos(int nextX, int nextY)
{
    this->nextX = nextX;
    this->nextY = nextY;
}

void Piece::initNextPos()
{
    this->nextX = NoMove;
    this->nextY = NoMove;
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

int Piece::getNextX()
{
    return this->nextX;
}

int Piece::getNextY()
{
    return this->nextY;
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