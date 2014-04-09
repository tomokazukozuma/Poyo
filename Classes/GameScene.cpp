#include "GameScene.h"
#include "Config.h"
#include "Piece.h"
#include "vector.h"

USING_NS_CC;

using namespace std;
bool GameScene::isNotAnimation = true;
int GameScene::count = 0;

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
    
//    if(!Piece::getIsAnimation()) {
        this->setTouchEnabled(true);
        this->setTouchMode(kCCTouchesOneByOne);
//    }
    
    Piece::makePazzle(this);
    
    this->scheduleUpdate();
    return true;
}

//アニメーション中か毎フレーム判定
void GameScene::update(float dt)
{
    bool isAnimation = false;
    CCObject* obj;
    CCARRAY_FOREACH(this->getChildren(), obj) {
        Piece* piece = (Piece*)obj;
        if (piece->numberOfRunningActions() != 0) {
            isAnimation = true;
        }
    }
    Piece::setIsAnimation(isAnimation);
}


//タッチイベント開始
bool GameScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (isNotAnimation == true){
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
	
    
    return true;
}

//
void GameScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (isNotAnimation == true) {
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
}

//タッチエンド処理（ピースを削除する）
void GameScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (isNotAnimation == true) {
    // ピースの削除
    Piece::deletePiece(this);
	
	GameScene::loopAnimation();

//	printf("after fal\n");
//	Piece::showDeleteMap();
	
	Piece::showPuzzle();
	
	}
}
void GameScene::loopAnimation() {
	// ピースの削除処理と落ちる処理
	do {
		if (isNotAnimation == true && count ==0) {
			GameScene::fallOnePiece();
			count++;
		}
		
        //パズルの描画
		if (isNotAnimation == true && count == 1) {
			//ピースの落ちる処理
			
			Piece::drawPazzle(this);
			
			isNotAnimation = false;
			this->schedule(schedule_selector(GameScene::stopAnimation), 1);
		}
        
		
		//        if(!Piece::getIsAnimation()) {
		
		//        }
	} while (Piece::getDeleteFinishFlag() == false && isNotAnimation == true);
	bool isEmpty = false;
	for (int y = 0; y < MaxPieceY; y++) {
        for (int x = 0; x < MaxPieceX; x++) {
            if (Piece::pieceInstanceArray[x][y]->getType() == EMPTY) {
				isEmpty = true;
			}
		}
	}
	if (isEmpty == true) {
		Piece::pushPiece(this);
		isNotAnimation = false;
		this->schedule(schedule_selector(GameScene::stopPushAnimation), 1);
	}
}
void GameScene::stopAnimation() {
	GameScene::checkDeleteMap();
	
	//ピースを削除
	Piece::deletePiece(this);
	isNotAnimation = true;
	count = 0;
	this->unschedule(schedule_selector(GameScene::stopAnimation));
}

void GameScene::stopPushAnimation() {
	GameScene::checkDeleteMap();
	Piece::deletePiece(this);
	isNotAnimation = true;
	count = 0;
	this->unschedule(schedule_selector(GameScene::stopPushAnimation));
	GameScene::loopAnimation();

}
void GameScene::fallOnePiece()
{
	int n;
	do {
		int iy;
		n = 0;
	    for (int x=0; x < MaxPieceX; x++) {
    	    for (int y= MaxPieceY - 1; y >=0; y--) {
				
            	if (Piece::pieceInstanceArray[x][y]->getType() == EMPTY){
                	for (iy = y - 1; iy >= 0 && Piece::pieceInstanceArray[x][iy]->getType() == EMPTY;iy--);
	                if (iy < 0) break;
					n++;
    	            for (iy = y; iy >= 0; iy--) {
	                    if(iy - 1 >= 0) {
							Piece::pieceInstanceArray[x][iy] = Piece::pieceInstanceArray[x][iy-1];
						}
            	        else {
							Piece::pieceInstanceArray[x][iy] = Piece::emptyPiece;
						}
	                }
    	            break;
        	    }
        	}
	    }
	}while (n != 0);
}

bool GameScene::checkDeleteMap()
{
	bool checkFlag = false;
	for (int x = 0; x < MaxPieceX; x++) {
		for (int y = 0; y < MaxPieceY; y++) {
			if (Piece::pieceDeleteArray[x][y] == DeleteFlag) continue;
			if (GameScene::check(1, x, y) >= thresholdOfDeletePiece) checkFlag = true;
		}
	}
	printf("\n");
 //   Piece::showDeleteMap();
	return checkFlag;
}



int GameScene::check(int checkType, int x, int y)
{
	if (Piece::pieceInstanceArray[x][y] == NULL) return 0;
	int targetColorType = Piece::pieceInstanceArray[x][y]->getType();
	int cells_check[MaxPieceX][MaxPieceY];
	for (int tempY = 0; tempY < MaxPieceY; tempY++) {
		for (int tempX = 0; tempX < MaxPieceX; tempX++) {
			if (Piece::pieceInstanceArray[tempX][tempY] -> getType() == EMPTY) {
				cells_check[tempX][tempY] = 2;
			} else {
				cells_check[tempX][tempY] = -1; //未チェック
			}

		}
	}
	
    
	//CCLOG("------before check --------- x:%d y:%d",x ,y);
	for (int tempY = 0; tempY < MaxPieceY; tempY++) {
		for (int tempX = 0; tempX < MaxPieceX; tempX++) {
	//		printf("%3d",cells_check[tempX][tempY]);
		}
	//	printf("\n");
	}
	
	checkRecursive(x, y, cells_check,targetColorType);
	
//	CCLOG("------after check --------- x:%d y:%d",x ,y);
	int count = 0;
	for (int tempY = 0; tempY < MaxPieceY; tempY++) {
		for (int tempX = 0; tempX < MaxPieceX; tempX++) {
//			printf("%3d",cells_check[tempX][tempY]);
			if (cells_check[tempX][tempY] == 1) {
				count++;
			}
		}
//		printf("\n");
	}
	
	if (count >= thresholdOfDeletePiece) {
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
	if (x > MaxPieceX - 1 || y > MaxPieceY - 1 || x < 0 || y < 0 ||0 < check_array[x][y]) return;
	if (Piece::pieceInstanceArray[x][y]->getType() != colorType) {
		check_array[x][y] = 2;
		return;
	}
	
	check_array[x][y] = 1;
	GameScene::checkRecursive(x + 1, y, check_array, colorType);
	GameScene::checkRecursive(x - 1, y, check_array, colorType);
	GameScene::checkRecursive(x, y + 1, check_array, colorType);
	GameScene::checkRecursive(x, y - 1, check_array, colorType);
}
