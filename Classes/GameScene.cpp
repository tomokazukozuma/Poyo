#include "GameScene.h"
#include "Config.h"
#include "Piece.h"
#include "vector.h"

USING_NS_CC;

using namespace std;

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCLayerColor::initWithColor(ccc4(255, 255, 255, 255));
    
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    
    Piece::makePazzle(this);
    return true;
}


//タッチイベント開始
bool GameScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

//
void GameScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    // タップポイント取得
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCPoint touchPoint = pDirector->convertToGL(pTouch->getLocationInView());

    CCObject *obj = NULL;
    CCARRAY_FOREACH_REVERSE(this->getChildren(), obj) {
        Piece *piece = (Piece *)obj;
        CCRect pieceRect = piece->boundingBox();
        if (pieceRect.containsPoint(touchPoint))
        {
            Piece::pieceDeleteArray[piece->getX()][piece->getY()] = DeleteFlag;
        }
    }
}

//タッチエンド処理（ピースを削除する）
void GameScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
//    Piece::showDeleteMap();
    Piece::showPuzzle();
    
    // ピースの削除
    Piece::deletePiece(this);
	
	printf("before fall\n");
	Piece::showPuzzle();
    
    //　ピースの落ちる処理
	while (GameScene::fallOnePiece() != 0) {
		
	}
	
	
	printf("after fal\n");
	Piece::showPuzzle();
	
    //ピースの描画
}

int GameScene::fallOnePiece()
{
	
	int iy,n=0;
	
    for (int x=0; x < MaxPieceX; x++) {
        for (int y= MaxPieceY - 1; y >=0; y--) {
			
            if (Piece::pieceInstanceArray[x][y]->getType() == EMPTY){
                for (iy = y - 1; iy >= 0 && Piece::pieceInstanceArray[x][iy]->getType() == EMPTY;iy--);
                if (iy < 0) break;
                n++;
                for (iy = y; iy >= 0; iy--) {
                    if(iy - 1 >= 0) {
						Piece::pieceInstanceArray[x][iy] = Piece::pieceInstanceArray[x][iy-1];
						Piece::pieceInstanceArray[x][iy] -> setPos(x, iy);
					}
                    else {
						Piece::pieceInstanceArray[x][iy] = Piece::emptyPiece;
					}
                }
                break;   
            }
        }
    }
	return n;
}

void GameScene::checkDeleteMap()
{
	for (int x = 0; x < MaxPieceX; x++) {
		for (int y = 0; y < MaxPieceY; y++) {
			if (Piece::pieceDeleteArray[x][y] == DeleteFlag) continue;
			GameScene::check(1, x, y);
		}
	}
	printf("\n");
    Piece::showDeleteMap();
}



int GameScene::check(int checkType, int x, int y)
{
	if (Piece::pieceInstanceArray[x][y] == NULL) return 0;
	int targetColorType = Piece::pieceInstanceArray[x][y]->getTag();
	int cells_check[MaxPieceX][MaxPieceY];
	for (int tempY = 0; tempY < MaxPieceY; tempY++) {
		for (int tempX = 0; tempX < MaxPieceX; tempX++) {
			cells_check[tempX][tempY] = -1; //未チェック
		}
	}
    
    //	CCLOG("------before check --------- x:%d y:%d",x ,y);
	for (int tempY = 0; tempY < MaxPieceY; tempY++) {
		for (int tempX = 0; tempX < MaxPieceX; tempX++) {
			printf("%d",cells_check[tempX][tempY]);
		}
	}
	
	checkRecursive(x, y, cells_check,targetColorType);
	
//	CCLOG("------after check --------- x:%d y:%d",x ,y);
	int count = 0;
	for (int tempY = 0; tempY < MaxPieceY; tempY++) {
		for (int tempX = 0; tempX < MaxPieceX; tempX++) {
			if (cells_check[tempX][tempY] == 1) {
				count++;
			}
		}
	}
	
	if (count >= 3) {
		for (int tempY = 0; tempY < MaxPieceY; tempY++) {
			for (int tempX = 0; tempX < MaxPieceX; tempX++) {
				if (cells_check[tempX][tempY] == 1) {
					Piece::pieceDeleteArray[tempX][tempY] = DeleteFlag;
				}
			}
		}
	}
	
	return count;
}

void GameScene::checkRecursive(int x, int y, int check_array[MaxPieceX][MaxPieceY], int colorType)
{
	if (x > 3 || y > 3 || x < 0 || y < 0 ||0 < check_array[x][y]) return;
	if (Piece::pieceInstanceArray[x][y]->getTag() != colorType) {
		check_array[x][y] = 2;
		return;
	}
	
	check_array[x][y] = 1;
	GameScene::checkRecursive(x + 1, y, check_array, colorType);
	GameScene::checkRecursive(x - 1, y, check_array, colorType);
	GameScene::checkRecursive(x, y + 1, check_array, colorType);
	GameScene::checkRecursive(x, y - 1, check_array, colorType);
}
