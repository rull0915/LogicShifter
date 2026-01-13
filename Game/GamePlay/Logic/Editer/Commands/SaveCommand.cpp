#include "SaveCommand.h"

SaveCommand::SaveCommand(StageReceiver& reciever, std::wstring fileName)
	: EditCommand(reciever)
	, m_fileName{ fileName }
{
}

bool SaveCommand::Execute()
{
	json stage;
	stage["Stage"];

	// ƒtƒ@ƒCƒ‹‚Ö‘‚«‚İ
	std::ofstream file(m_fileName);

	if (file.is_open())
	{
		for (int i = -OFFSET_Y; i < OFFSET_Y; i++)
		{
			for (int j = -OFFSET_X; j < OFFSET_X; j++)
			{
				if (m_receiver.GetCell({ j, i }) == 0) continue;

				json cell =
				{
					{"PosX", j},
					{"PosY", i},
					{"Type", GetType(m_receiver.GetCell({j, i}))},
					{"SubType", GetSubType(m_receiver.GetCell({j, i}))},
				};

				stage["Stage"].push_back(cell);
			}
		}
	}

	file << stage.dump();

	file.close();

	return true;
}
