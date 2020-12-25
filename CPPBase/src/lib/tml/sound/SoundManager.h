/**
 * @file
 * @brief SoundManager�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SOUND.h"


namespace tml {
/**
 * @brief SoundManager�N���X
 */
class SoundManager
{
public: SoundManager(const tml::SoundManager &) = delete;
public: tml::SoundManager &operator =(const tml::SoundManager &) = delete;

private:
	void Release(void);

public:
	SoundManager();
	virtual ~SoundManager();

	virtual void Init(void);
	INT Create(void);
};
}
