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
	//���f���̑傫��
	scale_ = SCALE;
	MV1SetScale(modelId_, scale_);

	//���f���̊p�x
	angle_ = AsoUtility::VECTOR_ZERO;
	MV1SetRotationXYZ(modelId_, angle_);

	//���f���̍��W
	pos_ = INIT_POS;
	MV1SetPosition(modelId_, pos_);

	//���Ȕ��s
	MV1SetMaterialAmbColor(modelId_, 0, EMI_COLOR);

	//�W�����v�̏�����
	junpPow_ = 0.0f;

	//�A�j���[�V����
	prevAnimType_ = ANIM_TYPE::IDLE;
	nowAnimType_ = ANIM_TYPE::IDLE;
	attachNo_ = 0;
	nowAnimTime_ = 0;
	totalAnimTime_ = 0;
}

void Player::Load(void)
{
	//���f���̃��[�h
	modelId_ = MV1LoadModel("Data/Model/Player/Player.mv1");
}

void Player::LoadEnd(void)
{
	//������
	Init();

	//�A�j���[�V�����̏�����
	attachNo_ = MV1AttachAnim(modelId_, static_cast<int>(nowAnimType_));

	//�A�j���[�V�����̂����Đ����Ԃ��擾
	totalAnimTime_ = MV1GetAttachAnim(modelId_, attachNo_);
}

void Player::Update(void)
{
	//�ړ�����
	ProsessMove();

	//�W�����v����	
	ProcessJump();

	//�A�j���[�V�����̍X�V
	UpdateAnim();

	//�J�����ɍ��W��n��
	Camera::GetInstance()->SetFollowPos(pos_);
}

void Player::Draw(void)
{
	//���f���̕`��
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
	//�Փ˂��Ė߂��ʒu
	pos_ = pos;
	junpPow_ = 0.0f;
}

void Player::ProsessMove(void)
{
	//�ړ����������߂�
	VECTOR moveDir = AsoUtility::VECTOR_ZERO;

	//�����
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_W))
	{
		moveDir = AsoUtility::DIR_F;
	}
	//������
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_S))
	{
		moveDir = AsoUtility::DIR_B;
	}
	//������
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_A))
	{
		moveDir = AsoUtility::DIR_L;
	}
	//�E����
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_D))
	{
		moveDir = AsoUtility::DIR_R;
	}
	
	//�ړ����Ă�����
	if (!AsoUtility::EqualsVZero(moveDir))
	{
		//���f���̈ړ�������Y����]������
		//�������p�x�i���W�A���j�ɕύX����
		angle_.y = atan2(moveDir.x, moveDir.z);

		//���f�������]���Ă���̂ŋ����I�ɉ�]������
		angle_.y += AsoUtility::Deg2RadF(180.0f);

		//���f���ɉ�]��ݒ肷��
		MV1SetRotationXYZ(modelId_, angle_);

		//�ړ��ʂ��v�Z����i�������X�s�[�h�j
		VECTOR movePow = VScale(moveDir, MOVE_SPEED);

		//�ړ�����
		pos_ = VAdd(pos_, movePow);

		//���f�������W�̂ɐݒ肷��
		MV1SetPosition(modelId_, pos_);

		//�A�j���[�V������ύX����
		nowAnimType_ = ANIM_TYPE::WALK;
	}
	//�ړ����Ă��Ȃ�
	else
	{
		//�ړ����Ă��Ȃ�
		

		//�A�j���[�V������ύX����
		nowAnimType_ = ANIM_TYPE::IDLE;
	}
}

void Player::ProcessJump(void)
{
	//�d��
	junpPow_ -= GRAVITY;
	
	//�v���C���[�̍��W�ɃW�����v�͂����Z����
	pos_.y += junpPow_;

	//�Փ˔���̗�������
	if (pos_.y < -1000.0f)
	{
		//������
		Init();
	}

	//���f���ɍ��W��ݒ肷��
	MV1SetPosition(modelId_, pos_);
}

void Player::UpdateAnim(void)
{
	//�A�j���[�V�������ύX���ꂽ�H
	if (prevAnimType_ != nowAnimType_)
	{
		//�A�j���[�V������ʂ����킹��
		prevAnimType_ = nowAnimType_;

		//���f������O��̃A�j���[�V�������O��
		MV1DetachAnim(modelId_, attachNo_);

		//�A�j���[�V������ύX����
		attachNo_ = MV1AttachAnim(modelId_, static_cast<int>(nowAnimType_));

		//�A�j���[�V�����̂����Đ����Ԃ��擾	
		totalAnimTime_ = MV1GetAnimTotalTime(modelId_, attachNo_);

		//�A�j���[�V�������Ԃ�������
		nowAnimTime_ = 0.0f;
	}

	//�A�j���[�V�����̎��Ԃ�i�߂�
	nowAnimTime_ += 1.0f;

	//�A�j���[�V���������[�v
	if (nowAnimTime_ > totalAnimTime_)
	{
		nowAnimTime_ = 0.0f;
	}

	//�A�j���[�V�����̐ݒ�
	MV1SetAttachAnimTime(modelId_, attachNo_, nowAnimTime_);
}
