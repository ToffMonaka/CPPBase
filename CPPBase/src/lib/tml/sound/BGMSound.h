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

protected:
	void Release(void);

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
	tml::sound::SoundDesc::Release();

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

private:

protected:
	void Release(void);

public:
	BGMSound();
	virtual ~BGMSound();

	virtual void Init(void);
	INT Create(const tml::sound::BGMSoundDesc &);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::sound::BGMSound::Release(void)
{
	tml::sound::Sound::Release();

	return;
}
