#include "TouchController.h"

TouchController::TouchController() {
	m_iEventId = 0;
}

TouchController::~TouchController() {
}

bool TouchController::init() {

	return true;
}

void TouchController::setDisplay(Sprite* dis) {
	// ����֮ǰ�������û��Ҳ����ν
	removeChildByTag(TAG_DISPLAY, true);
	addChild(dis, 0, TAG_DISPLAY);
}

CCSprite* TouchController::getDisplay(){
    return dynamic_cast<Sprite*>(this->getChildByTag(TAG_DISPLAY));
}

void TouchController::setEventId(int eventId) {
	m_iEventId = eventId;
}

int TouchController::getEventId() {
	return m_iEventId;
}

bool TouchController::selfCheck(Touch* ccTouch, TouchControllerEvent* lsTe) {
	bool bRef = false;
	// �ɵ����ļ�⣬����չ
	do {
		// �Ƿ�ͨ�����λ�ü��
		CC_BREAK_IF(!containsCCTouchPoint(ccTouch));
		// �Ƿ��������У��ų����ܴ����Ѿ��ӽ����Ƴ������ǲ�û���ͷŵĿ���
		CC_BREAK_IF(!isRunning());
		// �ж��Ƿ�����
		CC_BREAK_IF(!isVisible());
		// ������ܻ���Ҫ�ж��ڲ���ʾ��Ŀ�Ƿ�����
		///// ����
		bRef = true;
	} while (0);
	return bRef;
}

bool TouchController::containsCCTouchPoint(Touch* ccTouch) {
	// �����ʾ����
	Node* dis = getChildByTag(TAG_DISPLAY);
	Sprite* sprite = dynamic_cast<Sprite*>(dis);
	Point point = sprite->convertTouchToNodeSpaceAR(ccTouch);
	Size s = sprite->getTexture()->getContentSize();
	Rect rect = CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
	return rect.containsPoint(point);
}

bool TouchController::isParentAllVisible(TouchControllerEvent* lsTe) {
	bool bRef = true;
	// ����ת�ͣ��Ա��ȡ��ַ�Ƚ϶���TouchControllerEvent �Ķ������ͬʱֱ�ӻ��߼��̳� CCNode
	Node* nLsTe = dynamic_cast<Node*>(lsTe);

	Node* parent = getParent();
	do {
		// ���������ϣ�˵�� TouchController ���� TouchControllerEvent ֮��
		if (!parent) {
			bRef = false;
			break;
		}
		// ��� TouchController �� TouchControllerEvent ֮�ڣ����� true
		// ע�⣺�������TouchControllerEvent ���� ������ CCNode �ṹ֮�ڵ�Ԫ�أ���ȡ���˴��ж�
		if (nLsTe == parent) {
			break;
		}
		if (!parent->isVisible()) {
			bRef = false;
			break;
		}
		parent = parent->getParent();
	} while (1);
	return bRef;
}

TouchControllerEvent::TouchControllerEvent() {
	m_pTouchControlleres = Array::create();
	m_pTouchControlleres->retain();
}

TouchControllerEvent::~TouchControllerEvent() {
	m_pTouchControlleres->release();
}

void TouchControllerEvent::addTouchController(TouchController* touch, int eventId) {
	touch->setEventId(eventId);
	m_pTouchControlleres->addObject(touch);
}

void TouchControllerEvent::removeTouchController(TouchController* touch) {
	m_pTouchControlleres->removeObject(touch, true);
}

bool TouchControllerEvent::sendTouchMessage(Touch* ccTouch, int type) {
	// ��д�жϣ������е��ĸ�Ԫ�ؼ���ߣ��ʹ�����һ��
	TouchController* touchController = NULL;
	// ��õ���ĵ�
	CCObject* pObj = NULL;
	TouchController* lt = NULL;
	CCARRAY_FOREACH(m_pTouchControlleres, pObj) {
		lt = dynamic_cast<TouchController*>(pObj);
		if (lt) {
			if (lt->selfCheck(ccTouch, this)) {
				if (touchController == NULL)
					touchController = lt;
				else
					// ����Ѵ��ڷ�������Ԫ�أ��Ƚ����ȼ�
					touchController = getPriorityTouch(touchController, lt);
			}
		}
	}
    // ���� ����Ϊ��
    touchEventAction(touchController, type);
	return true;
}

TouchController* TouchControllerEvent::getPriorityTouch(TouchController* a, TouchController* b) {
	// �������ȼ�ͨ�� CCNode ���жϣ�Ҳ������ʾ��μ��������
	// �Ե�ǰԪ��Ϊ����������ת�ͣ��Ա��ȡ��ַ�Ƚ϶���TouchControllerEvent �Ķ������ͬʱֱ�ӻ��߼��̳� CCNode
	Node* nLsTe = dynamic_cast<Node*>(this);

	// ��ͬ�ķ�֦
	Node* allParent = NULL;
	// Ѱ�� a �� b ��ͬ�ķ�֦
	Node* nAParent = a;
	Node* nBParent = b;
	Node* nAChild = NULL;
	Node* nBChild = NULL;
	do {
		nAChild = nAParent;
		nAParent = nAParent->getParent();
		if (!nAParent)
			break;

		nBParent = b;
		do {
			nBChild = nBParent;
			nBParent = nBParent->getParent();
			if (!nBParent)
				break;
			if (nAParent == nBParent) {
				allParent = nAParent;
				break;
			}
			if (nBParent == nLsTe) {
				break;
			}
		} while (1);
		if (allParent)
			break;
		if (nAParent == nLsTe) {
			break;
		}
	} while (1);

	// �˴�ֻ��Ҫ�ж� nAChild �� nBChild �����ȼ����ɣ�Ĭ�Ϸ��� a
	if (!nAChild || !nBChild)
		return a;
	// ���� ZOrder �жϣ���� ZOrderһ������������λ���ж�
	if (nAChild->getZOrder() == nBChild->getZOrder())
		return allParent->getChildren()->indexOfObject(nAChild) > allParent->getChildren()->indexOfObject(nBChild)? a: b;
	else
		return nAChild->getZOrder() > nBChild->getZOrder()? a: b;
}