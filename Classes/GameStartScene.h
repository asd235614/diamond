//
//  GameStartScene.h
//
//
//

#ifndef __ttgame__GameStartScene__
#define __ttgame__GameStartScene__
#include "cocos2d.h"
#include "DiamondSprite.h"

using namespace cocos2d;
enum class GAMEDIR{
 DIR_UP,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_DOWN
};
class GameStart:public Layer{
public:
    CREATE_FUNC(GameStart);
    static Scene * createScene();
    bool init();
	
};
#endif /* defined(__ttgame__GameStartScene__) */
