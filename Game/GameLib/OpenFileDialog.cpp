#include "OpenFileDialog.h"

#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

std::wstring SaveFileDialog(bool stageMode)
{
	SetMouseDispFlag(true);

	wchar_t filename[MAX_PATH];
	filename[0] = L'\0'; // 最初にヌル文字入れておく

	OPENFILENAME ofn;
	// ofnから始まるsizeof(ofn)分のメモリを0で埋める
	ZeroMemory(&ofn, sizeof(ofn));

	// 構造体の長さを指定
	ofn.lStructSize = sizeof(ofn);

	ofn.hInstance;

	wchar_t iniFileFolderPath[_MAX_PATH];
	memset(iniFileFolderPath, NULL, _countof(iniFileFolderPath));
	GetModuleFileName(NULL, iniFileFolderPath, _countof(iniFileFolderPath));

	PathRemoveFileSpec(iniFileFolderPath);

	std::wstring path = iniFileFolderPath;
	if (stageMode) path += L"\\Resources\\Stages";
	else path += L"\\Resources\\FreeStages";

	// フィルター文字列のバッファー
	ofn.lpstrFilter = L"ステージ\0*.json\0";

	TCHAR szCustomFilter[256] = L"";

	ofn.lpstrCustomFilter = szCustomFilter;
	ofn.nMaxCustFilter = sizeof(szCustomFilter);

	ofn.hwndOwner = NULL;
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrInitialDir = path.c_str();
	ofn.lpstrDefExt = _T("json");
	ofn.nFilterIndex = 2; // 明示的に指定
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
	ofn.lpstrTitle = L"ステージを保存";

	if (GetOpenFileNameW(&ofn))
	{
		SetMouseDispFlag(false);

		return std::wstring(filename);
	}

	SetMouseDispFlag(false);

	return L"";
}

std::wstring LoadFileDialog(bool stageMode)
{
	SetMouseDispFlag(true);

	wchar_t filename[MAX_PATH];
	filename[0] = L'\0'; // 最初にヌル文字入れておく

	OPENFILENAME ofn;
	// ofnから始まるsizeof(ofn)分のメモリを0で埋める
	ZeroMemory(&ofn, sizeof(ofn));

	// 構造体の長さを指定
	ofn.lStructSize = sizeof(ofn);

	ofn.hInstance;


	wchar_t iniFileFolderPath[_MAX_PATH];
	memset(iniFileFolderPath, NULL, _countof(iniFileFolderPath));
	GetModuleFileName(NULL, iniFileFolderPath, _countof(iniFileFolderPath));

	PathRemoveFileSpec(iniFileFolderPath);

	std::wstring path = iniFileFolderPath;
	if (stageMode) path += L"\\Resources\\Stages";
	else path += L"\\Resources\\FreeStages";

	// フィルター文字列のバッファー
	ofn.lpstrFilter = L"ステージ\0*.json\0";

	TCHAR szCustomFilter[256] = L"";

	ofn.lpstrCustomFilter = szCustomFilter;
	ofn.nMaxCustFilter = sizeof(szCustomFilter);

	ofn.hwndOwner = NULL;
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;

	ofn.lpstrInitialDir = (path.c_str());

	ofn.lpstrDefExt = _T("json");
	ofn.nFilterIndex = 2; // 明示的に指定
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
	ofn.lpstrTitle = L"ステージをロード";

	if (GetOpenFileNameW(&ofn))
	{
		SetMouseDispFlag(false);

		return std::wstring(filename);
	}

	SetMouseDispFlag(false);

	return L"";
}
