/**
 * @file
 * @brief TimeUtilEngine�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"


namespace tml {
/**
 * @brief TimeUtilEngine�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class TimeUtilEngine
{
public: TimeUtilEngine(const tml::TimeUtilEngine &) = delete;
public: tml::TimeUtilEngine &operator =(const tml::TimeUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

protected:
	void Release(void);
	INT Create(void);

public:
	TimeUtilEngine();
	virtual ~TimeUtilEngine();

	virtual void Init(void);
};
}
