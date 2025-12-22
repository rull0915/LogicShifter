#include "ClearChecker.h"

ClearChecker::ClearChecker(std::vector<PackedCell>& stage, std::vector<PackedCell>& nextStage, Conditions& con)
	:m_stage{ stage }
	, m_nextStage{ nextStage }
	, m_circuitSimulator{ stage, nextStage }
	, m_conditions{ con }
	, m_nowPlaySpeed{ 1.0f / 10 }
	, m_nowElapsedTime{ -1 }
	, m_isActive{ false }
	, m_gauge{ {200, Screen::HEIGHT * (7.f / 8)}, {300, 40}, GaugeMode::Right, 0x666666, 0x22FF22}
{
	m_gauge.Initialize();
}

void ClearChecker::Initialize(std::vector<PackedCell>& stage)
{
	m_nowCheckingNum = -1;

	m_beforeStage = stage;

	m_isActive = true;

	ToNextCondition();

	m_circuitSimulator.Initialize();
	m_circuitSimulator.ResetGenerationNum();

	m_gauge.Initialize();
}

bool ClearChecker::Update(float elapsedTime) 
{
	m_gauge.Update(elapsedTime);

	// 非アクティブなら実行しない
	if (!m_isActive) return false;

	// 時間の加算
	m_nowElapsedTime += elapsedTime;

	if(m_nowElapsedTime >= m_nowPlaySpeed)
	{
		// 経過時間の初期化
		m_nowElapsedTime = 0;

		// 次の世代へ
		if(m_circuitSimulator.ToNextCells())
		{
			// 変化がなくなったら

			// クリアチェック
			if (CheckCondition())
			{
				// クリアだったら
				m_gauge.SetRatio(static_cast<float>(m_nowCheckingNum + 1) / m_conditions.conditions.size());

				// 最後の条件だったら
				if (m_nowCheckingNum == m_conditions.conditions.size() - 1)
				{
					// チェックを終了しtrueを返す
					m_isActive = false;

					m_stage = m_beforeStage;
					
					return true;
				}
				// 違ったら
				else
					// 次の条件へ
					ToNextCondition();
			}
			// クリアでなかったら
			else
			{
				// チェックを終了しfalseを返す
				m_isActive = false;

				m_stage = m_beforeStage;

				return false;
			}
		}
		else
		{
			// 実行回数が一定以上になったら
			if(m_circuitSimulator.GetGenerationNum() > MAX_GENERATION)
			{
				// チェックを終了しfalseを返す
				m_isActive = false;

				m_stage = m_beforeStage;

				return false;
			}
		}
	}

	return false;
}

void ClearChecker::Render()
{		
//	m_gauge.Render();
}

void ClearChecker::ToNextCondition()
{
	// 初期状態へ戻す
	m_stage = m_beforeStage;

	m_circuitSimulator.ResetGenerationNum();

	// 次の条件へ
	m_nowCheckingNum++;

	// 入力条件をセット
	for(int i = 0; i < m_conditions.inputPoses.size(); i++)
	{
		// 条件がtrueなら
		if(m_conditions.conditions[m_nowCheckingNum].inputs[i])
		{
			// 信号を全てONに
			m_stage[GetIndex(m_conditions.inputPoses[i].x, m_conditions.inputPoses[i].y)] =
				m_stage[GetIndex(m_conditions.inputPoses[i].x, m_conditions.inputPoses[i].y)] | 0b00001111;
		}
		// falseなら
		else
		{
			// 信号を全てOFFに
			m_stage[GetIndex(m_conditions.inputPoses[i].x, m_conditions.inputPoses[i].y)] =
				m_stage[GetIndex(m_conditions.inputPoses[i].x, m_conditions.inputPoses[i].y)] & 0b11110000;
		}
	}
}

bool ClearChecker::CheckCondition()
{
	// 出力セル全てをチェック
	for(int i = 0; i < m_conditions.outputPoses.size(); i++)
	{
		// セルを取得
		PackedCell cell = m_stage[GetIndex(m_conditions.outputPoses[i].x, m_conditions.outputPoses[i].y)];

		// 信号があるかないか
		bool signal = cell & 0b00001111;

		// 条件と違っていたらfalseを返す
		if (m_conditions.conditions[m_nowCheckingNum].outputs[i] != signal) return false;
	}

	// すべて通過すればtrue
	return true;
}
