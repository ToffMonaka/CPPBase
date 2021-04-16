#if 0
/**
 * @file
 * @brief Resourceヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SOUND.h"
#include "../file/INIFile.h"


namespace tml {
namespace sound {
class Manager;
class Sound;
class BGMSound;
class SESound;
}
}


namespace tml {
namespace sound {
/**
 * @brief ResourceDescクラス
 */
class ResourceDesc
{
public:
	tml::sound::Manager *manager;
	std::wstring name;

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	ResourceDesc();
	virtual ~ResourceDesc();

	virtual void Init(void);

	INT Read(const tml::INIFileReadDesc &);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::sound::ResourceDesc::Release(void)
{
	return;
}


namespace tml {
namespace sound {
/**
 * @brief Resourceクラス
 *
 * インターフェースパターン
 */
class Resource
{
public: Resource(const tml::sound::Resource &) = delete;
public: tml::sound::Resource &operator =(const tml::sound::Resource &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::ConstantUtil::SOUND::RESOURCE_TYPE res_type_;
	tml::sound::Manager *mgr_;
	std::wstring name_;

protected:
	void Release(void);
	INT Create(const tml::sound::ResourceDesc &, const tml::ConstantUtil::SOUND::RESOURCE_TYPE);

public:
	Resource();
	virtual ~Resource();

	virtual void Init(void);

	tml::ConstantUtil::SOUND::RESOURCE_TYPE GetResourceType(void) const;
	tml::sound::Manager *GetManager(void);
	const std::wstring &GetName(void) const;
};
}
}


/**
 * @brief Release関数
 */
inline void tml::sound::Resource::Release(void)
{
	return;
}


/**
 * @brief GetResourceType関数
 * @return res_type (resource_type)
 */
inline tml::ConstantUtil::SOUND::RESOURCE_TYPE tml::sound::Resource::GetResourceType(void) const
{
	return (this->res_type_);
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::sound::Manager *tml::sound::Resource::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetName関数
 * @return name (name)
 */
inline const std::wstring &tml::sound::Resource::GetName(void) const
{
	return (this->name_);
}
#endif
