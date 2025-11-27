#pragma once

#include "../StageReceiver.h"
#include "../../CellInfo.h"

// エディタ用コマンド基底クラス
class EditCommand
{
protected:
    // レシーバーの参照
    StageReceiver& m_receiver;

public:
    // コンストラクタ
    EditCommand(StageReceiver& receiver)
        : m_receiver{ receiver }
    {
    };

    // デストラクタ
    virtual ~EditCommand() = default;

    // 実行
    virtual bool Execute() = 0;
};

