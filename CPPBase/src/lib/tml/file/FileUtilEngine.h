/**
 * @file
 * @brief FileUtilEngine�w�b�_�[�t�@�C��
 */
#pragma once


#include "../ConstantUtil.h"


namespace tml {
/**
 * @brief FileUtilEngine�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class FileUtilEngine
{
public: FileUtilEngine(const FileUtilEngine &) = delete;
public: FileUtilEngine &operator =(const FileUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

protected:
	void Release(void);
	INT Create(void);

public:
	FileUtilEngine();
	virtual ~FileUtilEngine();

	virtual void Init(void);
};
}
