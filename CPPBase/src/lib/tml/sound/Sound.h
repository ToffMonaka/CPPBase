/**
 * @file
 * @brief Sound�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Resource.h"


namespace tml {
namespace sound {
/**
 * @brief SoundDesc�N���X
 */
class SoundDesc : public tml::sound::ResourceDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	SoundDesc();
	virtual ~SoundDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::sound::SoundDesc::Release(void)
{
	tml::sound::ResourceDesc::Release();

	return;
}


namespace tml {
namespace sound {
/**
 * @brief Sound�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class Sound : public tml::sound::Resource
{
public: Sound(const tml::sound::Sound &) = delete;
public: tml::sound::Sound &operator =(const tml::sound::Sound &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::ConstantUtil::SOUND::SOUND_TYPE type_;

protected:
	void Release(void);
	INT Create(const tml::sound::SoundDesc &, const tml::ConstantUtil::SOUND::SOUND_TYPE);

public:
	Sound();
	virtual ~Sound();

	virtual void Init(void);

	tml::ConstantUtil::SOUND::SOUND_TYPE GetType(void) const;
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::sound::Sound::Release(void)
{
	tml::sound::Resource::Release();

	return;
}


/**
 * @brief GetType�֐�
 * @return type (type)
 */
inline tml::ConstantUtil::SOUND::SOUND_TYPE tml::sound::Sound::GetType(void) const
{
	return (this->type_);
}
