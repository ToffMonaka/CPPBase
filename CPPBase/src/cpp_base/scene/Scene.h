/**
 * @file
 * @brief Sceneヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SCENE.h"
#include "../../lib/tml/scene/Scene.h"


namespace cpp_base {
namespace scene {
/**
 * @brief SceneDescクラス
 */
class SceneDesc : public tml::scene::SceneDesc
{
public:
	cpp_base::scene::Manager *manager2;

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	SceneDesc();
	virtual ~SceneDesc();

	virtual void Init(void);

	void SetManager(cpp_base::scene::Manager *);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::SceneDesc::Release(void)
{
	tml::scene::SceneDesc::Release();

	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief Sceneクラス
 *
 * インターフェースパターン
 */
class Scene : public tml::scene::Scene
{
public: Scene(const cpp_base::scene::Scene &) = delete;
public: cpp_base::scene::Scene &operator =(const cpp_base::scene::Scene &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	cpp_base::scene::Manager *mgr2_;

protected:
	void Release(void);
	INT Create(const cpp_base::scene::SceneDesc &, const cpp_base::ConstantUtil::SCENE::SCENE_TYPE);

public:
	Scene();
	virtual ~Scene();

	virtual void Init(void);

	cpp_base::scene::Manager *GetManager(void);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::Scene::Release(void)
{
	tml::scene::Scene::Release();

	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline cpp_base::scene::Manager *cpp_base::scene::Scene::GetManager(void)
{
	return (this->mgr2_);
}
