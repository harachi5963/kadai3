#include "Block.h"

Block::Block()
{
}

Block::~Block()
{
}

void Block::Create(TYPE type, int modelId, int mapX, int mapZ)
{
	//クロックの種類
	type_ = type;

	//モデルの複製
	modelId_ = MV1DuplicateModel(modelId);

	//自己発光
	MV1SetMaterialEmiColor(modelId_, 0, EMI_COLOR);
	
	//大きさ設定
	scale_ = SCALE;
	MV1SetScale(modelId_, scale_);

	//１ブロックあたりの半分の大きさ
	const float HALF_BLOCK_SIZE = SIZE * 0.5f;

	//引数で指定されたマップ座標から座標を計算する
	//３Dモデルの中心座標は、ブロックの中心
	float x = static_cast<float>(mapX);
	float z = static_cast<float>(mapZ);

	//座標の設定
	pos_ = VGet(
		(SIZE * x) + HALF_BLOCK_SIZE,
		-HALF_BLOCK_SIZE,
		(SIZE * z) + HALF_BLOCK_SIZE
	);
	MV1SetPosition(modelId_, pos_);
	//衝突判定
	MV1SetupCollInfo(modelId_, -1);
}



void Block::Uopdate(void)
{
}

void Block::Draw(void)
{
	//モデルの描画
	MV1DrawModel(modelId_);
}

void Block::Release(void)
{
	//モデルの解放
	MV1DeleteModel(modelId_);
}

int Block::GEtModelId(void)
{
	return modelId_;
}
