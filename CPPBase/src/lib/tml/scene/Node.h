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
	bool start_flg_;
	bool started_flg_;
	tml::scene::Node *parent_node_;
	std::list<tml::shared_ptr<tml::scene::Node>> child_node_cont_;
	std::list<tml::shared_ptr<tml::scene::Node>> add_child_node_cont_;
	std::list<tml::shared_ptr<tml::scene::Node>> remove_child_node_cont_;

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
	bool GetStartFlag(void) const;
	void SetStartFlag(const bool);
	bool IsStarted(void) const;
	tml::scene::Node *GetParentNode(void);
	void SetParentNode(tml::scene::Node *);
	const std::list<tml::shared_ptr<tml::scene::Node>> &GetChildNodeContainer(void);
	INT AddChildNode(tml::shared_ptr<tml::scene::Node> &, const bool immediate_flg = false);
	void RemoveChildNode(tml::shared_ptr<tml::scene::Node> &, const bool immediate_flg = false);
};
}
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
 * @brief GetStartFlag関数
 * @return start_flg (start_flag)
 */
inline bool tml::scene::Node::GetStartFlag(void) const
{
	return (this->start_flg_);
}


/**
 * @brief SetStartFlag関数
 * @param start_flg (start_flag)
 */
inline void tml::scene::Node::SetStartFlag(const bool start_flg)
{
	this->start_flg_ = start_flg;

	return;
}


/**
 * @brief IsStarted関数
 * @return res_flg (result_flag)<br>
 * false=非開始済み,true=開始済み
 */
inline bool tml::scene::Node::IsStarted(void) const
{
	return (this->started_flg_);
}


/**
 * @brief GetParentNode関数
 * @return parent_node (parent_node)
 */
inline tml::scene::Node *tml::scene::Node::GetParentNode(void)
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
