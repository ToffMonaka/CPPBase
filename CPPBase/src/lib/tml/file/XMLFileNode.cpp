/**
 * @file
 * @brief XMLFileNodeコードファイル
 */


#include "XMLFileNode.h"


const tml::shared_ptr<tml::XMLFileNode> tml::XMLFileNode::empty_child_node;


/**
 * @brief コンストラクタ
 */
tml::XMLFileNodeDesc::XMLFileNodeDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::XMLFileNodeDesc::~XMLFileNodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::XMLFileNodeDesc::Init(void)
{
	this->Release();

	this->name.clear();
	this->value_container.clear();
	this->string.clear();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::XMLFileNode::XMLFileNode() :
	parent_node_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::XMLFileNode::~XMLFileNode()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::XMLFileNode::Release(void)
{
	for (auto &child_node : this->child_node_cont_) {
		child_node->SetParentNode(nullptr);
	}

	this->child_node_cont_.clear();

	return;
}


/**
 * @brief Init関数
 */
void tml::XMLFileNode::Init(void)
{
	this->Release();

	this->parent_node_ = nullptr;

	this->name.clear();
	this->value_container.clear();
	this->string.clear();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::XMLFileNode::Create(const tml::XMLFileNodeDesc &desc)
{
	this->Init();

	this->name = desc.name;
	this->value_container = desc.value_container;
	this->string = desc.string;

	return (0);
}


/**
 * @brief GetChildNodeRecursivePart関数
 * @param child_node_cont (child_node_container)
 * @param child_node_name (child_node_name)
 * @return child_node (child_node)
 */
const tml::shared_ptr<tml::XMLFileNode> &tml::XMLFileNode::GetChildNodeRecursivePart(const std::list<tml::shared_ptr<tml::XMLFileNode>> &child_node_cont, const WCHAR *child_node_name)
{
	for (auto &child_node : child_node_cont) {
		if (child_node->name == child_node_name) {
			return (child_node);
		}

		auto &child_child_node = this->GetChildNodeRecursivePart(child_node->GetChildNodeContainer(), child_node_name);

		if (child_child_node != nullptr) {
			return (child_child_node);
		}
	}

	return (this->empty_child_node);
}


/**
 * @brief AddChildNode関数
 * @param child_node (child_node)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::XMLFileNode::AddChildNode(const tml::shared_ptr<tml::XMLFileNode> &child_node)
{
	if ((child_node == nullptr)
	|| (child_node.get() == this)) {
		return (-1);
	}

	if (child_node->GetParentNode() != nullptr) {
		return (-1);
	}

	auto child_node_itr = std::find(this->child_node_cont_.begin(), this->child_node_cont_.end(), child_node);

	if (child_node_itr != this->child_node_cont_.end()) {
		return (-1);
	}

	child_node->SetParentNode(this);

	this->child_node_cont_.push_back(child_node);

	return (0);
}


/**
 * @brief RemoveChildNode関数
 */
void tml::XMLFileNode::RemoveChildNode(void)
{
	std::list<tml::shared_ptr<tml::XMLFileNode>> child_node_cont = this->child_node_cont_;

	for (auto &child_node : child_node_cont) {
		this->RemoveChildNode(child_node);
	}

	return;
}


/**
 * @brief RemoveChildNode関数
 * @param child_node (child_node)
 */
void tml::XMLFileNode::RemoveChildNode(const tml::shared_ptr<tml::XMLFileNode> &child_node)
{
	if ((child_node == nullptr)
	|| (child_node.get() == this)) {
		return;
	}

	if (child_node->GetParentNode() == nullptr) {
		return;
	}

	auto child_node_itr = std::find(this->child_node_cont_.begin(), this->child_node_cont_.end(), child_node);

	if (child_node_itr == this->child_node_cont_.end()) {
		return;
	}

	child_node->SetParentNode(nullptr);

	this->child_node_cont_.erase(child_node_itr);

	return;
}


/**
 * @brief RemoveChildNodeFromParentNode関数
 */
void tml::XMLFileNode::RemoveChildNodeFromParentNode(void)
{
	if (this->parent_node_ == nullptr) {
		return;
	}

	tml::shared_ptr<tml::XMLFileNode> tmp_child_node;

	for (auto &child_node : this->parent_node_->child_node_cont_) {
		if (child_node.get() == this) {
			tmp_child_node = child_node;

			break;
		}
	}

	if (tmp_child_node == nullptr) {
		return;
	}

	this->parent_node_->RemoveChildNode(tmp_child_node);

	return;
}
