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

	//�ŏ��̓^�C�g���V�[������
	ChangeScene(SCENE_ID::TITLE);
}

void ScenManager::Init3D(void)
{
	//�w�i�F�ݒ�
	SetBackgroundColor(0, 0, 0);

	//�y�u�b�t�@��L���ɂ���
	SetUseZBuffer3D(true);

	//Z�u�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(true);

	//�o�b�N�J�����O��L���ɂ���
	SetUseBackCulling(true);

	//���C�g�̐ݒ�
	SetUseLighting(true);

	//���ʂ���΂߉��Ɍ����������C�g
	ChangeLightTypeDir({ 0.0f,-1.0f,1.0f });
}

void ScenManager::Update(void)
{

	//���݂̃V�[�����X�V
	scene_->Update();
}

void ScenManager::Draw(void)
{
	//���݂̃V�[����`��
	scene_->Draw();
}

void ScenManager::Release(void)
{
	//���݂̃V�[��������E�폜(
	scene_->Release();
	delete scene_;
}

void ScenManager::ChangeScene(SCENE_ID nextld)
{
	//�V�[����ύX����
	scendId_ = nextld;

	//���݂̃V�[�����J��
	if (scene_ != nullptr)
	{
		scene_->Release();	//���݂̃V�[���
		delete scene_;		//�V�[���̍폜
	}

	//�e�V�[���ɐ؂�ւ�
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

	//������
	scene_->Init();
	scene_->Load();
}
