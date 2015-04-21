//
//  GameStartScene.cpp
//
//

#include "GameStartScene.h"
#include "PlayScene.h"

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
	//Layer* layer = Layer::create();
	//auto rootNode =  CSLoader::createNode("LevelSelection.csb");//传入Studio2.x的资源路径 
	//layer->addChild(rootNode);//假设this是即将显示的scene 
	//this->addChild(layer);
	//button_start = dynamic_cast<Button*>(rootNode->getChildByTag(39));  
	//button_left = dynamic_cast<Button*>(rootNode->getChildByTag(40));  
	//button_right = dynamic_cast<Button*>(rootNode->getChildByTag(41));  

	//button_start->addTouchEventListener(CC_CALLBACK_2(GameStart::startCallback, this));
	//button_left->addTouchEventListener(CC_CALLBACK_2(GameStart::leftCallback, this));
	//button_right->addTouchEventListener(CC_CALLBACK_2(GameStart::rightCallback, this));

	// Create the page view
	Size widgetSize = this->getContentSize();
	pageView = PageView::create();
	pageView->setContentSize(Size(widgetSize.width, widgetSize.height));
	pageView->setAnchorPoint(Vec2(0,0));
	pageView->setPosition(Vec2(0 ,0));

	int pageCount = 6;
	for (int i = 0; i < pageCount; ++i)
	{
		HBox* outerBox = HBox::create();
		outerBox->setContentSize(Size(widgetSize.width, widgetSize.height));
		outerBox->setAnchorPoint(Vec2(0,0));
		outerBox->setPosition(Vec2(0 ,0));
		outerBox->setBackGroundImage(StringUtils::format("Backgrounds/back_%d.png",i+1));

		Sprite* sprite = Sprite::create(StringUtils::format("LevelSelection/thumb%d.png",i+1));
		sprite->setPosition(Vec2(widgetSize.width/2, widgetSize.height/3));
		outerBox->addChild(sprite);

		auto actionUp = JumpBy::create(2, Vec2(0,0), 80, 4);
		RepeatForever* act = RepeatForever::create(actionUp);
		sprite->runAction(act);

		pageView->insertPage(outerBox,i);
	}

	pageView->addEventListener(CC_CALLBACK_2(GameStart::pageViewEvent, this));
	pageView->setName("pageView");
	this->addChild(pageView);

	Button *btn_left = Button::create("LevelSelection/LS01.png","LevelSelection/LS02.png","LevelSelection/LS03.png");
	btn_left->setPosition(Vec2(widgetSize.width/6, widgetSize.height/3));
	this->addChild(btn_left);
	btn_left->setName(StringUtils::format("btn_left"));
	btn_left->setGlobalZOrder(1);
	btn_left->addTouchEventListener( CC_CALLBACK_2(GameStart::leftCallback, this));

	Button *btn_right = Button::create("LevelSelection/LS01.png","LevelSelection/LS02.png","LevelSelection/LS03.png");
	auto a1 = RotateBy::create(0.0f, 180);
	btn_right->runAction(Sequence::create(a1, nullptr));
	btn_left->setGlobalZOrder(1);
	btn_right->setPosition(Vec2(widgetSize.width-widgetSize.width/6, widgetSize.height/3));
	this->addChild(btn_right);
	
	btn_right->setName(StringUtils::format("btn_right"));
	btn_right->addTouchEventListener( CC_CALLBACK_2(GameStart::rightCallback, this));

	Button *btn_start = Button::create("LevelSelection/LS07.png","LevelSelection/LS08.png","LevelSelection/LS09.png");
	btn_start->setPosition(Vec2(widgetSize.width/2, widgetSize.height/8));
	this->addChild(btn_start);
	btn_left->setGlobalZOrder(1);
	btn_start->setName(StringUtils::format("btn_start"));
	btn_start->addTouchEventListener( CC_CALLBACK_2(GameStart::startCallback, this));
	
	return true;
}

void GameStart::pageViewEvent(Ref *pSender, PageView::EventType type)
{
	switch (type)
	{
	case PageView::EventType::TURNING:
		{
			PageView* pageView = dynamic_cast<PageView*>(pSender);
			log(CCString::createWithFormat("page = %ld", pageView->getCurPageIndex() + 1)->getCString());
		}
		break;

	default:
		break;
	}
}

//
//void GameStart::onButtonClicked(Ref* sender, Widget::TouchEventType type)
//{	
//	Button* btn = static_cast<Button*>(sender);
//	log("button %s clicked",btn->getName().c_str());
//	auto actionBy = JumpBy::create(2.0f, Vec2(0,0), 80, 4);
//	auto actionByBack = actionBy->reverse();
//	Sequence* act = Sequence::create(actionBy, actionByBack, nullptr);
//	btn->runAction(act);
//
//}
void GameStart::startCallback(Ref* sender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		Director::getInstance()->replaceScene(Play::createScene(1,pageView->getCurPageIndex() + 1));
	}
}

void GameStart::leftCallback(Ref* sender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		//CCDirector::getInstance()->replaceScene(UISceneManager::sharedUISceneManager()->previousUIScene());
	}
}


void GameStart::rightCallback(Ref* sender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		//CCDirector::getInstance()->replaceScene(UISceneManager::sharedUISceneManager()->previousUIScene());
	}
}
