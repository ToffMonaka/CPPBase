/**
 * @file
 * @brief SoundResource�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"


namespace tml {
class SoundManager;
}


namespace tml {
/**
 * @brief SoundResourceDesc�N���X
 */
class SoundResourceDesc
{
public:
	tml::SoundManager *manager;

public:
	SoundResourceDesc();
	virtual ~SoundResourceDesc();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief SoundResource�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class SoundResource
{
public: SoundResource(const tml::SoundResource &) = delete;
public: tml::SoundResource &operator =(const tml::SoundResource &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::SoundManager *mgr_;

protected:
	void Release(void);
	INT Create(const tml::SoundResourceDesc &);

public:
	SoundResource();
	virtual ~SoundResource();

	virtual void Init(void);

	tml::SoundManager *GetManager(void) const;
};
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::SoundManager *tml::SoundResource::GetManager(void) const
{
	return (this->mgr_);
}
