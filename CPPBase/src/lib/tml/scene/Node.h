/**
 * @file
 * @brief Nodeヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ManagerResource.h"


namespace tml {
namespace scene {
/**
 * @brief NodeDescクラス
 */
class NodeDesc : public tml::scene::ManagerResourceDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	NodeDesc();
	virtual ~NodeDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::scene::NodeDesc::Release(void)
{
	tml::scene::ManagerResourceDesc::Release();

	return;
}


namespace tml {
namespace scene {
/**
 * @brief Nodeクラス
 *
 * インターフェースパターン
 */
class Node : public tml::scene::ManagerResource
{
public: Node(const tml::scene::Node &) = delete;
public: tml::scene::Node &operator =(const tml::scene::Node &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::ConstantUtil::SCENE::NODE_TYPE type_;

protected:
	void Release(void);
	INT Create(const tml::scene::NodeDesc &, const tml::ConstantUtil::SCENE::NODE_TYPE);

public:
	Node();
	virtual ~Node();

	virtual void Init(void);

	tml::ConstantUtil::SCENE::NODE_TYPE GetType(void) const;
};
}
}


/**
 * @brief Release関数
 */
inline void tml::scene::Node::Release(void)
{
	tml::scene::ManagerResource::Release();

	return;
}


/**
 * @brief GetType関数
 * @return type (type)
 */
inline tml::ConstantUtil::SCENE::NODE_TYPE tml::scene::Node::GetType(void) const
{
	return (this->type_);
}
