/**
 * @file
 * @brief DefaultRandomUtilEngine�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "RandomUtilEngine.h"


namespace tml {
/**
 * @brief DefaultRandomUtilEngine�N���X
 */
class DefaultRandomUtilEngine : public tml::RandomUtilEngine
{
public: DefaultRandomUtilEngine(const DefaultRandomUtilEngine &) = delete;
public: DefaultRandomUtilEngine &operator =(const DefaultRandomUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	void Release(void);

public:
	DefaultRandomUtilEngine();
	virtual ~DefaultRandomUtilEngine();

	virtual void Init(void);
	INT Create(void);
};
}
