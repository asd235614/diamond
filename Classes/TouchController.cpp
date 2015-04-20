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
	// 设置之前先清除，没有也无所谓
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
	// 可点击项的检测，可扩展
	do {
		// 是否通过点击位置检测
		CC_BREAK_IF(!containsCCTouchPoint(ccTouch));
		// 是否正在运行，排除可能存在已经从界面移除，但是并没有释放的可能
		CC_BREAK_IF(!isRunning());
		// 判断是否隐藏
		CC_BREAK_IF(!isVisible());
		// 这里可能还需要判断内部显示项目是否隐藏
		///// 暂留
		bRef = true;
	} while (0);
	return bRef;
}

bool TouchController::containsCCTouchPoint(Touch* ccTouch) {
	// 获得显示内容
	Node* dis = getChildByTag(TAG_DISPLAY);
	Sprite* sprite = dynamic_cast<Sprite*>(dis);
	Point point = sprite->convertTouchToNodeSpaceAR(ccTouch);
	Size s = sprite->getTexture()->getContentSize();
	Rect rect = CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
	return rect.containsPoint(point);
}

bool TouchController::isParentAllVisible(TouchControllerEvent* lsTe) {
	bool bRef = true;
	// 向父类转型，以便获取地址比较对象，TouchControllerEvent 的对象必须同时直接或者简介继承 CCNode
	Node* nLsTe = dynamic_cast<Node*>(lsTe);

	Node* parent = getParent();
	do {
		// 如果遍历完毕，说明 TouchController 不再 TouchControllerEvent 之内
		if (!parent) {
			bRef = false;
			break;
		}
		// 如果 TouchController 在 TouchControllerEvent 之内，返回 true
		// 注意：如果想让TouchControllerEvent 处理 不在其 CCNode 结构之内的元素，则取消此处判断
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
	// 编写判断，集合中的哪个元素级别高，就触发哪一个
	TouchController* touchController = NULL;
	// 获得点击的点
	CCObject* pObj = NULL;
	TouchController* lt = NULL;
	CCARRAY_FOREACH(m_pTouchControlleres, pObj) {
		lt = dynamic_cast<TouchController*>(pObj);
		if (lt) {
			if (lt->selfCheck(ccTouch, this)) {
				if (touchController == NULL)
					touchController = lt;
				else
					// 如果已存在符合条件元素，比较优先级
					touchController = getPriorityTouch(touchController, lt);
			}
		}
	}
    // 返回 可以为空
    touchEventAction(touchController, type);
	return true;
}

TouchController* TouchControllerEvent::getPriorityTouch(TouchController* a, TouchController* b) {
	// 触摸优先级通过 CCNode 树判断，也既是显示层次级别等因素
	// 以当前元素为“根”向父类转型，以便获取地址比较对象，TouchControllerEvent 的对象必须同时直接或者简介继承 CCNode
	Node* nLsTe = dynamic_cast<Node*>(this);

	// 共同的分枝
	Node* allParent = NULL;
	// 寻找 a 与 b 共同的分枝
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

	// 此处只需要判断 nAChild 和 nBChild 的优先级即可，默认返回 a
	if (!nAChild || !nBChild)
		return a;
	// 根据 ZOrder 判断，如果 ZOrder一样，根据索引位置判断
	if (nAChild->getZOrder() == nBChild->getZOrder())
		return allParent->getChildren()->indexOfObject(nAChild) > allParent->getChildren()->indexOfObject(nBChild)? a: b;
	else
		return nAChild->getZOrder() > nBChild->getZOrder()? a: b;
}