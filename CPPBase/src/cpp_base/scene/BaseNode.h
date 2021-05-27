/**
 * @file
 * @brief BaseNodeヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SCENE.h"
#include "../../lib/tml/scene/BaseNode.h"


namespace cpp_base {
namespace scene {
/**
 * @brief BaseNodeDescクラス
 */
class BaseNodeDesc : public tml::scene::BaseNodeDesc
{
private:
	cpp_base::scene::Manager *mgr_;

public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	BaseNodeDesc();
	virtual ~BaseNodeDesc();

	virtual void Init(void);

	cpp_base::scene::Manager *GetManager(void) const;
	void SetManager(cpp_base::scene::Manager *);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::BaseNodeDesc::Release(void)
{
	tml::scene::BaseNodeDesc::Release();

	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline cpp_base::scene::Manager *cpp_base::scene::BaseNodeDesc::GetManager(void) const
{
	return (this->mgr_);
}


namespace cpp_base {
namespace scene {
/**
 * @brief BaseNodeクラス
 */
class BaseNode : public tml::scene::BaseNode
{
public: BaseNode(const cpp_base::scene::BaseNode &) = delete;
public: cpp_base::scene::BaseNode &operator =(const cpp_base::scene::BaseNode &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	cpp_base::scene::Manager *mgr_;

protected:
	void Release(void);

public:
	BaseNode();
	virtual ~BaseNode();

	virtual void Init(void);
	INT Create(const cpp_base::scene::BaseNodeDesc &);

	cpp_base::scene::Manager *GetManager(void);
};
}
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline cpp_base::scene::Manager *cpp_base::scene::BaseNode::GetManager(void)
{
	return (this->mgr_);
}
