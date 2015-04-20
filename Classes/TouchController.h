#pragma once
#ifndef TouchController_H_
#define TouchController_H_

#include "cocos2d.h"

USING_NS_CC;

class TouchControllerEvent;
class TouchController: public Node
{
public:
	TouchController(void);
	~TouchController(void);
	CREATE_FUNC(TouchController);
	virtual bool init()	;

	// 设置显示项
	void setDisplay(Sprite* dis);
    Sprite* getDisplay();

	void setEventId(int eventId);
	int getEventId();

	/// 常规判断
	bool selfCheck(Touch* ccTouch, TouchControllerEvent* lsTe);

private:
	// 判断当前的元素是否被点击
	bool containsCCTouchPoint(Touch* ccTouch);
	bool isParentAllVisible(TouchControllerEvent* lsTe);

	// 用户保存显示精灵的 tag
	static const int TAG_DISPLAY = 100;
	int m_iEventId;

};

class TouchControllerEvent {
public:
	TouchControllerEvent();
	~TouchControllerEvent();

	void addTouchController(TouchController* touch, int eventId);

	void removeTouchController(TouchController* touch);

	bool sendTouchMessage(CCTouch* ccTouch, int type);

	// 返回优先级较高的可触摸对象
	TouchController* getPriorityTouch(TouchController* a, TouchController* b);

	virtual void touchEventAction(TouchController* touch, int type) = 0;
private:
	CCArray* m_pTouchControlleres;
};


#endif /* TouchController_H_ */