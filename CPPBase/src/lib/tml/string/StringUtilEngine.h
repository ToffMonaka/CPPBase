/**
 * @file
 * @brief StringUtilEngine�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../thread/MutexThreadLock.h"
#include "../thread/SpinThreadLock.h"


namespace tml {
/**
 * @brief StringUtilEngineDesc�N���X
 */
class StringUtilEngineDesc
{
public:
	std::string locale_name;

private:
	void Release(void);

public:
	StringUtilEngineDesc();
	virtual ~StringUtilEngineDesc();

	virtual void Init(void);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::StringUtilEngineDesc::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief StringUtilEngine�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class StringUtilEngine
{
public: StringUtilEngine(const tml::StringUtilEngine &) = delete;
public: tml::StringUtilEngine &operator =(const tml::StringUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	std::string locale_name_;

private:
	void Release(void);

public:
	StringUtilEngine();
	virtual ~StringUtilEngine();

	virtual void Init(void);
	INT Create(const tml::StringUtilEngineDesc &);

	const std::string &GetLocaleName(void) const;
};
}


/**
 * @brief Release�֐�
 */
inline void tml::StringUtilEngine::Release(void)
{
	return;
}


/**
 * @brief GetLocaleName�֐�
 * @return locale_name (locale_name)
 */
inline const std::string &tml::StringUtilEngine::GetLocaleName(void) const
{
	return (this->locale_name_);
}
