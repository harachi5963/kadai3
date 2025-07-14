#include "Player.h"
#include"../../Utility/AsoUtility.h"
#include"../../Input/InputManager.h"
#include"../../Camera/Camera.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(void)
{
	//モデルの大きさ
	scale_ = SCALE;
	MV1SetScale(modelId_, scale_);

	//モデルの角度
	angle_ = AsoUtility::VECTOR_ZERO;
	MV1SetRotationXYZ(modelId_, angle_);

	//モデルの座標
	pos_ = INIT_POS;
	MV1SetPosition(modelId_, pos_);

	//自己発行
	MV1SetMaterialAmbColor(modelId_, 0, EMI_COLOR);

	//ジャンプの初期化
	junpPow_ = 0.0f;

	//アニメーション
	prevAnimType_ = ANIM_TYPE::IDLE;
	nowAnimType_ = ANIM_TYPE::IDLE;
	attachNo_ = 0;
	nowAnimTime_ = 0;
	totalAnimTime_ = 0;
}

void Player::Load(void)
{
	//モデルのロード
	modelId_ = MV1LoadModel("Data/Model/Player/Player.mv1");
}

void Player::LoadEnd(void)
{
	//初期化
	Init();

	//アニメーションの初期化
	attachNo_ = MV1AttachAnim(modelId_, static_cast<int>(nowAnimType_));

	//アニメーションのそう再生時間を取得
	totalAnimTime_ = MV1GetAttachAnim(modelId_, attachNo_);
}

void Player::Update(void)
{
	//移動操作
	ProsessMove();

	//ジャンプ操作	
	ProcessJump();

	//アニメーションの更新
	UpdateAnim();

	//カメラに座標を渡す
	Camera::GetInstance()->SetFollowPos(pos_);
}

void Player::Draw(void)
{
	//モデルの描画
	MV1DrawModel(modelId_);
}

void Player::Release(void)
{
	MV1DeleteModel(modelId_);
}

VECTOR Player::GetPos(void)
{
	return pos_;
}

void Player::CollisionStage(VECTOR pos)
{
	//衝突して戻す位置
	pos_ = pos;
	junpPow_ = 0.0f;
}

void Player::ProsessMove(void)
{
	//移動方向を決める
	VECTOR moveDir = AsoUtility::VECTOR_ZERO;

	//上方向
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_W))
	{
		moveDir = AsoUtility::DIR_F;
	}
	//下方向
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_S))
	{
		moveDir = AsoUtility::DIR_B;
	}
	//左方向
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_A))
	{
		moveDir = AsoUtility::DIR_L;
	}
	//右方向
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_D))
	{
		moveDir = AsoUtility::DIR_R;
	}
	
	//移動していたら
	if (!AsoUtility::EqualsVZero(moveDir))
	{
		//モデルの移動方向にY軸回転させる
		//方向を角度（ラジアン）に変更する
		angle_.y = atan2(moveDir.x, moveDir.z);

		//モデルが反転しているので強制的に回転させる
		angle_.y += AsoUtility::Deg2RadF(180.0f);

		//モデルに回転を設定する
		MV1SetRotationXYZ(modelId_, angle_);

		//移動量を計算する（方向＊スピード）
		VECTOR movePow = VScale(moveDir, MOVE_SPEED);

		//移動処理
		pos_ = VAdd(pos_, movePow);

		//モデルを座標のに設定する
		MV1SetPosition(modelId_, pos_);

		//アニメーションを変更する
		nowAnimType_ = ANIM_TYPE::WALK;
	}
	//移動していない
	else
	{
		//移動していない
		

		//アニメーションを変更する
		nowAnimType_ = ANIM_TYPE::IDLE;
	}
}

void Player::ProcessJump(void)
{
	//重力
	junpPow_ -= GRAVITY;
	
	//プレイヤーの座標にジャンプ力を加算する
	pos_.y += junpPow_;

	//衝突判定の落下制御
	if (pos_.y < -1000.0f)
	{
		//初期化
		Init();
	}

	//モデルに座標を設定する
	MV1SetPosition(modelId_, pos_);
}

void Player::UpdateAnim(void)
{
	//アニメーションが変更された？
	if (prevAnimType_ != nowAnimType_)
	{
		//アニメーション種別を合わせる
		prevAnimType_ = nowAnimType_;

		//モデルから前回のアニメーションを外す
		MV1DetachAnim(modelId_, attachNo_);

		//アニメーションを変更する
		attachNo_ = MV1AttachAnim(modelId_, static_cast<int>(nowAnimType_));

		//アニメーションのそう再生時間を取得	
		totalAnimTime_ = MV1GetAnimTotalTime(modelId_, attachNo_);

		//アニメーション時間を初期化
		nowAnimTime_ = 0.0f;
	}

	//アニメーションの時間を進める
	nowAnimTime_ += 1.0f;

	//アニメーションをループ
	if (nowAnimTime_ > totalAnimTime_)
	{
		nowAnimTime_ = 0.0f;
	}

	//アニメーションの設定
	MV1SetAttachAnimTime(modelId_, attachNo_, nowAnimTime_);
}
