/**
 * @file
 * @brief Nodeコードファイル
 */


#include "Node.h"
#include "Manager.h"
#include "NodeEvent.h"


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
	run_flg_(false),
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
		child_node->SetRunFlag(false);
		child_node->SetParentNode(nullptr);
	}

	this->child_node_cont_.clear();

	tml::scene::ManagerResource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::Node::Init(void)
{
	this->type_ = tml::ConstantUtil::SCENE::NODE_TYPE::NONE;
	this->run_flg_ = false;
	this->start_flg_ = false;
	this->started_flg_ = false;
	this->parent_node_ = nullptr;

	this->name.clear();

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
 * 0未満=失敗
 */
INT tml::scene::Node::Start(void)
{
	if ((!this->run_flg_) || (!this->start_flg_)) {
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
 * @brief End関数
 */
void tml::scene::Node::End(void)
{
	if (!this->run_flg_) {
		return;
	}

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
 * @brief Update関数
 */
void tml::scene::Node::Update(void)
{
	if ((!this->run_flg_) || (!this->started_flg_)) {
		return;
	}

	this->OnUpdate();

	for (auto &child_node : this->child_node_cont_) {
		if (!child_node->IsStarted()) {
			if (child_node->GetStartFlag()) {
				child_node->Start();
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
 * @brief SetRunFlag関数
 * @param run_flg (run_flag)
 */
void tml::scene::Node::SetRunFlag(const bool run_flg)
{
	this->run_flg_ = run_flg;

	for (auto &child_node : this->child_node_cont_) {
		child_node->SetRunFlag(run_flg);
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
 * @param event_flg (event_flag)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::scene::Node::AddChildNode(const tml::shared_ptr<tml::scene::Node> &child_node, const bool event_flg)
{
	if ((child_node == nullptr)
	|| (child_node.get() == this)) {
		return (-1);
	}

	if (event_flg) {
		tml::scene::NodeEventDesc event_desc;

		event_desc.SetManager(this->GetManager());
		event_desc.data.type = tml::ConstantUtil::SCENE::NODE_EVENT_DATA_TYPE::ADD;
		event_desc.data.parent_node = std::reinterpret_pointer_cast<tml::scene::Node>(this->GetResourceSharedPointer());
		event_desc.data.child_node = child_node;

		if (this->GetManager()->AddEvent<tml::scene::NodeEvent>(event_desc) < 0) {
			return (-1);
		}
	} else {
		if (child_node->GetParentNode() != nullptr) {
			return (-1);
		}

		auto child_node_itr = std::find(this->child_node_cont_.begin(), this->child_node_cont_.end(), child_node);

		if (child_node_itr != this->child_node_cont_.end()) {
			return (-1);
		}

		child_node->End();
		child_node->SetRunFlag(this->run_flg_);
		child_node->SetParentNode(this);

		this->child_node_cont_.push_back(child_node);
	}

	return (0);
}


/**
 * @brief RemoveChildNode関数
 * @param child_node (child_node)
 * @param event_flg (event_flag)
 */
void tml::scene::Node::RemoveChildNode(const tml::shared_ptr<tml::scene::Node> &child_node, const bool event_flg)
{
	if ((child_node == nullptr)
	|| (child_node.get() == this)) {
		return;
	}

	if (event_flg) {
		tml::scene::NodeEventDesc event_desc;

		event_desc.SetManager(this->GetManager());
		event_desc.data.type = tml::ConstantUtil::SCENE::NODE_EVENT_DATA_TYPE::REMOVE;
		event_desc.data.parent_node = std::reinterpret_pointer_cast<tml::scene::Node>(this->GetResourceSharedPointer());
		event_desc.data.child_node = child_node;

		if (this->GetManager()->AddEvent<tml::scene::NodeEvent>(event_desc) < 0) {
			return;
		}
	} else {
		if (child_node->GetParentNode() == nullptr) {
			return;
		}

		auto child_node_itr = std::find(this->child_node_cont_.begin(), this->child_node_cont_.end(), child_node);

		if (child_node_itr == this->child_node_cont_.end()) {
			return;
		}

		child_node->End();
		child_node->SetRunFlag(false);
		child_node->SetParentNode(nullptr);

		this->child_node_cont_.erase(child_node_itr);
	}

	return;
}
