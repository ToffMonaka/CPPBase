/**
 * @file
 * @brief Base2DNodeヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SCENE.h"
#include "../../lib/tml/scene/Base2DNode.h"


namespace cpp_base {
namespace scene {
/**
 * @brief Base2DNodeDescクラス
 */
class Base2DNodeDesc : public tml::scene::Base2DNodeDesc
{
private:
	cpp_base::scene::Manager *mgr_;

public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	Base2DNodeDesc();
	virtual ~Base2DNodeDesc();

	virtual void Init(void);

	cpp_base::scene::Manager *GetManager(void) const;
	void SetManager(cpp_base::scene::Manager *);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::Base2DNodeDesc::Release(void)
{
	tml::scene::Base2DNodeDesc::Release();

	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline cpp_base::scene::Manager *cpp_base::scene::Base2DNodeDesc::GetManager(void) const
{
	return (this->mgr_);
}


namespace cpp_base {
namespace scene {
/**
 * @brief Base2DNodeクラス
 */
class Base2DNode : public tml::scene::Base2DNode
{
public: Base2DNode(const cpp_base::scene::Base2DNode &) = delete;
public: cpp_base::scene::Base2DNode &operator =(const cpp_base::scene::Base2DNode &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	cpp_base::scene::Manager *mgr_;

protected:
	void Release(void);

public:
	Base2DNode();
	virtual ~Base2DNode();

	virtual void Init(void);
	INT Create(const cpp_base::scene::Base2DNodeDesc &);

	cpp_base::scene::Manager *GetManager(void) const;
};
}
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline cpp_base::scene::Manager *cpp_base::scene::Base2DNode::GetManager(void) const
{
	return (this->mgr_);
}
