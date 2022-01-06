/**
 * @file
 * @brief Managerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../time/FrameRate.h"
#include "../file/XMLFile.h"
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
	UINT frame_rate_limit;

private:
	void Release(void);

protected:
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
	UINT frame_rate_limit_;
	tml::TIME_REAL elapsed_time_;
	std::chrono::steady_clock::time_point cpu_start_time_;
	tml::TIME_REAL cpu_elapsed_time_;
	std::chrono::steady_clock::time_point gpu_start_time_;
	tml::TIME_REAL gpu_elapsed_time_;
	tml::shared_ptr<tml::scene::Scene> scene_;

public:
	tml::scene::ManagerCommon common;

private:
	void Release(void);

	tml::shared_ptr<tml::scene::Scene> &GetSceneGetPart(tml::shared_ptr<tml::scene::Scene> &, const tml::shared_ptr<tml::XMLFileNode> &, INT *dst_result = nullptr);
	tml::shared_ptr<tml::scene::Node> &GetNodeGetPart(tml::shared_ptr<tml::scene::Node> &, const tml::shared_ptr<tml::XMLFileNode> &, INT *dst_result = nullptr);
	void GetNodeRecursivePart(const tml::shared_ptr<tml::scene::Scene> &, const tml::shared_ptr<tml::XMLFileNode> &);
	void GetNodeRecursivePart(const tml::shared_ptr<tml::scene::Node> &, const tml::shared_ptr<tml::XMLFileNode> &);

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
	UINT GetFrameRateLimit(void) const;
	const tml::TIME_REAL &GetElapsedTime(void) const;
	const tml::TIME_REAL &GetCPUElapsedTime(void) const;
	const tml::TIME_REAL &GetGPUElapsedTime(void) const;

	tml::shared_ptr<tml::scene::Scene> &GetScene(tml::shared_ptr<tml::scene::Scene> &, const tml::XMLFileReadDesc &, INT *dst_result = nullptr);
	const tml::shared_ptr<tml::scene::Scene> &GetScene(void);
	INT StartScene(const tml::shared_ptr<tml::scene::Scene> &);
	void EndScene(void);
	tml::shared_ptr<tml::scene::Node> &GetNode(tml::shared_ptr<tml::scene::Node> &, const tml::XMLFileReadDesc &, INT *dst_result = nullptr);
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
 * @brief GetFrameRateLimit関数
 * @return frame_rate_limit (frame_rate_limit)
 */
inline UINT tml::scene::Manager::GetFrameRateLimit(void) const
{
	return (this->frame_rate_limit_);
}


/**
 * @brief GetElapsedTime関数
 * @return elapsed_time (elapsed_time)
 */
inline const tml::TIME_REAL &tml::scene::Manager::GetElapsedTime(void) const
{
	return (this->elapsed_time_);
}


/**
 * @brief GetCPUElapsedTime関数
 * @return cpu_elapsed_time (cpu_elapsed_time)
 */
inline const tml::TIME_REAL &tml::scene::Manager::GetCPUElapsedTime(void) const
{
	return (this->cpu_elapsed_time_);
}


/**
 * @brief GetGPUElapsedTime関数
 * @return gpu_elapsed_time (gpu_elapsed_time)
 */
inline const tml::TIME_REAL &tml::scene::Manager::GetGPUElapsedTime(void) const
{
	return (this->gpu_elapsed_time_);
}


/**
 * @brief GetScene関数
 * @return scene (scene)
 */
inline const tml::shared_ptr<tml::scene::Scene> &tml::scene::Manager::GetScene(void)
{
	return (this->scene_);
}
