/**
 * @file
 * @brief ManagerResourceヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"


namespace tml {
/**
 * @brief ManagerResourceDescクラス
 */
class ManagerResourceDesc
{
public:
	std::wstring name;

protected:
	void Release(void);

public:
	ManagerResourceDesc();
	virtual ~ManagerResourceDesc();

	virtual void Init(void);
};
}


/**
 * @brief Release関数
 */
inline void tml::ManagerResourceDesc::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief ManagerResourceクラス
 *
 * インターフェースパターン
 */
class ManagerResource
{
public: ManagerResource(const tml::ManagerResource &) = delete;
public: tml::ManagerResource &operator =(const tml::ManagerResource &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	UINT res_main_index_;
	UINT res_sub_index_;
	std::wstring name_;

protected:
	void Release(void);
	INT Create(const tml::ManagerResourceDesc &, const UINT, const UINT);

public:
	ManagerResource();
	virtual ~ManagerResource();

	virtual void Init(void);

	UINT GetResourceMainIndex(void) const;
	UINT GetResourceSubIndex(void) const;
	const std::wstring &GetName(void) const;
};
}


/**
 * @brief Release関数
 */
inline void tml::ManagerResource::Release(void)
{
	return;
}


/**
 * @brief GetResourceMainIndex関数
 * @return res_main_index (resource_main_index)
 */
inline UINT tml::ManagerResource::GetResourceMainIndex(void) const
{
	return (this->res_main_index_);
}


/**
 * @brief GetResourceSubIndex関数
 * @return res_sub_index (resource_sub_index)
 */
inline UINT tml::ManagerResource::GetResourceSubIndex(void) const
{
	return (this->res_sub_index_);
}


/**
 * @brief GetName関数
 * @return name (name)
 */
inline const std::wstring &tml::ManagerResource::GetName(void) const
{
	return (this->name_);
}
