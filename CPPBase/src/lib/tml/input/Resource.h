/**
 * @file
 * @brief Resourceヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"


namespace tml {
namespace input {
class Manager;
}
}


namespace tml {
namespace input {
/**
 * @brief ResourceDescクラス
 */
class ResourceDesc
{
public:
	tml::input::Manager *manager;

public:
	ResourceDesc();
	virtual ~ResourceDesc();

	virtual void Init(void);
};
}
}


namespace tml {
namespace input {
/**
 * @brief Resourceクラス
 *
 * インターフェースパターン
 */
class Resource
{
public: Resource(const tml::input::Resource &) = delete;
public: tml::input::Resource &operator =(const tml::input::Resource &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::input::Manager *mgr_;

protected:
	void Release(void);
	INT Create(tml::input::ResourceDesc &);

public:
	Resource();
	virtual ~Resource();

	virtual void Init(void);

	tml::input::Manager *GetManager(void) const;
};
}
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::input::Manager *tml::input::Resource::GetManager(void) const
{
	return (this->mgr_);
}
