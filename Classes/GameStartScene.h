//
//  GameStartScene.h
//
//
//

#ifndef __ttgame__GameStartScene__
#define __ttgame__GameStartScene__
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocostudio;//动画相关的类位于cocostuio::timeline当中 
using namespace cocostudio::timeline;//动画相关的类位于cocostuio::timeline当中 
using namespace cocos2d;
using namespace cocos2d::ui;

class GameStart:public Layer {
public:
    CREATE_FUNC(GameStart);
    static Scene * createScene();
    bool init();
private:
	void startCallback(Ref* sender, Widget::TouchEventType type);
	void leftCallback(Ref* sender, Widget::TouchEventType type);
	void rightCallback(Ref* sender, Widget::TouchEventType type);
	PageView* pageView;
	/*Button* button_start;
	Button* button_left;
	Button* button_right;*/


	void pageViewEvent(Ref *pSender, PageView::EventType type);
	//void onButtonClicked(Ref* sender, Widget::TouchEventType type);
};
#endif /* defined(__ttgame__GameStartScene__) */
