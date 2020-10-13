/**
 * @file
 * @brief DefaultMemoryUtilEngine�w�b�_�[�t�@�C��
 */
#pragma once


#include "../ConstantUtil.h"
#include "MemoryUtilEngine.h"


namespace tml {
/**
 * @brief DefaultMemoryUtilEngine�N���X
 */
class DefaultMemoryUtilEngine : public tml::MemoryUtilEngine
{
public: DefaultMemoryUtilEngine(const DefaultMemoryUtilEngine &) = delete;
public: DefaultMemoryUtilEngine &operator =(const DefaultMemoryUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	void Release(void);

public:
	DefaultMemoryUtilEngine();
	virtual ~DefaultMemoryUtilEngine();

	void Init(void);
	INT Create(void);
};
}
