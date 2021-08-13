/**
 * @file
 * @brief Manager�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../manager/Manager.h"
#include "ManagerFactory.h"
#include "ManagerCommon.h"


namespace tml {
namespace sound {
/**
 * @brief ManagerDesc�N���X
 */
class ManagerDesc : public tml::ManagerDesc
{
public:
	std::array<FLOAT, tml::ConstantUtil::SOUND::SOUND_TYPE_COUNT> volume_array;
	std::array<bool, tml::ConstantUtil::SOUND::SOUND_TYPE_COUNT> mute_flag_array;

private:
	void Release(void);

protected:
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
 * @brief Release�֐�
 */
inline void tml::sound::ManagerDesc::Release(void)
{
	return;
}


/**
 * @brief GetVolume�֐�
 * @param type (type)
 * @return volume (volume)
 */
inline FLOAT tml::sound::ManagerDesc::GetVolume(const tml::ConstantUtil::SOUND::SOUND_TYPE type) const
{
	return (this->volume_array[static_cast<UINT>(type)]);
}


/**
 * @brief SetVolume�֐�
 * @param type (type)
 * @param volume (volume)
 */
inline void tml::sound::ManagerDesc::SetVolume(const tml::ConstantUtil::SOUND::SOUND_TYPE type, const FLOAT volume)
{
	this->volume_array[static_cast<UINT>(type)] = volume;

	return;
}


/**
 * @brief GetMuteFlag�֐�
 * @param type (type)
 * @return mute_flg (mute_flag)
 */
inline bool tml::sound::ManagerDesc::GetMuteFlag(const tml::ConstantUtil::SOUND::SOUND_TYPE type) const
{
	return (this->mute_flag_array[static_cast<UINT>(type)]);
}


/**
 * @brief SetMuteFlag�֐�
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
 * @brief Manager�N���X
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
	tml::sound::ManagerFactory factory;
	std::map<std::wstring, std::wstring> factory_value_container;
	tml::sound::ManagerCommon common;

private:
	void Release(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(const tml::sound::ManagerDesc &);

	void Update(void);
	const std::wstring *GetFactoryValue(const WCHAR *) const;

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
 * @brief GetFactoryValue�֐�
 * @param factory_val_name (factory_value_name)
 * @return factory_val (factory_value)<br>
 * nullptr=���s
 */
inline const std::wstring *tml::sound::Manager::GetFactoryValue(const WCHAR *factory_val_name) const
{
	auto factory_val_itr = this->factory_value_container.find(factory_val_name);

	if (factory_val_itr == this->factory_value_container.end()) {
		return (nullptr);
	}

	return (&factory_val_itr->second);
}


/**
 * @brief GetDevice�֐�
 * @return device (device)
 */
inline ALCdevice *tml::sound::Manager::GetDevice(void)
{
	return (this->device_);
}


/**
 * @brief GetDeviceContext�֐�
 * @return device_context (device_context)
 */
inline ALCcontext *tml::sound::Manager::GetDeviceContext(void)
{
	return (this->device_context_);
}


/**
 * @brief GetVolume�֐�
 * @param type (type)
 * @return volume (volume)
 */
inline FLOAT tml::sound::Manager::GetVolume(const tml::ConstantUtil::SOUND::SOUND_TYPE type) const
{
	return (this->volume_ary_[static_cast<UINT>(type)]);
}


/**
 * @brief GetMuteFlag�֐�
 * @param type (type)
 * @return mute_flg (mute_flag)
 */
inline bool tml::sound::Manager::GetMuteFlag(const tml::ConstantUtil::SOUND::SOUND_TYPE type) const
{
	return (this->mute_flg_ary_[static_cast<UINT>(type)]);
}
