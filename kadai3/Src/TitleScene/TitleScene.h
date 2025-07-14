#pragma once
#include <DxLib.h>
#include "../Scene/SceneBase.h"

//�x�[�X���p��
class TitleScene : public SceneBase
{
public:
    TitleScene(void);                //�R���X�g���N�^
    ~TitleScene(void) override;        //�f�X�g���N�^

    // ������
    void Init(void) override;

    //�ǂݍ���
    void Load(void) override;

    //�ǂݍ��݌�
    void LoadEnd(void) override;

    //�X�V
    void Update(void) override;

    // �`��
    void Draw(void) override;

    // �폜
    void Release(void) override;

    //���̃V�[����
    void toNextScene(void);

private:
    int handle_;
};