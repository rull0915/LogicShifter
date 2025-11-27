//--------------------------------------------------------------------------------------
// File: SceneManager.cpp
//
//--------------------------------------------------------------------------------------
#include "SceneManager.h"
#include "Scene.h"

// コンストラクタ
SceneManager::SceneManager()
	: m_scenes{}
	, m_pCurrentScene{ nullptr }
	, m_pRequestedScene{ nullptr }
{
}

// デストラクタ
SceneManager::~SceneManager()
{
	// 実行中のシーンの終了処理
	if (m_pCurrentScene) m_pCurrentScene->Finalize();
}

// シーンの登録
void SceneManager::RegisterScene(const std::string& sceneName, std::unique_ptr<Scene> scene)
{
	// シーンの名前でシーンを登録
	m_scenes.emplace(sceneName, std::move(scene));
}

// 更新処理
void SceneManager::Update(float elapsedTime)
{
	// シーンの変更
	if (m_pRequestedScene) ChangeScene();

	// シーンの更新
	if (m_pCurrentScene) m_pCurrentScene->Update(elapsedTime);
}

// 描画処理
void SceneManager::Render()
{
	// シーンの描画処理
	if (m_pCurrentScene) m_pCurrentScene->Render();
}

// 開始シーンの設定
void SceneManager::SetStartScene(const std::string& startSceneName)
{
	RequestSceneChange(startSceneName);
}

// シーンの変更
void SceneManager::RequestSceneChange(const std::string& requestSceneName)
{
	// シーンが未登録？
	if (m_scenes.count(requestSceneName) == 0)
	{
		OutputDebugString(L"%sは登録されていません。");
		return;
	}

	// 登録されたリクエストシーンを取得
	m_pRequestedScene = m_scenes[requestSceneName].get();
}

// シーンの変更
void SceneManager::ChangeScene()
{
	// シーンのリクエスト要求がない？
	if (!m_pRequestedScene) return;

	// 実行中のシーンの終了処理
	if (m_pCurrentScene) m_pCurrentScene->Finalize();

	// リクエスト要求のシーンへ移行
	m_pCurrentScene = m_pRequestedScene;
	// シーンの初期化処理
	m_pCurrentScene->Initialize();

	// リクエスト要求をクリア
	m_pRequestedScene = nullptr;
}

