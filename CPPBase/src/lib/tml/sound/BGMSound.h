/**
 * @file
 * @brief BGMSoundヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Sound.h"


namespace tml {
namespace sound {
/**
 * @brief BGMSoundDescクラス
 */
class BGMSoundDesc : public tml::sound::SoundDesc
{
public:

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	BGMSoundDesc();
	virtual ~BGMSoundDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::sound::BGMSoundDesc::Release(void)
{
	return;
}


namespace tml {
namespace sound {
/**
 * @brief BGMSoundクラス
 */
class BGMSound : public tml::sound::Sound
{
public: BGMSound(const tml::sound::BGMSound &) = delete;
public: tml::sound::BGMSound &operator =(const tml::sound::BGMSound &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT RESOURCE_TYPE = static_cast<UINT>(tml::ConstantUtil::SOUND::RESOURCE_TYPE::BGM_SOUND);

private:
	const tml::sound::BGMSoundDesc *desc_;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);

public:
	BGMSound();
	virtual ~BGMSound();

	virtual void Init(void);

	const tml::sound::BGMSoundDesc *GetDesc(void) const;
};
}
}


/**
 * @brief GetDesc関数
 * @return desc (desc)
 */
inline const tml::sound::BGMSoundDesc *tml::sound::BGMSound::GetDesc(void) const
{
	return (this->desc_);
}
