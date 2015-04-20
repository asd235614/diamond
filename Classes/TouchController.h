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

	// ������ʾ��
	void setDisplay(Sprite* dis);
    Sprite* getDisplay();

	void setEventId(int eventId);
	int getEventId();

	/// �����ж�
	bool selfCheck(Touch* ccTouch, TouchControllerEvent* lsTe);

private:
	// �жϵ�ǰ��Ԫ���Ƿ񱻵��
	bool containsCCTouchPoint(Touch* ccTouch);
	bool isParentAllVisible(TouchControllerEvent* lsTe);

	// �û�������ʾ����� tag
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

	// �������ȼ��ϸߵĿɴ�������
	TouchController* getPriorityTouch(TouchController* a, TouchController* b);

	virtual void touchEventAction(TouchController* touch, int type) = 0;
private:
	CCArray* m_pTouchControlleres;
};


#endif /* TouchController_H_ */