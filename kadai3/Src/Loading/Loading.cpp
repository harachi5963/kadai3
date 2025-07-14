#include "Loading.h"
#include<DxLib.h>
#include"../Application/Application.h"

Loading* Loading::instance_ = nullptr;

//最低でも表示する時間
static constexpr int MIN_LOAD_TIME = 60;	

Loading::Loading(){}
Loading::~Loading(){}

void Loading::Init(void)
{
	loadTimer_ = 0;
	isLoading_ = false;
	posX_ = Application::SCREEN_SIZE_X / 2;
	posY_ = Application::SCREEN_SIZE_Y / 2;
}

void Loading::Load(void)
{
	handle_ = LoadGraph("Data/Image/load.png");
}

void Loading::Update(void)
{
	loadTimer_++;

	//読み込み中のものがなくなったら
	if (GetASyncLoadNum() == 0 && loadTimer_>=MIN_LOAD_TIME)
	{
		//ロード終了
		Init();
	}
	//読み込み中
	else
	{
		//ロード画面で亜予備を入れられるならここに記述
	}
}

void Loading::Draw(void)
{
	DrawRotaGraph(
		posX_, posY_,	//座標
		1.0,			//拡大地
		0.0,			//回転地
		handle_,		//画像ハンドル
		true			//透過フラグ
	);
}

void Loading::Release(void)
{
	DeleteGraph(handle_);
}

void Loading::StartAsyncLoad(void)
{
	isLoading_ = true;
	SetUseASyncLoadFlag(true);
}

void Loading::EndAsyncLoad(void)
{
	SetUseASyncLoadFlag(false);
}

bool Loading::IsLoading(void)
{
	return isLoading_;
}
