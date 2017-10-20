#ifndef __TitleScene_SCENE_H__
#define __TitleScene_SCENE_H__

#include "tinyxml2/tinyxml2.h"
#include "cocos2d.h"
#include "SystemHead.h"
#include "GameProgress.h"
#include "MyUtils.h"


class TitleScene : public cocos2d::Layer
{
private:
	Label * LabelRestart;
	Label * LabelContinue;
	GameProgress * PGameProgress;
	~TitleScene();
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(TitleScene);
	cocos2d::Node* test;

	void SceneGameSelect(float dt);
	void ToSceneGame();
	//����������Ϸ��ʼ����,Ԥ���غú���û�ɫ������ʾ���Դ���;
	bool onTouchBegan(Touch *touch, Event *unused_event);

};

#endif // __TitleScene_SCENE_H__
