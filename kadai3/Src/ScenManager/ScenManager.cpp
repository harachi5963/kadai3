#include "ScenManager.h"
#include <DxLib.h>
#include"../TitleScene/TitleScene.h"
#include"../GameScene/GameScene.h"

#include"../Loading/Loading.h"

ScenManager*ScenManager::instance_ = nullptr;

ScenManager::ScenManager(void){}
ScenManager::~ScenManager(void){}

void ScenManager::Init(void)
{
	//ロード画面生成
	Loading::CreateInstance();
	Loading::GetInstance()->Load();
	Loading::GetInstance()->Init();

	//３D情報の初期化
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
	//ロード中
	if (Loading::GetInstance()->IsLoading())
	{
		//ロード更新
		Loading::GetInstance()->Update();

		//ロードが終了していたら
		if (Loading::GetInstance()->IsLoading() == false)
		{
			//ロード後の初期化
			scene_->LoadEnd();
		}
	}
	//通常の更新処理
	else
	{
		//現在のシーンを更新
		scene_->Update();
	}
}

void ScenManager::Draw(void)
{
	//ロード中ならロード画面を描画
	if(Loading::GetInstance()->IsLoading())
	{ 
		//ロード画面
		Loading::GetInstance()->Draw();
	}
	//通常の描画
	else
	{
		//現在のシーンを描画
		scene_->Draw();
	}
}

void ScenManager::Release(void)
{
	//現在のシーンを解放・削除(
	scene_->Release();
	delete scene_;

	//ロード画面の解放
	Loading::GetInstance()->Release();
	Loading::DeleteInstance();
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
	Loading::GetInstance()->StartAsyncLoad();
	scene_->Load();
	Loading::GetInstance()->EndAsyncLoad();
}
