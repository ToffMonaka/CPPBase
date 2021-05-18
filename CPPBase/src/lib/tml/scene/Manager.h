/**
 * @file
 * @brief Managerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../time/FrameRate.h"
#include "../manager/Manager.h"
#include "ManagerCommon.h"


namespace tml {
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


namespace tml {
namespace scene {
/**
 * @brief ManagerDescクラス
 */
class ManagerDesc : public tml::ManagerDesc
{
private:
	tml::input::Manager *input_mgr_;
	tml::graphic::Manager *graphic_mgr_;
	tml::sound::Manager *sound_mgr_;

public:

protected:
	void Release(void);

	void InitResourceCount(void);
	void InitEventCount(void);

public:
	ManagerDesc();
	virtual ~ManagerDesc();

	virtual void Init(void);

	tml::input::Manager *GetInputManager(void) const;
	void SetInputManager(tml::input::Manager *);
	tml::graphic::Manager *GetGraphicManager(void) const;
	void SetGraphicManager(tml::graphic::Manager *);
	tml::sound::Manager *GetSoundManager(void) const;
	void SetSoundManager(tml::sound::Manager *);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::scene::ManagerDesc::Release(void)
{
	tml::ManagerDesc::Release();

	return;
}


/**
 * @brief GetInputManager関数
 * @return input_mgr (input_manager)
 */
inline tml::input::Manager *tml::scene::ManagerDesc::GetInputManager(void) const
{
	return (this->input_mgr_);
}


/**
 * @brief GetGraphicManager関数
 * @return graphic_mgr (graphic_manager)
 */
inline tml::graphic::Manager *tml::scene::ManagerDesc::GetGraphicManager(void) const
{
	return (this->graphic_mgr_);
}


/**
 * @brief GetSoundManager関数
 * @return sound_mgr (sound_manager)
 */
inline tml::sound::Manager *tml::scene::ManagerDesc::GetSoundManager(void) const
{
	return (this->sound_mgr_);
}


namespace tml {
namespace scene {
/**
 * @brief Managerクラス
 */
class Manager : public tml::Manager
{
public: Manager(const tml::scene::Manager &) = delete;
public: tml::scene::Manager &operator =(const tml::scene::Manager &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	tml::input::Manager *input_mgr_;
	tml::graphic::Manager *graphic_mgr_;
	tml::sound::Manager *sound_mgr_;
	tml::FrameRate frame_rate_;
	tml::shared_ptr<tml::scene::Scene> scene_;
	bool scene_end_flg_;
	tml::shared_ptr<tml::scene::Scene> next_scene_;

public:
	tml::scene::ManagerCommon common;

protected:
	void Release(void);

	INT CreateCommon(void);
	void DeleteCommon(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(const tml::scene::ManagerDesc &);

	void Update(void);

	tml::input::Manager *GetInputManager(void);
	tml::graphic::Manager *GetGraphicManager(void);
	tml::sound::Manager *GetSoundManager(void);
	const tml::FrameRate &GetFrameRate(void) const;

	tml::scene::Scene *Get(void);
	INT Start(tml::shared_ptr<tml::scene::Scene> &);
	void End(void);

	template <typename T>
	tml::shared_ptr<T> &GetScene(tml::shared_ptr<T> &, const WCHAR *);
	template <typename T>
	tml::shared_ptr<T> &GetNode(tml::shared_ptr<T> &, const WCHAR *);
};
}
}


/**
 * @brief GetInputManager関数
 * @return input_mgr (input_manager)
 */
inline tml::input::Manager *tml::scene::Manager::GetInputManager(void)
{
	return (this->input_mgr_);
}


/**
 * @brief GetGraphicManager関数
 * @return graphic_mgr (graphic_manager)
 */
inline tml::graphic::Manager *tml::scene::Manager::GetGraphicManager(void)
{
	return (this->graphic_mgr_);
}


/**
 * @brief GetSoundManager関数
 * @return sound_mgr (sound_manager)
 */
inline tml::sound::Manager *tml::scene::Manager::GetSoundManager(void)
{
	return (this->sound_mgr_);
}


/**
 * @brief GetFrameRate関数
 * @return frame_rate (frame_rate)
 */
inline const tml::FrameRate &tml::scene::Manager::GetFrameRate(void) const
{
	return (this->frame_rate_);
}


/**
 * @brief Get関数
 * @return scene (scene)
 */
inline tml::scene::Scene *tml::scene::Manager::Get(void)
{
	return (this->scene_.get());
}


/**
 * @brief GetScene関数
 * @param dst_scene (dst_scene)
 * @param class_name (class_name)
 * @return dst_scene (dst_scene)
 */
template <typename T>
inline tml::shared_ptr<T> &tml::scene::Manager::GetScene(tml::shared_ptr<T> &dst_scene, const WCHAR *class_name)
{
	dst_scene.reset();

	if (class_name == nullptr) {
		return (dst_scene);
	}

	return (dst_scene);
}


/**
 * @brief GetNode関数
 * @param dst_node (dst_node)
 * @param class_name (class_name)
 * @return dst_node (dst_node)
 */
template <typename T>
inline tml::shared_ptr<T> &tml::scene::Manager::GetNode(tml::shared_ptr<T> &dst_node, const WCHAR *class_name)
{
	dst_node.reset();

	if (class_name == nullptr) {
		return (dst_node);
	}

	return (dst_node);
}
