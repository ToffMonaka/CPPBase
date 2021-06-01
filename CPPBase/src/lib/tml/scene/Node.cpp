/**
 * @file
 * @brief Node�R�[�h�t�@�C��
 */


#include "Node.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::scene::NodeDesc::NodeDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::scene::NodeDesc::~NodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::scene::NodeDesc::Init(void)
{
	this->Release();

	tml::scene::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0����=���s
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
 * @brief �R���X�g���N�^
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
 * @brief �f�X�g���N�^
 */
tml::scene::Node::~Node()
{
	return;
}


/**
 * @brief Release�֐�
 */
void tml::scene::Node::Release(void)
{
	for (auto &child_node : this->child_node_cont_) {
		child_node->End();
		child_node->SetParentNode(nullptr);
	}

	this->child_node_cont_.clear();
	this->add_child_node_cont_.clear();
	this->remove_child_node_cont_.clear();

	tml::scene::ManagerResource::Release();

	return;
}


/**
 * @brief Init�֐�
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
 * @brief Create�֐�
 * @param desc (desc)
 * @param type (type)
 * @return res (result)<br>
 * 0����=���s
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
 * @brief Start�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::scene::Node::Start(void)
{
	if (!this->start_flg_) {
		return (-1);
	}

	if (!this->started_flg_) {
		if (this->OnStart() < 0) {
			return (-1);
		}

		this->started_flg_ = true;
	}

	for (auto &child_node : this->child_node_cont_) {
		child_node->Start();
	}

	return (0);
}


/**
 * @brief End�֐�
 */
void tml::scene::Node::End(void)
{
	for (auto &child_node : this->child_node_cont_) {
		child_node->End();
	}

	if (this->started_flg_) {
		this->OnEnd();

		this->started_flg_ = false;
	}

	return;
}


/**
 * @brief Update�֐�
 */
void tml::scene::Node::Update(void)
{
	if (!this->started_flg_) {
		return;
	}

	this->OnUpdate();

	if (this->add_child_node_cont_.size() > 0U) {
		std::list<tml::shared_ptr<tml::scene::Node>> tmp_child_node_cont = std::move(this->add_child_node_cont_);

		for (auto &tmp_child_node : tmp_child_node_cont) {
			this->AddChildNode(tmp_child_node, true);
		}
	}

	if (this->remove_child_node_cont_.size() > 0U) {
		std::list<tml::shared_ptr<tml::scene::Node>> tmp_child_node_cont = std::move(this->remove_child_node_cont_);

		for (auto &tmp_child_node : tmp_child_node_cont) {
			this->RemoveChildNode(tmp_child_node, true);
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
 * @brief SetParentNode�֐�
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
 * @brief AddChildNode�֐�
 * @param child_node (child_node)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::scene::Node::AddChildNode(tml::shared_ptr<tml::scene::Node> &child_node, const bool immediate_flg)
{
	if ((child_node == nullptr)
	|| (child_node.get() == this)) {
		return (-1);
	}

	if (immediate_flg) {
		if (child_node->GetParentNode() != nullptr) {
			return (-1);
		}

		auto child_node_itr = std::find(this->child_node_cont_.begin(), this->child_node_cont_.end(), child_node);

		if (child_node_itr != this->child_node_cont_.end()) {
			return (-1);
		}

		child_node->End();
		child_node->SetParentNode(this);

		this->child_node_cont_.push_back(child_node);
	} else {
		this->add_child_node_cont_.push_back(child_node);
	}

	return (0);
}


/**
 * @brief RemoveChildNode�֐�
 * @param child_node (child_node)
 */
void tml::scene::Node::RemoveChildNode(tml::shared_ptr<tml::scene::Node> &child_node, const bool immediate_flg)
{
	if ((child_node == nullptr)
	|| (child_node.get() == this)) {
		return;
	}

	if (immediate_flg) {
		if (child_node->GetParentNode() == nullptr) {
			return;
		}

		auto child_node_itr = std::find(this->child_node_cont_.begin(), this->child_node_cont_.end(), child_node);

		if (child_node_itr == this->child_node_cont_.end()) {
			return;
		}

		child_node->End();
		child_node->SetParentNode(nullptr);

		this->child_node_cont_.erase(child_node_itr);
	} else {
		this->remove_child_node_cont_.push_back(child_node);
	}

	return;
}
