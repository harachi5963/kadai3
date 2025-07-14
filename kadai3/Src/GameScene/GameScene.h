#pragma once
#include"../TitleScene/TitleScene.h"
#include<DxLib.h>

//クラスの前方宣言
class Grid;
class Stage;
class Player;

//ベースを継承
class GameScene :public SceneBase
{
public:
	GameScene();                        //コンストラクタ
	~GameScene()			override;   //デストラクト

    // 初期化
    void Init(void)         override;

    //読み込み
    void Load(void)         override;

    //読み込み後
    void LoadEnd(void)      override;

    //更新
    void Update(void)       override;

    // 描画
    void Draw(void)         override;

    // 削除
    void Release(void)       override;

private:
    //デバック描画
    void DebugDraw(void);
    
    //線のデバック表示
    VECTOR lineTopPos_;
    VECTOR lineDownPos_;

    //衝突判定
    void Collision(void);

    //ステージとプレイヤーの衝突判定
    void CollisionStage(void);

private:
    Grid* grid_;    //グリッドクラス

    Stage* stage_;
    Player* player_;
};