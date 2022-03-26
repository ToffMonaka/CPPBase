/**
 * @file
 * @brief SESound�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Sound.h"


namespace tml {
namespace sound {
/**
 * @brief SESoundDesc�N���X
 */
class SESoundDesc : public tml::sound::SoundDesc
{
public:

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	SESoundDesc();
	virtual ~SESoundDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::sound::SESoundDesc::Release(void)
{
	return;
}


namespace tml {
namespace sound {
/**
 * @brief SESound�N���X
 */
class SESound : public tml::sound::Sound
{
public: SESound(const tml::sound::SESound &) = delete;
public: tml::sound::SESound &operator =(const tml::sound::SESound &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT RESOURCE_TYPE = static_cast<UINT>(tml::ConstantUtil::SOUND::RESOURCE_TYPE::SE_SOUND);

private:
	const tml::sound::SESoundDesc *desc_;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);

public:
	SESound();
	virtual ~SESound();

	virtual void Init(void);

	const tml::sound::SESoundDesc *GetDesc(void) const;
};
}
}


/**
 * @brief GetDesc�֐�
 * @return desc (desc)
 */
inline const tml::sound::SESoundDesc *tml::sound::SESound::GetDesc(void) const
{
	return (this->desc_);
}
