#pragma once
#include"../TitleScene/TitleScene.h"
#include<DxLib.h>

//�N���X�̑O���錾
class Grid;
class Stage;
class Player;

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

private:
    //�f�o�b�N�`��
    void DebugDraw(void);
    
    //���̃f�o�b�N�\��
    VECTOR lineTopPos_;
    VECTOR lineDownPos_;

    //�Փ˔���
    void Collision(void);

    //�X�e�[�W�ƃv���C���[�̏Փ˔���
    void CollisionStage(void);

private:
    Grid* grid_;    //�O���b�h�N���X

    Stage* stage_;
    Player* player_;
};