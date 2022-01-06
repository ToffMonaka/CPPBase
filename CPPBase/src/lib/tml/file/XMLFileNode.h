/**
 * @file
 * @brief XMLFileNodeヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <list>
#include <map>
#include "../memory/DynamicBuffer.h"


namespace tml {
/**
 * @brief XMLFileNodeクラス
 */
class XMLFileNode
{
public: XMLFileNode(const tml::XMLFileNode &) = delete;
public: tml::XMLFileNode &operator =(const tml::XMLFileNode &) = delete;

public:
	static const tml::shared_ptr<tml::XMLFileNode> empty_child_node;

private:
	tml::XMLFileNode *parent_node_;
	std::list<tml::shared_ptr<tml::XMLFileNode>> child_node_cont_;

public:
	std::wstring name;
	std::map<std::wstring, std::wstring> value_container;
	std::wstring string;

private:
	void Release(void);

	const tml::shared_ptr<tml::XMLFileNode> &GetChildNodeRecursivePart(const std::list<tml::shared_ptr<tml::XMLFileNode>> &, const WCHAR *);

public:
	XMLFileNode();
	virtual ~XMLFileNode();

	virtual void Init(void);

	const std::wstring *GetValue(const WCHAR *) const;
	tml::XMLFileNode *GetParentNode(void);
	tml::XMLFileNode *GetParentNode(const WCHAR *);
	void SetParentNode(tml::XMLFileNode *);
	const std::list<tml::shared_ptr<tml::XMLFileNode>> &GetChildNodeContainer(void);
	const tml::shared_ptr<tml::XMLFileNode> &GetChildNode(void);
	const tml::shared_ptr<tml::XMLFileNode> &GetChildNode(const WCHAR *);
	INT AddChildNode(const tml::shared_ptr<tml::XMLFileNode> &);
	void RemoveChildNode(void);
	void RemoveChildNode(const tml::shared_ptr<tml::XMLFileNode> &);
	void RemoveChildNodeFromParentNode(void);
};
}


/**
 * @brief GetValue関数
 * @param val_name (value_name)
 * @return val (value)<br>
 * nullptr=失敗
 */
inline const std::wstring *tml::XMLFileNode::GetValue(const WCHAR *val_name) const
{
	auto val_itr = this->value_container.find(val_name);

	if (val_itr == this->value_container.end()) {
		return (nullptr);
	}

	return (&val_itr->second);
}


/**
 * @brief GetParentNode関数
 * @return parent_node (parent_node)
 */
inline tml::XMLFileNode *tml::XMLFileNode::GetParentNode(void)
{
	return (this->parent_node_);
}


/**
 * @brief GetParentNode関数
 * @param parent_node_name (parent_node_name)
 * @return parent_node (parent_node)
 */
inline tml::XMLFileNode *tml::XMLFileNode::GetParentNode(const WCHAR *parent_node_name)
{
	auto parent_node = this->parent_node_;

	while (parent_node != nullptr) {
		if (parent_node->name == parent_node_name) {
			break;
		}

		parent_node = parent_node->GetParentNode();
	}

	return (parent_node);
}


/**
 * @brief SetParentNode関数
 * @param parent_node (parent_node)
 */
inline void tml::XMLFileNode::SetParentNode(tml::XMLFileNode *parent_node)
{
	if (parent_node == this) {
		return;
	}

	this->parent_node_ = parent_node;

	return;
}


/**
 * @brief GetChildNodeContainer関数
 * @return child_node_container (child_node_container)
 */
inline const std::list<tml::shared_ptr<tml::XMLFileNode>> &tml::XMLFileNode::GetChildNodeContainer(void)
{
	return (this->child_node_cont_);
}


/**
 * @brief GetChildNode関数
 * @return child_node (child_node)<br>
 * nullptr=失敗
 */
inline const tml::shared_ptr<tml::XMLFileNode> &tml::XMLFileNode::GetChildNode(void)
{
	if (this->child_node_cont_.empty()) {
		return (this->empty_child_node);
	}

	return (this->child_node_cont_.front());
}


/**
 * @brief GetChildNode関数
 * @param child_node_name (child_node_name)
 * @return child_node (child_node)<br>
 * nullptr=失敗
 */
inline const tml::shared_ptr<tml::XMLFileNode> &tml::XMLFileNode::GetChildNode(const WCHAR *child_node_name)
{
	if ((child_node_name == nullptr)
	|| (child_node_name[0] == 0)) {
		return (this->empty_child_node);
	}

	return (this->GetChildNodeRecursivePart(this->child_node_cont_, child_node_name));
}
