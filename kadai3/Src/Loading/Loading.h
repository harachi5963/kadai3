#pragma once

class Loading
{
public:
	//シングルトン（生成・取得・削除）
	static void CreateInstance(void) { if (instance_ == nullptr) { instance_ = new Loading(); } }
	static Loading* GetInstance(void) { return instance_; }
	static void DeleteInstance(void) { if (instance_ != nullptr) { delete instance_;instance_ = nullptr; } }

private:
	//コンストラクタ
	Loading(void);
	//デスクトラクタ
	~Loading(void);

	//静的インスタンス
	static Loading* instance_;

public:

	void Init(void);
	void Load(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void StartAsyncLoad(void);	//非同期ロードの開始
	void EndAsyncLoad(void);	//非同期ロードの終了

	//ロード中なのか返す
	bool IsLoading(void);

private:
	//画像ハンドル
	int handle_;

	//座標
	int posX_;
	int posY_;

	//ロード中のフラグ
	bool isLoading_;

	//最低でもロード画面を表示する時間
	int loadTimer_;
};
