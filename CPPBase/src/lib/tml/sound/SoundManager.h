/**
 * @file
 * @brief SoundManagerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SOUND.h"


namespace tml {
/**
 * @brief SoundManagerDescクラス
 */
class SoundManagerDesc
{
public:

public:
	SoundManagerDesc();
	virtual ~SoundManagerDesc();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief SoundManagerクラス
 */
class SoundManager
{
public: SoundManager(const tml::SoundManager &) = delete;
public: tml::SoundManager &operator =(const tml::SoundManager &) = delete;

private:

private:
	void Release(void);

public:
	SoundManager();
	virtual ~SoundManager();

	virtual void Init(void);
	INT Create(tml::SoundManagerDesc &);
};
}
