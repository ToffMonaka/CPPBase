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
	tml::shared_ptr<tml::scene::Node> parent_node_;
	std::list<tml::shared_ptr<tml::scene::Node>> child_node_cont_;
	bool started_flg_;

protected:
	void Release(void);
	INT Create(const tml::scene::NodeDesc &, const tml::ConstantUtil::SCENE::NODE_TYPE);

public:
	Node();
	virtual ~Node();

	virtual void Init(void);

	INT Start(void);
	void End(void);
	void Update(void);

	virtual INT OnStart(void) = 0;
	virtual void OnEnd(void) = 0;
	virtual void OnUpdate(void) = 0;

	tml::ConstantUtil::SCENE::NODE_TYPE GetType(void) const;
	const tml::shared_ptr<tml::scene::Node> &GetParentNode(void);
	void SetParentNode(const tml::shared_ptr<tml::scene::Node> &);
	const std::list<tml::shared_ptr<tml::scene::Node>> &GetChildNodeContainer(void);
	INT AddChildNode(const tml::shared_ptr<tml::scene::Node> &);
	void RemoveChildNode(const tml::shared_ptr<tml::scene::Node> &);
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


/**
 * @brief GetParentNode関数
 * @return parent_node (parent_node)
 */
inline const tml::shared_ptr<tml::scene::Node> &tml::scene::Node::GetParentNode(void)
{
	return (this->parent_node_);
}


/**
 * @brief GetChildNodeContainer関数
 * @return child_node_container (child_node_container)
 */
inline const std::list<tml::shared_ptr<tml::scene::Node>> &tml::scene::Node::GetChildNodeContainer(void)
{
	return (this->child_node_cont_);
}
