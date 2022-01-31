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
 * @brief FileUtilEngineDesc�N���X
 */
class FileUtilEngineDesc
{
public:

private:
	void Release(void);

public:
	FileUtilEngineDesc();
	virtual ~FileUtilEngineDesc();

	virtual void Init(void);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::FileUtilEngineDesc::Release(void)
{
	return;
}


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

private:
	void Release(void);

public:
	FileUtilEngine();
	virtual ~FileUtilEngine();

	virtual void Init(void);
	INT Create(const tml::FileUtilEngineDesc &);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::FileUtilEngine::Release(void)
{
	return;
}
