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
public: DefaultRandomUtilEngine(const tml::DefaultRandomUtilEngine &) = delete;
public: tml::DefaultRandomUtilEngine &operator =(const tml::DefaultRandomUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

protected:
	void Release(void);

public:
	DefaultRandomUtilEngine();
	virtual ~DefaultRandomUtilEngine();

	virtual void Init(void);
	INT Create(void);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::DefaultRandomUtilEngine::Release(void)
{
	tml::RandomUtilEngine::Release();

	return;
}
