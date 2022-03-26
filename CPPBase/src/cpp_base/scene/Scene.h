/**
 * @file
 * @brief Sceneヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SCENE.h"
#include "../../lib/tml/scene/Scene.h"


namespace cpp_base {
namespace input {
class Manager;
}
namespace graphic {
class Manager;
}
namespace sound {
class Manager;
}
}


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

	virtual void OnSetManager(tml::Manager *);

public:
	SceneDesc();
	virtual ~SceneDesc();

	virtual void Init(void);

	cpp_base::scene::Manager *GetManager(void) const;
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
	const cpp_base::scene::SceneDesc *desc_;
	cpp_base::scene::Manager *mgr_;
	cpp_base::input::Manager *input_mgr_;
	cpp_base::graphic::Manager *graphic_mgr_;
	cpp_base::sound::Manager *sound_mgr_;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);
	virtual void OnSetManager(tml::Manager *);

public:
	Scene();
	virtual ~Scene();

	virtual void Init(void);

	const cpp_base::scene::SceneDesc *GetDesc(void) const;
	cpp_base::scene::Manager *GetManager(void);
	cpp_base::input::Manager *GetInputManager(void);
	cpp_base::graphic::Manager *GetGraphicManager(void);
	cpp_base::sound::Manager *GetSoundManager(void);
};
}
}


/**
 * @brief GetDesc関数
 * @return desc (desc)
 */
inline const cpp_base::scene::SceneDesc *cpp_base::scene::Scene::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline cpp_base::scene::Manager *cpp_base::scene::Scene::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetInputManager関数
 * @return input_mgr (input_manager)
 */
inline cpp_base::input::Manager *cpp_base::scene::Scene::GetInputManager(void)
{
	return (this->input_mgr_);
}


/**
 * @brief GetGraphicManager関数
 * @return graphic_mgr (graphic_manager)
 */
inline cpp_base::graphic::Manager *cpp_base::scene::Scene::GetGraphicManager(void)
{
	return (this->graphic_mgr_);
}


/**
 * @brief GetSoundManager関数
 * @return sound_mgr (sound_manager)
 */
inline cpp_base::sound::Manager *cpp_base::scene::Scene::GetSoundManager(void)
{
	return (this->sound_mgr_);
}
