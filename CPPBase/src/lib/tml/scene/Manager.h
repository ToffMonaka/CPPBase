/**
 * @file
 * @brief Managerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <functional>
#include "../time/FrameRate.h"
#include "../manager/Manager.h"
#include "ManagerCommon.h"
#include "Scene.h"
#include "Node.h"


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
	std::unordered_map<std::wstring, std::function<tml::shared_ptr<tml::scene::Scene>(const tml::INIFileReadDesc &)>> scene_factory_cont_;
	std::unordered_map<std::wstring, std::function<tml::shared_ptr<tml::scene::Node>(const tml::INIFileReadDesc &)>> node_factory_cont_;
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
	void SetSceneFactory(const WCHAR *, std::function<tml::shared_ptr<tml::scene::Scene>(const tml::INIFileReadDesc &)>);
	template <typename T>
	tml::shared_ptr<T> &GetScene(tml::shared_ptr<T> &, const WCHAR *, const tml::INIFileReadDesc &);
	void SetNodeFactory(const WCHAR *, std::function<tml::shared_ptr<tml::scene::Node>(const tml::INIFileReadDesc &)>);
	template <typename T>
	tml::shared_ptr<T> &GetNode(tml::shared_ptr<T> &, const WCHAR *, const tml::INIFileReadDesc &);

	tml::scene::Scene *Get(void);
	INT Start(tml::shared_ptr<tml::scene::Scene> &);
	void End(void);
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
 * @brief GetScene関数
 * @param dst_scene (dst_scene)
 * @param class_name (class_name)
 * @param read_desc (read_desc)
 * @return dst_scene (dst_scene)
 */
template <typename T>
inline tml::shared_ptr<T> &tml::scene::Manager::GetScene(tml::shared_ptr<T> &dst_scene, const WCHAR *class_name, const tml::INIFileReadDesc &read_desc)
{
	dst_scene.reset();

	if ((class_name == nullptr)
	|| (class_name[0] == 0)) {
		return (dst_scene);
	}

	tml::shared_ptr<tml::scene::Scene> scene;

	auto scene_factory_itr = this->scene_factory_cont_.find(class_name);

	if (scene_factory_itr == this->scene_factory_cont_.end()) {
		return (dst_scene);
	}

	scene = scene_factory_itr->second(read_desc);

	dst_scene = std::dynamic_pointer_cast<T>(scene);

	return (dst_scene);
}


/**
 * @brief GetNode関数
 * @param dst_node (dst_node)
 * @param class_name (class_name)
 * @param read_desc (read_desc)
 * @return dst_node (dst_node)
 */
template <typename T>
inline tml::shared_ptr<T> &tml::scene::Manager::GetNode(tml::shared_ptr<T> &dst_node, const WCHAR *class_name, const tml::INIFileReadDesc &read_desc)
{
	dst_node.reset();

	if ((class_name == nullptr)
	|| (class_name[0] == 0)) {
		return (dst_node);
	}

	tml::shared_ptr<tml::scene::Scene> node;

	auto node_factory_itr = this->node_factory_cont_.find(class_name);

	if (node_factory_itr == this->node_factory_cont_.end()) {
		return (dst_node);
	}

	node = node_factory_itr->second(read_desc);

	dst_node = std::dynamic_pointer_cast<T>(node);

	return (dst_node);
}


/**
 * @brief Get関数
 * @return scene (scene)
 */
inline tml::scene::Scene *tml::scene::Manager::Get(void)
{
	return (this->scene_.get());
}
