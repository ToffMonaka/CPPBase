/**
 * @file
 * @brief DefaultThreadUtilEngine�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ThreadUtilEngine.h"


namespace tml {
/**
 * @brief DefaultThreadUtilEngine�N���X
 */
class DefaultThreadUtilEngine : public tml::ThreadUtilEngine
{
public: DefaultThreadUtilEngine(const DefaultThreadUtilEngine &) = delete;
public: DefaultThreadUtilEngine &operator =(const DefaultThreadUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	void Release(void);

public:
	DefaultThreadUtilEngine();
	virtual ~DefaultThreadUtilEngine();

	virtual void Init(void);
	INT Create(void);
};
}
