#include "LayerChangeName.h"
#include "LayerMainPageA.h"

LayerChangeName::LayerChangeName()
{
}

LayerChangeName::~LayerChangeName()
{
	CC_SAFE_RELEASE(this->data);
	removeAllChildren();
}

LayerChangeName* LayerChangeName::create(MyLayout_N_M_P_OTHER * data)
{
	auto ly = new LayerChangeName();
	if (ly&&ly->init(data))
	{
		ly->autorelease();
		return ly;
	}
	CC_SAFE_DELETE(ly);
	return ly;
}

bool LayerChangeName::init(MyLayout_N_M_P_OTHER * data)
{
	if (!Layer::init())
	{
		return false;
	}
	lyChangeName = ui::Layout::create();
	this->addChild(lyChangeName);
	this->data = data;
	this->data->retain();
	EventListenerTouchOneByOne* touch = EventListenerTouchOneByOne::create();
	touch->onTouchBegan = CC_CALLBACK_2(LayerChangeName::onTouchBegan,this);
	touch->onTouchMoved = CC_CALLBACK_2(LayerChangeName::onTouchMoved, this);
	touch->onTouchEnded = CC_CALLBACK_2(LayerChangeName::onTouchEnded, this);

	//this->setSwallowsTouches(true);   // 这个语句无法吞噬触摸事件!  触摸事件的吞噬要用Listener
	touch->setSwallowTouches(true);   // 这个语句才是设置触摸吞噬;
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touch,this);   //  设置触摸优先级;

	Vec2 vec2 =data->getWorldPosition();
	btnChange = Button::create("btnWhite.jpg","btnWhite_Press.jpg");
	//btn->setContentSize(Size(100, 100));
	btnChange->setColor(Color3B::WHITE);
	btnChange->setPosition(Vec2(FRAMESIZE.width / 2, vec2.y));
	Label* lb = Label::createWithBMFont(CHINESE_FNT, "修改备注", TextHAlignment::CENTER);
	lb->setColor(Color3B::BLACK);
	btnChange->addChild(lb);
	lb->setPosition(Vec2(btnChange->getContentSize().width / 2, btnChange->getContentSize().height / 2));
	addChild(btnChange);
	btnChange->setSwallowTouches(true);
	btnChange->addTouchEventListener(CC_CALLBACK_2(LayerChangeName::changeNameBtnCallback, this));


	return true;
}

void LayerChangeName::changeNameBtnCallback(Ref* pSender, Widget::TouchEventType type )
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
	{
													   break;
	}
	case cocos2d::ui::Widget::TouchEventType::MOVED:
	{
													   isBtnChangeMoved = true;
													   break;
	}
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
	{
														  if (!isBtnChangeMoved)
														  {
															  log("changeName call");
															  EditBox *editBox = EditBox::create(Size(200, 40), "EditBg.jpg");
															  editBox->setFont("Arial", 32);
															  editBox->setFontColor(Color4B::BLACK);
															  layerEdit = Layer::create();
															 
															/*  layerSwallow->setSwallowsTouches(true);
															  EventListenerTouchOneByOne*listener2 = EventListenerTouchOneByOne::create();*/

															  editBox->setPlaceHolder("please outPut");   //提示文本.默认灰色
															  editBox->setPlaceholderFont("Arial",32);
															  editBox->setPosition(Vec2(btnChange->getWorldPosition().x, btnChange->getWorldPosition().y + FRAMESIZE.height / 20));
															  editBox->setInputMode(EditBox::InputMode::SINGLE_LINE);
															  editBox->setReturnType(EditBox::KeyboardReturnType::DONE);
															  editBox->setDelegate(this);
															  addChild(editBox);

															  btnChange->setEnabled(false);
															  btnChange->setVisible(false);
															  isBtnChangeMoved = false;
														  }
														  isBtnChangeMoved = false;
														break;
	}
	}
}

bool LayerChangeName::onTouchBegan(Touch *touch, Event *unused_event)
{
	log("chanName Layer onTouchBegan");
	return true;
}

void LayerChangeName::onTouchMoved(Touch *touch, Event *unused_event)
{
	isLayerCancel = true;
}

void LayerChangeName::onTouchEnded(Touch *touch, Event *unused_event)
{
	if (!isLayerCancel)
	{
		EventCustom ev = EventCustom("TouchRecover");
		_eventDispatcher->dispatchEvent(&ev);
	}
	else
	{
		isLayerCancel = false;
	}
}


void LayerChangeName::editBoxEditingDidBegin(EditBox* editBox)
{
	log("editBoxEditingDidBegin");
	editBox->setText("outPut");
}

void LayerChangeName::editBoxReturn(EditBox* editBox)  //特指在键盘中按下return后;  要再给编辑框配一个确定或取消按钮;
{
	log("editBoxReturn");
	//EventCustom ev = EventCustom("TouchRecover");    在这里调用这个语句会造成线程冲突
	//_eventDispatcher->dispatchEvent(&ev);
}

void LayerChangeName::editBoxTextChanged(EditBox* editBox, const std::string& text)
{
	log("TextChanged");
	//可以用来检测输入长度;
}




