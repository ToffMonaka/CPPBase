/**
 * @file
 * @brief StringUtilEngineヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"


namespace tml {
/**
 * @brief StringUtilEngineクラス
 *
 * インターフェースパターン
 */
class StringUtilEngine
{
public: StringUtilEngine(const tml::StringUtilEngine &) = delete;
public: tml::StringUtilEngine &operator =(const tml::StringUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	std::string locale_name_;

protected:
	void Release(void);
	INT Create(const CHAR *);

public:
	StringUtilEngine();
	virtual ~StringUtilEngine();

	virtual void Init(void);

	const std::string &GetLocaleName(void) const;
};
}


/**
 * @brief GetLocaleName関数
 * @return locale_name (locale_name)
 */
inline const std::string &tml::StringUtilEngine::GetLocaleName(void) const
{
	return (this->locale_name_);
}
