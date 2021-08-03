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
	static const UINT RESOURCE_SUB_INDEX = static_cast<UINT>(tml::ConstantUtil::SOUND::SOUND_TYPE::BGM);

private:

private:
	void Release(void);

public:
	BGMSound();
	virtual ~BGMSound();

	virtual void Init(void);
	INT Create(const tml::sound::BGMSoundDesc &);
};
}
}
