/**
 * @file
 * @brief BGMSound�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Sound.h"


namespace tml {
namespace sound {
/**
 * @brief BGMSoundDesc�N���X
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
 * @brief Release�֐�
 */
inline void tml::sound::BGMSoundDesc::Release(void)
{
	tml::sound::SoundDesc::Release();

	return;
}


namespace tml {
namespace sound {
/**
 * @brief BGMSound�N���X
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
 * @brief Release�֐�
 */
inline void tml::sound::BGMSound::Release(void)
{
	tml::sound::Sound::Release();

	return;
}
