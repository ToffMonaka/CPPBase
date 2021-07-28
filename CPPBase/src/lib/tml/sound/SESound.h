/**
 * @file
 * @brief SESoundヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Sound.h"


namespace tml {
namespace sound {
/**
 * @brief SESoundDescクラス
 */
class SESoundDesc : public tml::sound::SoundDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	SESoundDesc();
	virtual ~SESoundDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::sound::SESoundDesc::Release(void)
{
	tml::sound::SoundDesc::Release();

	return;
}


namespace tml {
namespace sound {
/**
 * @brief SESoundクラス
 */
class SESound : public tml::sound::Sound
{
public: SESound(const tml::sound::SESound &) = delete;
public: tml::sound::SESound &operator =(const tml::sound::SESound &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT RESOURCE_SUB_INDEX = static_cast<UINT>(tml::ConstantUtil::SOUND::SOUND_TYPE::SE);

private:

protected:
	void Release(void);

public:
	SESound();
	virtual ~SESound();

	virtual void Init(void);
	INT Create(const tml::sound::SESoundDesc &);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::sound::SESound::Release(void)
{
	tml::sound::Sound::Release();

	return;
}
