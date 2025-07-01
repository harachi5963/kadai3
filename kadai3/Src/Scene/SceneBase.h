#pragma once
#include <DxLib.h>

class SceneBase
{
public:
    SceneBase();                        //コンストラクタ
    virtual ~SceneBase() = 0;            //デストラクタ

    // 初期化
    virtual void Init(void) = 0;

    //読み込み
    virtual void Load(void) = 0;

    //読み込み後
    virtual void LoadEnd(void) = 0;

    // 更新
    virtual void Update(void) = 0;

    // 描画
    virtual void Draw(void) = 0;

    // 削除
    virtual void Release(void) = 0;


};
