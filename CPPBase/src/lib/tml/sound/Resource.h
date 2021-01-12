/**
 * @file
 * @brief Resourceヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"


namespace tml {
namespace sound {
class Manager;
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

public:
	ResourceDesc();
	virtual ~ResourceDesc();

	virtual void Init(void);
};
}
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
	tml::sound::Manager *mgr_;

protected:
	void Release(void);
	INT Create(tml::sound::ResourceDesc &);

public:
	Resource();
	virtual ~Resource();

	virtual void Init(void);

	tml::sound::Manager *GetManager(void) const;
};
}
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::sound::Manager *tml::sound::Resource::GetManager(void) const
{
	return (this->mgr_);
}
