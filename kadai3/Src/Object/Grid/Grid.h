#pragma once

//グリッドクラス
class Grid
{
public:
	//定数定義

	//線の長さ
	static constexpr float LEN = 3000.0f;

	//線の長さの半分	
	static constexpr float HLEN = LEN / 2.0f;

	//線の間隔
	static constexpr float DISTANCE = 100.0f;

	//線の数
	static constexpr int NUM = static_cast<int>(LEN / DISTANCE);

	//線の数の半分
	static constexpr int HNUM = NUM / 2;

	//コンストラクタ
	Grid(void);

	//デスクトラクタ
	~Grid(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);
};
