/**
 * @file
 * @brief FileUtilEngine�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../thread/MutexThreadLock.h"
#include "../thread/SpinThreadLock.h"


namespace tml {
/**
 * @brief FileUtilEngine�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class FileUtilEngine
{
public: FileUtilEngine(const tml::FileUtilEngine &) = delete;
public: tml::FileUtilEngine &operator =(const tml::FileUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	void Release(void);

public:
	FileUtilEngine();
	virtual ~FileUtilEngine();

	virtual void Init(void);
	INT Create(void);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::FileUtilEngine::Release(void)
{
	return;
}
