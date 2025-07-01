#pragma once

//�N���X�̐錾
class SceneBase;

class ScenManager
{
public:
	//�V�[���Ǘ�
	enum class SCENE_ID
	{
		NOME,
		TITLE,
		GAME,
	};

public:
	//�V���O���g���i�����E�擾�E�폜�j
	static void CreateInstance(void) {if (instance_ == nullptr){instance_ = new ScenManager();}}
	static ScenManager* GetInstance(void){return instance_;}
	static void DeleteInstance(void){if (instance_ != nullptr){delete instance_;instance_ = nullptr;}}

private:
	//�R���X�g���N�^
	ScenManager(void);
	//�f�X�N�g���N�^
	~ScenManager(void);

	//�ÓI�C���X�^���X
	static ScenManager* instance_;

public:
	void Init(void);	//������
	void Init3D(void);	//�RD�̏�����
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	void Release(void);	//���

	//��ԑJ��
	void ChangeScene(SCENE_ID nextld);

	//�V�[��ID�̎擾
	SCENE_ID GetSceneID(void) { return scendId_; }

	//�Q�[���I��
	void GameEnd(void) { isGameEnd_ - true; }

	//�Q�[���I���t���O�̎擾
	bool GetGameEnd(void) { return isGameEnd_; }

private:
	//�e��V�[��
	SceneBase* scene_;


	//�V�[��ID
	SCENE_ID scendId_;

	//�Q�[���I��
	bool isGameEnd_;
};
