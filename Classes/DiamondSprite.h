
//  钻石完成
//

#ifndef __ttgame__Diamond__
#define __ttgame__Diamond__

#include "cocos2d.h"

using namespace cocos2d;
class DiamondSprite:public Node
{
public:
	Sprite *sp;
    int number;//数字编号 怪物编号
    int row,col;
    bool canRemove;//是否要消除
    
    CREATE_FUNC(DiamondSprite);
    static DiamondSprite * createDiamondSprite(int num,int r,int c);
    bool init();
    void moveTo(int r,int c);
};
#endif /* defined(__ttgame__Card__) */
