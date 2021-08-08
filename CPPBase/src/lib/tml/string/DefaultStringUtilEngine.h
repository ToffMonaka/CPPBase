/**
 * @file
 * @brief DefaultStringUtilEngine�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "StringUtilEngine.h"


namespace tml {
/**
 * @brief DefaultStringUtilEngine�N���X
 */
class DefaultStringUtilEngine : public tml::StringUtilEngine
{
public: DefaultStringUtilEngine(const tml::DefaultStringUtilEngine &) = delete;
public: tml::DefaultStringUtilEngine &operator =(const tml::DefaultStringUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	void Release(void);

public:
	DefaultStringUtilEngine();
	virtual ~DefaultStringUtilEngine();

	virtual void Init(void);
	INT Create(const CHAR *);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::DefaultStringUtilEngine::Release(void)
{
	return;
}
