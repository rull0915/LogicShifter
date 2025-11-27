#pragma once

// テキスト入力クラス
class TextInputManager
{
private:
	// 位置
	Vector2D m_position;

	// サイズ
	Vector2D m_size;

	// 変更する文字列変数
	std::wstring* m_changeString;

	// キー入力ハンドル
	int m_keyInputHandle;

	// 文字列格納用
	TCHAR result[255];

	// 入力が開始されたか
	bool m_isStart;

public:
	TextInputManager(std::wstring* change, Vector2D pos, Vector2D size);

	// 初期化関数
	void Initialize(bool numOnly = false);

	// 更新関数
	void Update();

	// 描画関数
	void Render();

	void SetPos(Vector2D pos) { m_position = pos; }

	// 入力中かどうかを返す関数
	bool IsInputting() const { return (m_isStart && CheckKeyInput(m_keyInputHandle) == 0); }

	// 入力中の文字列をセットする関数
	void SetInputString(TCHAR* str) { SetKeyInputString(str, m_keyInputHandle); }

private:
	bool OnMe(Vector2D pos);

};

