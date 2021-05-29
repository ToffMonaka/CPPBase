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
	started_flg_(false)
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
 * @brief Init�֐�
 */
void tml::scene::Node::Init(void)
{
	this->type_ = tml::ConstantUtil::SCENE::NODE_TYPE::NONE;
	this->parent_node_.reset();
	this->child_node_cont_.clear();
	this->started_flg_ = false;

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

	return (0);
}


/**
 * @brief Start�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::scene::Node::Start(void)
{
	if (this->started_flg_) {
		return (0);
	}

	if (this->OnStart() < 0) {
		return (-1);
	}

	this->started_flg_ = true;

	return (0);
}


/**
 * @brief End�֐�
 */
void tml::scene::Node::End(void)
{
	if (!this->started_flg_) {
		return;
	}

	this->OnEnd();

	this->started_flg_ = false;

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

	return;
}


/**
 * @brief SetParentNode�֐�
 * @param parent_node (parent_node)
 */
void tml::scene::Node::SetParentNode(const tml::shared_ptr<tml::scene::Node> &parent_node)
{
	if (parent_node.get() == this) {
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
INT tml::scene::Node::AddChildNode(const tml::shared_ptr<tml::scene::Node> &child_node)
{
	if ((child_node == nullptr)
	|| (child_node.get() == this)) {
		return (-1);
	}

	this->child_node_cont_.push_back(child_node);

	return (0);
}


/**
 * @brief RemoveChildNode�֐�
 * @param child_node (child_node)
 */
void tml::scene::Node::RemoveChildNode(const tml::shared_ptr<tml::scene::Node> &child_node)
{
	if ((child_node == nullptr)
	|| (child_node.get() == this)) {
		return;
	}

	this->child_node_cont_.remove(child_node);

	return;
}
