/**
 * @file
 * @brief Managerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../manager/Manager.h"
#include "ManagerCommon.h"


namespace tml {
namespace sound {
/**
 * @brief ManagerDescクラス
 */
class ManagerDesc : public tml::ManagerDesc
{
public:
	std::array<FLOAT, tml::ConstantUtil::SOUND::SOUND_TYPE_COUNT> volume_array;
	std::array<bool, tml::ConstantUtil::SOUND::SOUND_TYPE_COUNT> mute_flag_array;

protected:
	void Release(void);

	void InitResourceCount(void);
	void InitEventCount(void);

public:
	ManagerDesc();
	virtual ~ManagerDesc();

	virtual void Init(void);

	FLOAT GetVolume(const tml::ConstantUtil::SOUND::SOUND_TYPE) const;
	void SetVolume(const tml::ConstantUtil::SOUND::SOUND_TYPE, const FLOAT);
	bool GetMuteFlag(const tml::ConstantUtil::SOUND::SOUND_TYPE) const;
	void SetMuteFlag(const tml::ConstantUtil::SOUND::SOUND_TYPE, const bool);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::sound::ManagerDesc::Release(void)
{
	tml::ManagerDesc::Release();

	return;
}


/**
 * @brief GetVolume関数
 * @param type (type)
 * @return volume (volume)
 */
inline FLOAT tml::sound::ManagerDesc::GetVolume(const tml::ConstantUtil::SOUND::SOUND_TYPE type) const
{
	return (this->volume_array[static_cast<UINT>(type)]);
}


/**
 * @brief SetVolume関数
 * @param type (type)
 * @param volume (volume)
 */
inline void tml::sound::ManagerDesc::SetVolume(const tml::ConstantUtil::SOUND::SOUND_TYPE type, const FLOAT volume)
{
	this->volume_array[static_cast<UINT>(type)] = volume;

	return;
}


/**
 * @brief GetMuteFlag関数
 * @param type (type)
 * @return mute_flg (mute_flag)
 */
inline bool tml::sound::ManagerDesc::GetMuteFlag(const tml::ConstantUtil::SOUND::SOUND_TYPE type) const
{
	return (this->mute_flag_array[static_cast<UINT>(type)]);
}


/**
 * @brief SetMuteFlag関数
 * @param type (type)
 * @param mute_flg (mute_flag)
 */
inline void tml::sound::ManagerDesc::SetMuteFlag(const tml::ConstantUtil::SOUND::SOUND_TYPE type, const bool mute_flg)
{
	this->mute_flag_array[static_cast<UINT>(type)] = mute_flg;

	return;
}


namespace tml {
namespace sound {
/**
 * @brief Managerクラス
 */
class Manager : public tml::Manager
{
public: Manager(const tml::sound::Manager &) = delete;
public: tml::sound::Manager &operator =(const tml::sound::Manager &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	ALCdevice *device_;
	ALCcontext *device_context_;
	std::array<FLOAT, tml::ConstantUtil::SOUND::SOUND_TYPE_COUNT> volume_ary_;
	std::array<bool, tml::ConstantUtil::SOUND::SOUND_TYPE_COUNT> mute_flg_ary_;

public:
	tml::sound::ManagerCommon common;

protected:
	void Release(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(const tml::sound::ManagerDesc &);

	void Update(void);

	ALCdevice *GetDevice(void);
	ALCcontext *GetDeviceContext(void);
	FLOAT GetVolume(const tml::ConstantUtil::SOUND::SOUND_TYPE) const;
	void SetVolume(const tml::ConstantUtil::SOUND::SOUND_TYPE, const FLOAT);
	bool GetMuteFlag(const tml::ConstantUtil::SOUND::SOUND_TYPE) const;
	void SetMuteFlag(const tml::ConstantUtil::SOUND::SOUND_TYPE, const bool);

	void PlaySound(tml::sound::Sound *, const bool);
	void StopSound(tml::sound::Sound *);
	void PauseSound(tml::sound::Sound *);
};
}
}


/**
 * @brief GetDevice関数
 * @return device (device)
 */
inline ALCdevice *tml::sound::Manager::GetDevice(void)
{
	return (this->device_);
}


/**
 * @brief GetDeviceContext関数
 * @return device_context (device_context)
 */
inline ALCcontext *tml::sound::Manager::GetDeviceContext(void)
{
	return (this->device_context_);
}


/**
 * @brief GetVolume関数
 * @param type (type)
 * @return volume (volume)
 */
inline FLOAT tml::sound::Manager::GetVolume(const tml::ConstantUtil::SOUND::SOUND_TYPE type) const
{
	return (this->volume_ary_[static_cast<UINT>(type)]);
}


/**
 * @brief GetMuteFlag関数
 * @param type (type)
 * @return mute_flg (mute_flag)
 */
inline bool tml::sound::Manager::GetMuteFlag(const tml::ConstantUtil::SOUND::SOUND_TYPE type) const
{
	return (this->mute_flg_ary_[static_cast<UINT>(type)]);
}
