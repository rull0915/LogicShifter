#include "Scene.h"
#include "SceneManager.h"

// コンストラクタ
Scene::Scene(SceneManager* pSceneManager)
	: m_pSceneManager(pSceneManager)
{

}

// デストラクタ
Scene::~Scene()
{

}

// シーンの変更
void Scene::ChangeScene(const std::string& nextSceneName)
{
	m_pSceneManager->RequestSceneChange(nextSceneName);
}
