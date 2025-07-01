#pragma once

//クラスの宣言
class SceneBase;

class ScenManager
{
public:
	//シーン管理
	enum class SCENE_ID
	{
		NOME,
		TITLE,
		GAME,
	};

public:
	//シングルトン（生成・取得・削除）
	static void CreateInstance(void) {if (instance_ == nullptr){instance_ = new ScenManager();}}
	static ScenManager* GetInstance(void){return instance_;}
	static void DeleteInstance(void){if (instance_ != nullptr){delete instance_;instance_ = nullptr;}}

private:
	//コンストラクタ
	ScenManager(void);
	//デスクトラクタ
	~ScenManager(void);

	//静的インスタンス
	static ScenManager* instance_;

public:
	void Init(void);	//初期化
	void Init3D(void);	//３Dの初期化
	void Update(void);	//更新
	void Draw(void);	//描画
	void Release(void);	//解放

	//状態遷移
	void ChangeScene(SCENE_ID nextld);

	//シーンIDの取得
	SCENE_ID GetSceneID(void) { return scendId_; }

	//ゲーム終了
	void GameEnd(void) { isGameEnd_ - true; }

	//ゲーム終了フラグの取得
	bool GetGameEnd(void) { return isGameEnd_; }

private:
	//各種シーン
	SceneBase* scene_;


	//シーンID
	SCENE_ID scendId_;

	//ゲーム終了
	bool isGameEnd_;
};
