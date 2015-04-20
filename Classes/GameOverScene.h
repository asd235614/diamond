//
//  GameOverScene.h
//
//
//

#ifndef __ttgame__GameOverScene__
#define __ttgame__GameOverScene__
#include "cocos2d.h"
#include "DiamondSprite.h"
using namespace cocos2d;
enum class GAMEDIR{
 DIR_UP,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_DOWN
};
class GameOver:public Layer{
public:
    CREATE_FUNC(GameOver);
    static Scene * createScene(int result);
    bool init();
};
#endif /* defined(__ttgame__GameOverScene__) */
