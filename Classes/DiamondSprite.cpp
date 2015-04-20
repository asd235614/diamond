//
//  DiamondSprite.cpp
//  ttgame
//
//  Created by zhao on 14-9-3.
//
//

#include "DiamondSprite.h"
DiamondSprite * DiamondSprite::createDiamondSprite(int num,int r,int c){
    DiamondSprite * nc=DiamondSprite::create();
    nc->number=num;
    nc->sp=Sprite::create(StringUtils::format("Diamond%d.png",num));
//    auto bg=LayerColor::create(Color4B(175,175,175,125),80, 80);
//    nc->addChild(bg);
    //nc->sp->setContentSize(Size(80,80));
    nc->setScale(80/nc->sp->getContentSize().width,
                 80/nc->sp->getContentSize().height);
    nc->sp->setAnchorPoint(Vec2::ZERO);
    nc->addChild(nc->sp);
    nc->setPosition(c*80,700);
    nc->moveTo(r, c);
    nc->canRemove=false;//不能消除
    
    return nc;
}
bool DiamondSprite::init(){
    if(!Node::init())
    {
        return false;
    }
    
    return true;
}
void DiamondSprite::moveTo(int r,int c){
    this->row=r;
    this->col=c;
//    this->setPosition(c*80,r*80);
    this->stopAllActions();
    this->runAction(MoveTo::create(0.5, Vec2(c*80,r*80)));
   
}
