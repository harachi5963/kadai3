#pragma once
#include <DxLib.h>
#include"Block.h"

class Stage
{
public:
	//�u���b�N�̃��f�����
	static constexpr int BLOCK_MODEL_NUM = static_cast<int>(Block::TYPE::MAX);

	//�u���b�N�̍H���i�}�b�v�T�C�Y�j
	static constexpr int BLOCK_NUM_X = 20;
	static constexpr int BLOCK_NUM_Z = 20;

public:
	Stage(void);
	~Stage(void);

	void Init(void);	//������
	void Load(void);	//�ǂ݂���
	void LOadEnd(void);	//�ǂ݂��݌�
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	void Release(void);	//���

	//�����ƃu���b�N�̏Փ˔���
	bool IsCollLine(
		VECTOR topPos, VECTOR downPos, MV1_COLL_RESULT_POLY* result
	);

private:
	//�}�b�v�f�[�^�ǂݍ���
	void LoadMapCsvData(void);

private:
	//�u���b�N�̃I���W�i���n���h��
	int blockOriginModeleId_[BLOCK_MODEL_NUM];

	//�u���b�N�N���X
	Block* blocks_[BLOCK_NUM_Z][BLOCK_NUM_X];
};