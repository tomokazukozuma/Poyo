#include "GameScene.h"
#include "Config.h"
#include "Piece.h"
#include "vector.h"

USING_NS_CC;

using namespace std;

//static const int numberOfRows = 4;
//static const int numberOfColumns = 5;

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
            Piece::pieceDeleteArray[piece->getX()][piece->getY()] = 1;
//            Piece::array->addObject(piece);
//            Piece::setElementToPieceTypeArray(piece->getX(), piece->getY(), 0);
//            Piece::setPieceInstanceArray(piece);
//            piece->removeFromParentAndCleanup(true);
        }
    }
}

//タッチエンド処理（ピースを削除する）
void GameScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCLOG("enddddddddddddddddddd");
    Piece::showDeleteMap();
//    CCObject* obj = NULL;
//    if (sizeof(Piece::array) != 0) {
//        CCLOG("%d", sizeof(Piece::array));
//        CCLOG("2222222222222");
//        CCARRAY_FOREACH_REVERSE(Piece::array, obj)
//        {
//            CCLOG("333333333333333");
//            Piece* piece = (Piece *)obj;
//            this->removeChild(piece, true);
//        }
//    }
}


void GameScene::checkDeleteMap() {
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			if (Piece::pieceDeleteArray[x][y] == 1) continue;
			GameScene::check(1, x, y);
		}
	}
	printf("\n");
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%2d",Piece::pieceDeleteArray[j][i]);
		}
		printf("\n");
	}
}



int GameScene::check(int checkType, int x, int y)
{
	if (Piece::pieceTypeArray[x][y] == EMPTY) return 0;
	int targetColorType = Piece::pieceTypeArray[x][y];
	int cells_check[4][4];
	for (int i = 0; i < 4; i++) {
//		cells_check[i] = new int[4];
		for (int j = 0; j < 4; j++) {
			cells_check[i][j] = -1; //未チェック
		}
	}
//	CCLOG("------before check --------- x:%d y:%d",x ,y);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			//printf("%2d",cells_check[j][i]);
		}
//		printf("\n");
	}
	
	checkRecursive(x, y, cells_check,targetColorType);
	
//	CCLOG("------after check --------- x:%d y:%d",x ,y);
	int count = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
//			printf("%2d",cells_check[j][i]);
			if (cells_check[j][i] == 1) {
				count++;
			}
		}
//		printf("\n");
	}
	
	if (count >= 3) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (cells_check[j][i] == 1) {
					Piece::pieceDeleteArray[j][i] = 1;
				}
			}
		}
	}
	
	return 0;
}

void GameScene::checkRecursive(int x, int y, int check_array[4][4], int colorType)
{
	if (x > 3 || y > 3 || x < 0 || y < 0 ||0 < check_array[x][y]) return;
	if (Piece::pieceTypeArray[x][y] != colorType) {
		check_array[x][y] = 2;
		return;
	}
	
	check_array[x][y] = 1;
	GameScene::checkRecursive(x + 1, y, check_array, colorType);
	GameScene::checkRecursive(x - 1, y, check_array, colorType);
	GameScene::checkRecursive(x, y + 1, check_array, colorType);
	GameScene::checkRecursive(x, y - 1, check_array, colorType);
}
