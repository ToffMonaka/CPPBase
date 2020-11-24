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
public: TimeUtilEngine(const TimeUtilEngine &) = delete;
public: TimeUtilEngine &operator =(const TimeUtilEngine &) = delete;
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
