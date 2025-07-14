#include "Block.h"

Block::Block()
{
}

Block::~Block()
{
}

void Block::Create(TYPE type, int modelId, int mapX, int mapZ)
{
	//�N���b�N�̎��
	type_ = type;

	//���f���̕���
	modelId_ = MV1DuplicateModel(modelId);

	//���Ȕ���
	MV1SetMaterialEmiColor(modelId_, 0, EMI_COLOR);
	
	//�傫���ݒ�
	scale_ = SCALE;
	MV1SetScale(modelId_, scale_);

	//�P�u���b�N������̔����̑傫��
	const float HALF_BLOCK_SIZE = SIZE * 0.5f;

	//�����Ŏw�肳�ꂽ�}�b�v���W������W���v�Z����
	//�RD���f���̒��S���W�́A�u���b�N�̒��S
	float x = static_cast<float>(mapX);
	float z = static_cast<float>(mapZ);

	//���W�̐ݒ�
	pos_ = VGet(
		(SIZE * x) + HALF_BLOCK_SIZE,
		-HALF_BLOCK_SIZE,
		(SIZE * z) + HALF_BLOCK_SIZE
	);
	MV1SetPosition(modelId_, pos_);
	//�Փ˔���
	MV1SetupCollInfo(modelId_, -1);
}



void Block::Uopdate(void)
{
}

void Block::Draw(void)
{
	//���f���̕`��
	MV1DrawModel(modelId_);
}

void Block::Release(void)
{
	//���f���̉��
	MV1DeleteModel(modelId_);
}

int Block::GEtModelId(void)
{
	return modelId_;
}
