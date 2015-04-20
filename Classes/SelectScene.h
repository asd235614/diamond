//
//  SelectScene.h
//  ttgame
//
//  Created by zhao on 14-9-3.
//
//

#ifndef __ttgame__SelectScene__
#define __ttgame__SelectScene__
#include "cocos2d.h"
#include "DiamondSprite.h"
using namespace cocos2d;
enum class GAMEDIR{
 DIR_UP,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_DOWN
};
class Select:public Layer{
public:
    CREATE_FUNC(Select);
    static Scene * createScene();
    bool init();
};
#endif /* defined(__ttgame__SelectScene__) */
