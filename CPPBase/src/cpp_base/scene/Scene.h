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
private:
	cpp_base::scene::Manager *mgr_;

public:

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	SceneDesc();
	virtual ~SceneDesc();

	virtual void Init(void);

	cpp_base::scene::Manager *GetManager(void) const;
	void SetManager(cpp_base::scene::Manager *);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::SceneDesc::Release(void)
{
	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline cpp_base::scene::Manager *cpp_base::scene::SceneDesc::GetManager(void) const
{
	return (this->mgr_);
}


namespace cpp_base {
namespace scene {
/**
 * @brief Sceneクラス
 */
class Scene : public tml::scene::Scene
{
public: Scene(const cpp_base::scene::Scene &) = delete;
public: cpp_base::scene::Scene &operator =(const cpp_base::scene::Scene &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	cpp_base::scene::Manager *mgr_;

private:
	void Release(void);

protected:
	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);

public:
	Scene();
	virtual ~Scene();

	virtual void Init(void);
	INT Create(const cpp_base::scene::SceneDesc &);

	cpp_base::scene::Manager *GetManager(void);
};
}
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline cpp_base::scene::Manager *cpp_base::scene::Scene::GetManager(void)
{
	return (this->mgr_);
}
