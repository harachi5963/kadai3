#pragma once
#include <DxLib.h>
#include"Block.h"

class Stage
{
public:
	//ブロックのモデル種類
	static constexpr int BLOCK_MODEL_NUM = static_cast<int>(Block::TYPE::MAX);

	//ブロックの工数（マップサイズ）
	static constexpr int BLOCK_NUM_X = 20;
	static constexpr int BLOCK_NUM_Z = 20;

public:
	Stage(void);
	~Stage(void);

	void Init(void);	//初期化
	void Load(void);	//読みこみ
	void LOadEnd(void);	//読みこみ後
	void Update(void);	//更新
	void Draw(void);	//描画
	void Release(void);	//解放

	//線分とブロックの衝突判定
	bool IsCollLine(
		VECTOR topPos, VECTOR downPos, MV1_COLL_RESULT_POLY* result
	);

private:
	//マップデータ読み込み
	void LoadMapCsvData(void);

private:
	//ブロックのオリジナルハンドル
	int blockOriginModeleId_[BLOCK_MODEL_NUM];

	//ブロッククラス
	Block* blocks_[BLOCK_NUM_Z][BLOCK_NUM_X];
};