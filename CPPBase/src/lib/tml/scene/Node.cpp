/**
 * @file
 * @brief Nodeコードファイル
 */


#include "Node.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::scene::NodeDesc::NodeDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::NodeDesc::~NodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::NodeDesc::Init(void)
{
	this->Release();

	tml::scene::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::scene::NodeDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::scene::ManagerResourceDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Node Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"NODE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::scene::Node::Node() :
	type_(tml::ConstantUtil::SCENE::NODE_TYPE::NONE),
	start_flg_(false),
	started_flg_(false),
	parent_node_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::Node::~Node()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::scene::Node::Release(void)
{
	for (auto &child_node : this->child_node_cont_) {
		child_node->End();
		child_node->SetParentNode(nullptr);

		child_node.reset();
	}

	this->child_node_cont_.clear();
	this->add_child_node_cont_.clear();
	this->remove_child_node_cont_.clear();

	tml::scene::ManagerResource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::Node::Init(void)
{
	this->type_ = tml::ConstantUtil::SCENE::NODE_TYPE::NONE;
	this->start_flg_ = false;
	this->started_flg_ = false;
	this->parent_node_ = nullptr;

	tml::scene::ManagerResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @param type (type)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::scene::Node::Create(const tml::scene::NodeDesc &desc, const tml::ConstantUtil::SCENE::NODE_TYPE type)
{
	if (type == tml::ConstantUtil::SCENE::NODE_TYPE::NONE) {
		return (-1);
	}

	if (tml::scene::ManagerResource::Create(desc, tml::ConstantUtil::SCENE::RESOURCE_TYPE::NODE, static_cast<UINT>(type)) < 0) {
		return (-1);
	}

	this->type_ = type;
	this->start_flg_ = true;

	return (0);
}


/**
 * @brief Start関数
 * @return res (result)<br>
 * 0未満=失敗,1=開始済み
 */
INT tml::scene::Node::Start(void)
{
	if (this->started_flg_) {
		return (1);
	}

	if (this->OnStart() < 0) {
		return (-1);
	}

	this->started_flg_ = true;

	for (auto &child_node : this->child_node_cont_) {
		child_node->Start();
	}

	return (0);
}


/**
 * @brief End関数
 */
void tml::scene::Node::End(void)
{
	if (!this->started_flg_) {
		return;
	}

	for (auto &child_node : this->child_node_cont_) {
		child_node->End();
	}

	this->OnEnd();

	this->started_flg_ = false;

	return;
}


/**
 * @brief Update関数
 */
void tml::scene::Node::Update(void)
{
	if (!this->started_flg_) {
		return;
	}

	this->OnUpdate();

	if (this->add_child_node_cont_.size() > 0U) {
		std::list<tml::shared_ptr<tml::scene::Node>> tmp_add_child_node_cont = std::move(this->add_child_node_cont_);

		for (auto &child_node : tmp_add_child_node_cont) {
			auto child_node_itr = std::find(this->child_node_cont_.begin(), this->child_node_cont_.end(), child_node);

			if (child_node_itr != this->child_node_cont_.end()) {
				continue;
			}

			if (!child_node->IsStarted()) {
				this->child_node_cont_.push_back(child_node);

				child_node->SetParentNode(this);
			}
		}
	}

	if (this->remove_child_node_cont_.size() > 0U) {
		std::list<tml::shared_ptr<tml::scene::Node>> tmp_remove_child_node_cont = std::move(this->remove_child_node_cont_);

		for (auto &child_node : tmp_remove_child_node_cont) {
			auto child_node_itr = std::find(this->child_node_cont_.begin(), this->child_node_cont_.end(), child_node);

			if (child_node_itr == this->child_node_cont_.end()) {
				continue;
			}

			child_node->End();
			child_node->SetParentNode(nullptr);

			this->child_node_cont_.erase(child_node_itr);
		}
	}

	for (auto &child_node : this->child_node_cont_) {
		if (!child_node->IsStarted()) {
			if (child_node->GetStartFlag()) {
				if (child_node->Start() < 0) {
				} else {
				}
			}
		}

		if (child_node->GetStartFlag()) {
			child_node->Update();
		}

		if (!child_node->GetStartFlag()) {
			child_node->End();
		}
	}

	return;
}


/**
 * @brief SetParentNode関数
 * @param parent_node (parent_node)
 */
void tml::scene::Node::SetParentNode(tml::scene::Node *parent_node)
{
	if (parent_node == this) {
		return;
	}

	this->parent_node_ = parent_node;

	return;
}


/**
 * @brief AddChildNode関数
 * @param child_node (child_node)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::scene::Node::AddChildNode(tml::shared_ptr<tml::scene::Node> &child_node)
{
	if ((child_node == nullptr)
	|| (child_node.get() == this)) {
		return (-1);
	}

	if (this->started_flg_) {
		this->add_child_node_cont_.push_back(child_node);
	} else {
		auto child_node_itr = std::find(this->child_node_cont_.begin(), this->child_node_cont_.end(), child_node);

		if (child_node_itr != this->child_node_cont_.end()) {
			return (-1);
		}

		if (!child_node->IsStarted()) {
			this->child_node_cont_.push_back(child_node);

			child_node->SetParentNode(this);
		}
	}

	return (0);
}


/**
 * @brief RemoveChildNode関数
 * @param child_node (child_node)
 */
void tml::scene::Node::RemoveChildNode(tml::shared_ptr<tml::scene::Node> &child_node)
{
	if ((child_node == nullptr)
	|| (child_node.get() == this)) {
		return;
	}

	if (this->started_flg_) {
		this->remove_child_node_cont_.push_back(child_node);
	} else {
		auto child_node_itr = std::find(this->child_node_cont_.begin(), this->child_node_cont_.end(), child_node);

		if (child_node_itr == this->child_node_cont_.end()) {
			return;
		}

		child_node->End();
		child_node->SetParentNode(nullptr);

		this->child_node_cont_.erase(child_node_itr);
	}

	return;
}
