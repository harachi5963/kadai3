#include "Stage.h"
#include "../../Utility/AsoUtility.h"
#include <fstream>

Stage::Stage(void)
{
}

Stage::~Stage(void)
{
}

void Stage::Init(void)
{
}

void Stage::Load(void)
{
	//各種ぶろっくのオリジナルをロード
	blockOriginModeleId_[static_cast<int>(Block::TYPE::GRASS)]
		= MV1LoadModel("Data/Model/Blocks/Block_Grass.mv1");
	blockOriginModeleId_[static_cast<int>(Block::TYPE::METAL)]
		= MV1LoadModel("Data/Model/Blocks/Block_Metal.mv1");
	blockOriginModeleId_[static_cast<int>(Block::TYPE::ICE)]
		= MV1LoadModel("Data/Model/Blocks/Block_Ice.mv1");

	//マップ読み込み
	LoadMapCsvData();
}

void Stage::LOadEnd(void)
{
}


void Stage::Update(void)
{
}

void Stage::Draw(void)
{
	//ブロックの描画
	for (int z = 0;z < BLOCK_NUM_Z;z++)
	{
		for (int x = 0;x < BLOCK_NUM_X;x++)

		{
			blocks_[z][x]->Draw();
		}
	}
}

void Stage::Release(void)
{
	//ブロックの削除
	for (int z = 0;z < BLOCK_NUM_Z;z++)
	{
		for (int x = 0;x < BLOCK_NUM_X;x++)

		{
			blocks_[z][x]->Release();
			delete blocks_[z][x];
		}
	}

	//オリジナルモデルの削除
	for (int i = 0;i < BLOCK_MODEL_NUM;i++)
	{
		MV1DeleteModel(blockOriginModeleId_[i]);
	}
}

bool Stage::IsCollLine(VECTOR topPos, VECTOR downPos, MV1_COLL_RESULT_POLY* result)
{
	for (int z = 0;z < BLOCK_NUM_Z;z++)
	{
		for (int x = 0;x < BLOCK_NUM_X;x++)
		{
			//配列からBlockを一つずつ取り出す
			Block* block = blocks_[z][x];

			//線分とモデルの当たり判定
			MV1_COLL_RESULT_POLY coll =
				MV1CollCheck_Line(block->GEtModelId(), -1, topPos, downPos);

			//当たった
			if (coll.HitFlag)
			{
				//結果を繰り返す
				*result = coll;
				return true;
			}
		}
	}
	return false;
}

void Stage::LoadMapCsvData(void)
{
	//ファイルの読み込み
	std::ifstream ifs = std::ifstream("Data/MapData/MapData.csv");

	//ファイルの読み込みが成功しているか
	if (!ifs)
	{
		//エラーが発生
		return;
	}

	//ファイルを１行ずつ読み込む
	std::string line;					//１行の文字情報
	std::vector<std::string> strSplit;	//１行を１文字の動的配列に分配

	int mapNo = 0;		//マップの種類
	int z = 0;

	//ファイルをすべて読み込むまで
	while (getline(ifs, line))
	{
		//１行をカンマ区切りで分割
		strSplit = AsoUtility::Split(line, ',');

		for (int x = 0; x < strSplit.size();x++)
		{
			//文字列から整数に変換
			//stringからintに変換
			mapNo = stoi(strSplit[x]);

			Block::TYPE type = static_cast<Block::TYPE>(mapNo);

			//オリジナルのモデルを取る
			int baseModel = blockOriginModeleId_[mapNo];

			//ブロックを生成
			Block* block = new Block();
			block->Create(type, baseModel, x, z);

			//２次元配列にブロックを格納
			blocks_[z][x] = block;
		}

		z++;
	}
}
