//
//  MonsterSprite.cpp
//  ttgame
//
//  Created by zhao on 14-9-3.
//
//

#include "MonsterSprite.h"
MonsterSprite * MonsterSprite::createMonsterSprite(int num,int blood){
    MonsterSprite * nc=MonsterSprite::create();
    nc->number=num;
	nc->monster=Sprite::create(StringUtils::format("Monster%d.png",num));
//    auto bg=LayerColor::create(Color4B(175,175,175,125),80, 80);
//    nc->addChild(bg);
    //nc->monster->setContentSize(Size(80,80));

    
    return nc;
}
bool MonsterSprite::init(){
    if(!Node::init())
    {
        return false;
    }
    
    return true;
}
