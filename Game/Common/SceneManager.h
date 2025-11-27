//--------------------------------------------------------------------------------------
// File: SceneManager.h
//
//--------------------------------------------------------------------------------------
#pragma once

#include <memory>
#include <string>
#include <unordered_map>

// 前方参照
class Scene;

// シーンマネージャークラス
class SceneManager
{

private:

	// エイリアス宣言
	using SceneCollection = std::unordered_map<std::string, std::unique_ptr<Scene>>;

	// シーン群
	SceneCollection m_scenes;

	// 実行中のシーン
	Scene* m_pCurrentScene;

	// 要求されたシーン
	Scene* m_pRequestedScene;

public:

	// コンストラクタ
	SceneManager();

	// デストラクタ
	~SceneManager();

	// シーンの登録
	void RegisterScene(const std::string& sceneName, std::unique_ptr<Scene> scene);

	// 更新処理
	void Update(float elapsedTime);

	// 描画処理
	void Render();

	// 開始シーンの設定
	void SetStartScene(const std::string& startSceneName);

	// シーンの変更
	void RequestSceneChange(const std::string& requestSceneName);

private:

	// シーンの変更
	void ChangeScene();

};
