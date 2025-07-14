#include "GameScene.h"
#include<DxLib.h>
#include"../Object/Grid/Grid.h"
#include "../Camera/Camera.h"
#include"../Object/Stage/Stage.h"
#include"../Object/Player/Player.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Init(void)
{
	//グリッドの初期化
	grid_->Init();

	//カメラの初期化
	Camera::GetInstance()->Init();

	//ステージの初期化
	stage_->Init();

	//プレイヤーの初期化
	player_->Init();
}

void GameScene::Load(void)
{
	//グリッドの生成
	grid_=new Grid();
	
	//カメラの生成
	Camera::CreateInstance();

	//ステージの生成
	stage_ = new Stage();
	stage_->Load();

	//プレイヤーの生成
	player_ = new Player();
	player_->Load();
}

void GameScene::LoadEnd(void)
{
	//初期化
	Init();

	//ステージの読み込み後
	stage_->LOadEnd();

	//プレイヤーの読み込み後
	player_->LoadEnd();
}

void GameScene::Update(void)
{
	//グリッドの更新
	grid_->Update();

	//カメラの更新
	Camera::GetInstance()->Update();

	//ステージの更新
	stage_->Update();

	//プレイヤーの更新
	player_->Update();

	//衝突判定
	Collision();
}

void GameScene::Draw(void)
{
	//グリッドの描画
	grid_->Draw();

	//カメラの描画
	Camera::GetInstance()->SetBeforDraw();
	Camera::GetInstance()->DebugDraw();

	//ステージの描画
	stage_->Draw();

	//プレイヤーの描画
	player_->Draw();
}

void GameScene::Release(void)
{
	grid_->Release();
	delete grid_;

	//カメラの解放
	Camera::GetInstance()->Release();
	Camera::DeleteInstance();

	//ステージの解放
	stage_->Release();
	delete stage_;

	//プレイヤーの解放
	player_->Release();
	delete player_;
}

void GameScene::DebugDraw(void)
{
}

void GameScene::Collision(void)
{
	//ステージとプレイヤーの当たり判定
	CollisionStage();
}

void GameScene::CollisionStage(void)
{
	//プレイヤーの座標を取得
	VECTOR playerPos = player_->GetPos();

	//線分の上座標
	VECTOR topPos = playerPos;
	topPos.y = playerPos.y + (Player::COLL_LINE_LEN * 1.0f);

	//線分の下座標
	VECTOR downPos = playerPos;
	downPos.y = playerPos.y - Player::COLL_LINE_LEN ;

	//デバック用に確保
	lineTopPos_ = topPos;
	lineDownPos_ = downPos;

	//線分とブロックの衝突判定
	MV1_COLL_RESULT_POLY result;

	//当たっているか？
	if (stage_->IsCollLine(topPos, downPos, &result))
	{
		//プレイヤーに衝突座標を渡す
		player_->CollisionStage(result.HitPosition);
	}
}


