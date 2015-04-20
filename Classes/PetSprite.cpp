//
//  PetSprite.cpp
//  ttgame
//
//  Created by zhao on 14-9-3.
//
//

#include "PetSprite.h"
PetSprite * PetSprite::createPetSprite(int num){
    PetSprite * nc=PetSprite::create();
    nc->number=num;
   
    nc->pet=Sprite::create(StringUtils::format("pet%d.png",num));
//    auto bg=LayerColor::create(Color4B(175,175,175,125),80, 80);
//    nc->addChild(bg);
    //nc->pet->setContentSize(Size(80,80));
    nc->setScale(80/nc->pet->getContentSize().width,
                 80/nc->pet->getContentSize().height);
    nc->pet->setAnchorPoint(Vec2::ZERO);
    nc->addChild(nc->pet);
    
    return nc;
}
bool PetSprite::init(){
    if(!Node::init())
    {
        return false;
    }
    
    return true;
}
void PetSprite::moveTo(int r,int c){
  
//    this->setPosition(c*80,r*80);
    this->stopAllActions();
    this->runAction(MoveTo::create(0.5, Vec2(c*80,r*80)));
   
}
