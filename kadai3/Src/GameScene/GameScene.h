#pragma once
#include"../TitleScene/TitleScene.h"

//�x�[�X���p��
class GameScene :public SceneBase
{
public:
	GameScene();                        //�R���X�g���N�^
	~GameScene()			override;   //�f�X�g���N�g

    // ������
    void Init(void)         override;

    //�ǂݍ���
    void Load(void)         override;

    //�ǂݍ��݌�
    void LoadEnd(void)      override;

    //�X�V
    void Update(void)       override;

    // �`��
    void Draw(void)         override;

    // �폜
    void Release(void)       override;
};