//
//  selectscene.cpp
//  1��ѡ������
//
//

#include "SelectScene.h"
Scene * Select::createScene(){
    auto scene=Scene::create();
    auto layer=Select::create();
    scene->addChild(layer);
    return scene;
}
bool Select::init(){
    if(!Layer::init())
    {
        return false;
    }
    
    
    return true;
}