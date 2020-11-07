/**
 * @file
 * @brief StringUtilEngine�w�b�_�[�t�@�C��
 */
#pragma once


#include "../ConstantUtil.h"


namespace tml {
/**
 * @brief StringUtilEngine�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class StringUtilEngine
{
public: StringUtilEngine(const StringUtilEngine &) = delete;
public: StringUtilEngine &operator =(const StringUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

protected:
	void Release(void);
	INT Create(void);

public:
	StringUtilEngine();
	virtual ~StringUtilEngine();

	virtual void Init(void);
};
}
