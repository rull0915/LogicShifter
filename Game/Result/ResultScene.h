#pragma once
#include "../Game/Common/Scene.h"

class Game;

class ResultScene : public Scene
{
	// 変数宣言
private:
	// このシーンを含むゲームオブジェクトへのポインタ
	Game* m_pGame;

	// クリアしたステージ名
	std::wstring m_stageName;

	// 第二条件の値
	int m_secondConditionValue;

	// 第三条件の値
	int m_thirdConditionValue;

	// 第三条件の条件文
	std::wstring m_thirdConditionStr;

	// 第三条件のid
	int m_thirdConditionID;

	// 満たしていたかどうか
	bool m_isSatisfied[3];

	// 関数宣言 -------------------------------
public:

	// コンストラクタ
	ResultScene(Game* pGame);

	// デストラクタ
	~ResultScene();

	// 初期化関数
	void Initialize() override;

	// 更新関数
	void Update(float elapsedTime) override;

	// 描画関数
	void Render() override;

	// 終了関数
	void Finalize()override;

private:
	// 3つ目の条件をまとめた文字列を返す関数
	std::wstring GetThirdCondition();
};

