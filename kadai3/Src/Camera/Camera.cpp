#include "Camera.h"
#include"../Input/InputManager.h"
#include"../Utility/AsoUtility.h"

Camera* Camera::instance_ = nullptr;

Camera::Camera(void)
{
}

Camera::~Camera(void)
{
}

void Camera::Init(void)
{
	pos_ = INIT_POS;
	angle_ = INIT_ANGLE;

}

void Camera::Update(void)
{
	////移動方向を決める
	//VECTOR moveDir = AsoUtility::VECTOR_ZERO;

	////前方向
	//if (InputManager::GetInstance()->IsNew(KEY_INPUT_I)){moveDir = AsoUtility::DIR_F;}

	////後方向
	//if (InputManager::GetInstance()->IsNew(KEY_INPUT_K)){moveDir = AsoUtility::DIR_B;}

	////後方向
	//if (InputManager::GetInstance()->IsNew(KEY_INPUT_J)){moveDir = AsoUtility::DIR_L;}

	////後方向
	//if (InputManager::GetInstance()->IsNew(KEY_INPUT_L)){moveDir = AsoUtility::DIR_R;}

	////移動量を計算する
	//VECTOR movePow = VScale(moveDir, MOVE_SPEED);

	////移動処理
	//pos_ = VAdd(pos_, movePow);

	////X軸の角度調節
	//float anglePowRad = AsoUtility::Deg2RadF(ANGLE_SPEED);
	//if (InputManager::GetInstance()->IsNew(KEY_INPUT_U))
	//{
	//	angle_.x += anglePowRad;
	//}
	//if (InputManager::GetInstance()->IsNew(KEY_INPUT_O))
	//{
	//	angle_.x -= anglePowRad;
	//}

	//座標を追従対象の位置に
	pos_.x = followPos_.x;
	pos_.z = followPos_.z - 1000.0f;
}

void Camera::SetBeforDraw(void)
{
	//クリップ距離を設定する
	SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);

	//カメラの位置設定
	SetCameraPositionAndAngle(
		pos_,
		angle_.x,
		angle_.y,
		angle_.z
	);
}

void Camera::DebugDraw(void)
{
	DrawFormatString(
		0,
		20,
		0xff0000,
		"カメラ座標(%2f,%2f,%2f)",
		pos_.x, pos_.y, pos_.z
	);
}

void Camera::Release(void)
{
}

void Camera::SetFollowPos(VECTOR pos)
{
	followPos_ = pos;
}
