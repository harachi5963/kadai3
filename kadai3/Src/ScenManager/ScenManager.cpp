#include "ScenManager.h"
#include <DxLib.h>
#include"../TitleScene/TitleScene.h"
#include"../GameScene/GameScene.h"

ScenManager*ScenManager::instance_ = nullptr;

ScenManager::ScenManager(void)
{
}

ScenManager::~ScenManager(void)
{
}

void ScenManager::Init(void)
{
	Init3D();

	//最初はタイトルシーンから
	ChangeScene(SCENE_ID::TITLE);
}

void ScenManager::Init3D(void)
{
	//背景色設定
	SetBackgroundColor(0, 0, 0);

	//Ｚブッファを有効にする
	SetUseZBuffer3D(true);

	//Zブッファへの書き込みを有効にする
	SetWriteZBuffer3D(true);

	//バックカリングを有効にする
	SetUseBackCulling(true);

	//ライトの設定
	SetUseLighting(true);

	//正面から斜め下に向かったライト
	ChangeLightTypeDir({ 0.0f,-1.0f,1.0f });
}

void ScenManager::Update(void)
{

	//現在のシーンを更新
	scene_->Update();
}

void ScenManager::Draw(void)
{
	//現在のシーンを描画
	scene_->Draw();
}

void ScenManager::Release(void)
{
	//現在のシーンを解放・削除(
	scene_->Release();
	delete scene_;
}

void ScenManager::ChangeScene(SCENE_ID nextld)
{
	//シーンを変更する
	scendId_ = nextld;

	//現在のシーンを開放
	if (scene_ != nullptr)
	{
		scene_->Release();	//現在のシー解放
		delete scene_;		//シーンの削除
	}

	//各シーンに切り替え
	switch (scendId_)
	{
	case ScenManager::SCENE_ID::NOME:
		break;
	case ScenManager::SCENE_ID::TITLE:
		scene_ = new TitleScene();
		break;
	case ScenManager::SCENE_ID::GAME:
		scene_ = new GameScene();
		break;
	default:
		break;
	}

	//初期化
	scene_->Init();
	scene_->Load();
}
