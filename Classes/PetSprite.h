//
//  PetSprite.h
//  
//  选择完宠物之后，需要把选择的宠物传给playscene
//

#include "cocos2d.h"

using namespace cocos2d;
class PetSprite:public Node
{
public:
    int number;//数字编号 编号
    int color;
    Sprite * pet;
    CREATE_FUNC(PetSprite);
    static PetSprite * createPetSprite(int num);
    bool init();
    void moveTo(int r,int c);
};