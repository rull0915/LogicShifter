#include "CircuitEditer.h"
#include "../CellRenderer.h"

CircuitEditer::CircuitEditer(std::vector<PackedCell>& stage, Vector2D& cameraPos, float& cameraScale)
	: m_cells{ stage }
	, m_cameraPos{ cameraPos }
	, m_cameraScale{ cameraScale }
	, m_downMousePos{}
	, m_upMousePos{}
	, m_putCell{ 0b01010000 }
	, m_nowPutMode{ PutMode::Put }
	, m_stageReceiver{ stage }
	, m_isStart{ false }
	, m_commandManager{}
	, m_selectUI{ this }
{
}

void CircuitEditer::Initialize(PlayMode playMode)
{
	m_selectUI.Initialize(playMode);
	m_putCell = 0b01010000;

	m_nowPutMode = PutMode::Put;

	m_stageReceiver.Initialize();
	m_commandManager.Initialize();
}

void CircuitEditer::Update(float elapsedTime)
{
	if (MouseDown() & MOUSE_INPUT_LEFT) m_downMousePos	= GetCellIndex(m_mousePos, m_cameraPos, 1.0f / m_cameraScale);
	if (MouseUp() & MOUSE_INPUT_LEFT)	m_upMousePos	= GetCellIndex(m_mousePos, m_cameraPos, 1.0f / m_cameraScale);

	m_mouseIndex = GetCellIndex(m_mousePos, { static_cast<float>(m_cameraPos.x), static_cast<float>(m_cameraPos.y) }, 1.0f / m_cameraScale);

	m_selectUI.Update(elapsedTime);
}

void CircuitEditer::CellUpdate()
{
	if(MouseDown() & MOUSE_INPUT_LEFT || (!(MouseEnter() & MOUSE_INPUT_LEFT) && MouseDown() & MOUSE_INPUT_RIGHT))
	{
		m_commandManager.ToNextGroup();
	}

	switch (m_nowPutMode)
	{
	case CircuitEditer::PutMode::Put:
		PutUpdate();
		break;
	case CircuitEditer::PutMode::Copy:
		CopyUpdate();
		break;
	case CircuitEditer::PutMode::Paste:
		PasteUpdate();
		break;
	case CircuitEditer::PutMode::Range:
		RangeUpdate();
		break;
	default:
		break;
	}
}

void CircuitEditer::Render()
{
	switch (m_nowPutMode)
	{
	case CircuitEditer::PutMode::Put:
		RangeRender(m_mouseIndex - m_stageReceiver.GetCursorSize() + Vector2DInt{1, 1}, m_mouseIndex, m_cameraPos, 1.0f / m_cameraScale, 0xAAAAFF);
		break;
	case CircuitEditer::PutMode::Copy:
		if (m_isStart) RangeRender(m_downMousePos, m_mouseIndex, m_cameraPos, 1.0f / m_cameraScale, 0xFFAAAA);
		break;
	case CircuitEditer::PutMode::Paste:
		PasteRander();
		break;
	case CircuitEditer::PutMode::Range:
		if (m_isStart) RangeRender(m_downMousePos, m_mouseIndex, m_cameraPos, 1.0f / m_cameraScale, 0xFFAAAA);
		break;
	default:
		break;
	}

	// テスト用
	for (auto cell : Cell::GET_INFO_TYPES)
	{
		for (int i = 0; i < m_stageReceiver.GetCellInfo(cell).size(); i++)
		{
			auto info = m_stageReceiver.GetCellInfo(cell)[i];

			DrawStringOnGrid(info.x, info.y, m_cameraPos, 1.0f / m_cameraScale, 0xffffff, std::to_wstring(i + 1).c_str());
		}
	}

	m_selectUI.Render();
}

void CircuitEditer::Finalize()
{
	m_selectUI.Finalize();
}

void CircuitEditer::PutUpdate()
{
	// 設置
	if (MouseEnter() & MOUSE_INPUT_LEFT)
	{
		if (m_commandManager.GetUndoCommandNum() == 0) return;

		//　カーソルの範囲分ループ
		for (int i = 0; i < m_stageReceiver.GetCursorSize().y; i++)
		{
			for (int j = 0; j < m_stageReceiver.GetCursorSize().x; j++)
			{
				auto com = std::make_unique<SetCommand>(m_stageReceiver, m_mouseIndex - Vector2DInt{ j, i }, m_putCell);

				m_commandManager.AddUndoCommand(std::move(com));
			}
		}
	}
	// 削除
	else if (MouseEnter() & MOUSE_INPUT_RIGHT)
	{
		//　カーソルの範囲分ループ
		for (int i = 0; i < m_stageReceiver.GetCursorSize().y; i++)
		{
			for (int j = 0; j < m_stageReceiver.GetCursorSize().x; j++)
			{
				auto com = std::make_unique<SetCommand>(m_stageReceiver, m_mouseIndex - Vector2DInt{ j, i }, 0);

				m_commandManager.AddUndoCommand(std::move(com));
			}
		}

		m_mouseDrawMode = MouseMode::Erase;
	}
}

void CircuitEditer::CopyUpdate()
{
	if (MouseDown() & MOUSE_INPUT_LEFT) m_isStart = true;

	if (m_isStart && MouseUp() & MOUSE_INPUT_LEFT) 
	{
		auto com = std::make_unique<CopyCommand>(m_stageReceiver,std::make_pair(m_downMousePos, m_mouseIndex + Vector2DInt{1, 1}));

		m_commandManager.AddDoCommand(std::move(com));

		m_isStart = false;

		m_nowPutMode = PutMode::Paste;
	}
}

void CircuitEditer::PasteUpdate()
{
	if (MouseDown() & MOUSE_INPUT_LEFT) 
	{
		auto com = std::make_unique<PasteCommand>(m_stageReceiver, m_mouseIndex);

		m_commandManager.AddUndoCommand(std::move(com));
	}
}

void CircuitEditer::RangeUpdate()
{
	if (MouseDown() & MOUSE_INPUT_LEFT) m_isStart = true;

	if (m_isStart && MouseUp() & MOUSE_INPUT_LEFT)
	{
		auto com = std::make_unique<RangeCommand>(m_stageReceiver, std::make_pair(m_downMousePos, m_mouseIndex + Vector2DInt{1, 1}));

		m_commandManager.AddDoCommand(std::move(com));

		m_isStart = false;

		m_nowPutMode = PutMode::Put;
	}
}

void CircuitEditer::PasteRander()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

	float scale = (1.0f / m_cameraScale);

	// ズーム中心補正
	float offsetX = Screen::WIDTH / 2 + Screen::WIDTH / 2 * scale;
	float offsetY = Screen::HEIGHT / 2 + Screen::HEIGHT / 2 * scale;

	// セルの描画
	for(auto& cell : m_stageReceiver.GetCopyCells())
	{
		int color = Cell::COLORS[{GetType(cell.second), GetSubType(cell.second)}];
		// 描画
		DrawCell(m_mouseIndex.x + cell.first.x, m_mouseIndex.y + cell.first.y, m_cameraPos, 1.0f / m_cameraScale, cell.second);
		DrawStringOnGrid(m_mouseIndex.x + cell.first.x, m_mouseIndex.y + cell.first.y, m_cameraPos, 1.0f / m_cameraScale, color, L"A");
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void CircuitEditer::Reset()
{
	auto com = std::make_unique<ClearCommand>(m_stageReceiver);

	m_commandManager.AddUndoCommand(std::move(com));
}

void CircuitEditer::SaveCells(std::wstring fileName)
{
	auto com = std::make_unique<SaveCommand>(m_stageReceiver, fileName);

	m_commandManager.AddDoCommand(std::move(com));
}

void CircuitEditer::LoadCells(std::wstring fileName)
{
	m_commandManager.ToNextGroup();

	auto com = std::make_unique<LoadCommand>(m_stageReceiver, fileName);

	m_commandManager.AddUndoCommand(std::move(com));
}

void CircuitEditer::CopyInversion(bool horizontal)
{
	auto com = std::make_unique<InverseCommand>(m_stageReceiver, horizontal);

	m_commandManager.AddDoCommand(std::move(com));
}

void CircuitEditer::Undo()
{
	m_commandManager.UndoCommand();
}

void CircuitEditer::Redo()
{
	m_commandManager.RedoCommand();
}
