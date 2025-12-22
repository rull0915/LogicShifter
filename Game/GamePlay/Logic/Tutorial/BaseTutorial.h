#pragma once
#include <queue>

// 一つのチュートリアル
class OnceTutorial
{
private:
	// クリックを待つ位置
	Vector2D m_position;

	// クリックを待つ矩形のサイズ
	Vector2D m_size;

	// 説明文
	std::wstring m_explainStr;

	// 描画する矩形のサイズ
	Vector2D m_drawSize;

	// 押されたフラグ
	bool m_isEnd;

public:
	OnceTutorial(Vector2D pos, Vector2D size, const std::wstring& explainStr, Vector2D drawSize);

	void Update();

	void Render();

	bool GetIsEnd() const { return m_isEnd; };

private:
	bool OnMe();
};

enum class TutorialType
{
	None = 0,
	Start,
	Operation,
	Select,
	And,
	Or,
	Not,
};

// チュートリアル基底クラス
class Tutorial
{
protected:
	// チュートリアルのキュー
	std::queue<OnceTutorial> m_tutorials;

	// アクティブフラグ
	bool m_isActive;

	// クリックされたフラグ
	bool m_isClicked;

public:
	Tutorial()
		: m_tutorials{}
		, m_isActive{ false }
		, m_isClicked{ false }
	{
	};
	virtual ~Tutorial() = default;

	void Initialize(TutorialType type);

	void Update();

	void Render();

	void Finalize();

	bool GetIsActive() const { return m_isActive; }

	bool GetIsClicked() const { return m_isClicked; }
};
