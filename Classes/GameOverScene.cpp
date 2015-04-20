//
//  GameOverScene.cpp
//  ttgame
//
//  Created by zhao on 14-9-3.
//
//

#include "GameOverScene.h"
Scene * GameOver::createScene(int result){
    auto scene=Scene::create();
    auto layer=GameOver::create();
    scene->addChild(layer);
    return scene;
}
bool GameOver::init(){
    if(!Layer::init())
    {
        return false;
    }
   
    
    return true;
}