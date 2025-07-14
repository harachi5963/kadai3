#pragma once
#include <DxLib.h>
#include "../Scene/SceneBase.h"

//ベースを継承
class TitleScene : public SceneBase
{
public:
    TitleScene(void);                //コンストラクタ
    ~TitleScene(void) override;        //デストラクタ

    // 初期化
    void Init(void) override;

    //読み込み
    void Load(void) override;

    //読み込み後
    void LoadEnd(void) override;

    //更新
    void Update(void) override;

    // 描画
    void Draw(void) override;

    // 削除
    void Release(void) override;

    //次のシーンへ
    void toNextScene(void);

private:
    int handle_;
};