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
	FLOAT bgm_sound_volume;
	bool bgm_sound_mute_flag;
	FLOAT se_sound_volume;
	bool se_sound_mute_flag;

private:
	void Release(void);

public:
	ManagerDesc();
	virtual ~ManagerDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::sound::ManagerDesc::Release(void)
{
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
	std::vector<FLOAT> sound_volume_cont_;
	std::vector<bool> sound_mute_flg_cont_;

public:
	tml::sound::ManagerCommon common;

private:
	void Release(void);

	void SetSoundVolumePart(const UINT);
	void SetSoundMuteFlagPart(const UINT);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(const tml::sound::ManagerDesc &);

	void Update(void);

	ALCdevice *GetDevice(void);
	ALCcontext *GetDeviceContext(void);
	FLOAT GetBGMSoundVolume(void) const;
	void SetBGMSoundVolume(const FLOAT);
	bool GetBGMSoundMuteFlag(void) const;
	void SetBGMSoundMuteFlag(const bool);
	FLOAT GetSESoundVolume(void) const;
	void SetSESoundVolume(const FLOAT);
	bool GetSESoundMuteFlag(void) const;
	void SetSESoundMuteFlag(const bool);

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
 * @brief GetBGMSoundVolume関数
 * @return bgm_sound_volume (bgm_sound_volume)
 */
inline FLOAT tml::sound::Manager::GetBGMSoundVolume(void) const
{
	return (this->sound_volume_cont_[static_cast<UINT>(tml::ConstantUtil::SOUND::RESOURCE_TYPE::BGM_SOUND)]);
}


/**
 * @brief SetBGMSoundVolume関数
 * @param bgm_sound_volume (bgm_sound_volume)
 */
inline void tml::sound::Manager::SetBGMSoundVolume(const FLOAT bgm_sound_volume)
{
	this->sound_volume_cont_[static_cast<UINT>(tml::ConstantUtil::SOUND::RESOURCE_TYPE::BGM_SOUND)] = bgm_sound_volume;

	this->SetSoundVolumePart(static_cast<UINT>(tml::ConstantUtil::SOUND::RESOURCE_TYPE::BGM_SOUND));

	return;
}


/**
 * @brief GetBGMSoundMuteFlag関数
 * @return bgm_sound_mute_flg (bgm_sound_mute_flag)
 */
inline bool tml::sound::Manager::GetBGMSoundMuteFlag(void) const
{
	return (this->sound_mute_flg_cont_[static_cast<UINT>(tml::ConstantUtil::SOUND::RESOURCE_TYPE::BGM_SOUND)]);
}


/**
 * @brief SetBGMSoundMuteFlag関数
 * @param bgm_sound_mute_flg (bgm_sound_mute_flag)
 */
inline void tml::sound::Manager::SetBGMSoundMuteFlag(const bool bgm_sound_mute_flg)
{
	this->sound_mute_flg_cont_[static_cast<UINT>(tml::ConstantUtil::SOUND::RESOURCE_TYPE::BGM_SOUND)] = bgm_sound_mute_flg;

	this->SetSoundMuteFlagPart(static_cast<UINT>(tml::ConstantUtil::SOUND::RESOURCE_TYPE::BGM_SOUND));

	return;
}


/**
 * @brief GetSESoundVolume関数
 * @return se_sound_volume (se_sound_volume)
 */
inline FLOAT tml::sound::Manager::GetSESoundVolume(void) const
{
	return (this->sound_volume_cont_[static_cast<UINT>(tml::ConstantUtil::SOUND::RESOURCE_TYPE::SE_SOUND)]);
}


/**
 * @brief SetSESoundVolume関数
 * @param se_sound_volume (se_sound_volume)
 */
inline void tml::sound::Manager::SetSESoundVolume(const FLOAT se_sound_volume)
{
	this->sound_volume_cont_[static_cast<UINT>(tml::ConstantUtil::SOUND::RESOURCE_TYPE::SE_SOUND)] = se_sound_volume;

	this->SetSoundVolumePart(static_cast<UINT>(tml::ConstantUtil::SOUND::RESOURCE_TYPE::SE_SOUND));

	return;
}


/**
 * @brief GetSESoundMuteFlag関数
 * @return se_sound_mute_flg (se_sound_mute_flag)
 */
inline bool tml::sound::Manager::GetSESoundMuteFlag(void) const
{
	return (this->sound_mute_flg_cont_[static_cast<UINT>(tml::ConstantUtil::SOUND::RESOURCE_TYPE::SE_SOUND)]);
}


/**
 * @brief SetSESoundMuteFlag関数
 * @param se_sound_mute_flg (se_sound_mute_flag)
 */
inline void tml::sound::Manager::SetSESoundMuteFlag(const bool se_sound_mute_flg)
{
	this->sound_mute_flg_cont_[static_cast<UINT>(tml::ConstantUtil::SOUND::RESOURCE_TYPE::SE_SOUND)] = se_sound_mute_flg;

	this->SetSoundMuteFlagPart(static_cast<UINT>(tml::ConstantUtil::SOUND::RESOURCE_TYPE::SE_SOUND));

	return;
}
