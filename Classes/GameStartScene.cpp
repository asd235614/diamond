//
//  GameStartScene.cpp
//  ttgame
//
//  Created by zhao on 14-9-3.
//
//

#include "GameStartScene.h"
Scene * GameStart::createScene(){
    auto scene=Scene::create();
    auto layer=GameStart::create();
    scene->addChild(layer);
    return scene;
}
bool GameStart::init(){
    if(!Layer::init())
    {
        return false;
    }

    return true;
}