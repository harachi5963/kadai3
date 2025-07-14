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
	//�e��Ԃ�����̃I���W�i�������[�h
	blockOriginModeleId_[static_cast<int>(Block::TYPE::GRASS)]
		= MV1LoadModel("Data/Model/Blocks/Block_Grass.mv1");
	blockOriginModeleId_[static_cast<int>(Block::TYPE::METAL)]
		= MV1LoadModel("Data/Model/Blocks/Block_Metal.mv1");
	blockOriginModeleId_[static_cast<int>(Block::TYPE::ICE)]
		= MV1LoadModel("Data/Model/Blocks/Block_Ice.mv1");

	//�}�b�v�ǂݍ���
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
	//�u���b�N�̕`��
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
	//�u���b�N�̍폜
	for (int z = 0;z < BLOCK_NUM_Z;z++)
	{
		for (int x = 0;x < BLOCK_NUM_X;x++)

		{
			blocks_[z][x]->Release();
			delete blocks_[z][x];
		}
	}

	//�I���W�i�����f���̍폜
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
			//�z�񂩂�Block��������o��
			Block* block = blocks_[z][x];

			//�����ƃ��f���̓����蔻��
			MV1_COLL_RESULT_POLY coll =
				MV1CollCheck_Line(block->GEtModelId(), -1, topPos, downPos);

			//��������
			if (coll.HitFlag)
			{
				//���ʂ��J��Ԃ�
				*result = coll;
				return true;
			}
		}
	}
	return false;
}

void Stage::LoadMapCsvData(void)
{
	//�t�@�C���̓ǂݍ���
	std::ifstream ifs = std::ifstream("Data/MapData/MapData.csv");

	//�t�@�C���̓ǂݍ��݂��������Ă��邩
	if (!ifs)
	{
		//�G���[������
		return;
	}

	//�t�@�C�����P�s���ǂݍ���
	std::string line;					//�P�s�̕������
	std::vector<std::string> strSplit;	//�P�s���P�����̓��I�z��ɕ��z

	int mapNo = 0;		//�}�b�v�̎��
	int z = 0;

	//�t�@�C�������ׂēǂݍ��ނ܂�
	while (getline(ifs, line))
	{
		//�P�s���J���}��؂�ŕ���
		strSplit = AsoUtility::Split(line, ',');

		for (int x = 0; x < strSplit.size();x++)
		{
			//�����񂩂琮���ɕϊ�
			//string����int�ɕϊ�
			mapNo = stoi(strSplit[x]);

			Block::TYPE type = static_cast<Block::TYPE>(mapNo);

			//�I���W�i���̃��f�������
			int baseModel = blockOriginModeleId_[mapNo];

			//�u���b�N�𐶐�
			Block* block = new Block();
			block->Create(type, baseModel, x, z);

			//�Q�����z��Ƀu���b�N���i�[
			blocks_[z][x] = block;
		}

		z++;
	}
}
