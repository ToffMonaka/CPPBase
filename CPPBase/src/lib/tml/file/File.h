/**
 * @file
 * @brief File�w�b�_�[�t�@�C��
 */
#pragma once


#include "../ConstantUtil.h"


namespace tml {
/**
 * @brief File�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class File
{
public: File(const File &) = delete;
public: File &operator =(const File &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

protected:
	void Release(void);

public:
	File();
	virtual ~File();

	virtual void Init(void);

	virtual INT Read(void) = 0;
	virtual INT Write(void) = 0;
};
}
