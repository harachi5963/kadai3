#pragma once
#include<DxLib.h>

class Block
{
public:
	//ブロックの種類
	enum class TYPE
	{
		NONE = -1,	//何もなし
		GRASS,		//草
		METAL,		//金属
		ICE,		//氷

		MAX			//全種別数
	};

	//定数
	//自己発光色
	static constexpr COLOR_F EMI_COLOR = { 0.5f,0.5f,0.5f,1.0f };

	//モデルの大きさ
	static constexpr VECTOR SCALE = { 0.5f,0.5f,0.5f };

	//1ブロックあたりのサイズ
	static constexpr float SIZE = 100.0f;
public:
	Block();
	~Block();

	//ブロックを生成する
	void Create(TYPE type, int modelId, int mapX, int mapZ);
	void Uopdate(void);	//更新
	void Draw(void);	//描画
	void Release(void);	//解放

	//モデルハンドルIDを取得する
	int GEtModelId(void);

private:
	TYPE type_;		//ブロックの種類
	int modelId_;	//モデルのID
	VECTOR pos_;	//座標
	VECTOR scale_;	//大きさ

};

