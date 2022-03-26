/**
 * @file
 * @brief NodeTaskコードファイル
 */


#include "NodeTask.h"
#include "Manager.h"
#include "Node.h"


/**
 * @brief コンストラクタ
 */
tml::scene::NodeTaskDesc::NodeTaskDesc() :
	run_type(tml::ConstantUtil::SCENE::NODE_TASK_RUN_TYPE::NONE)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::NodeTaskDesc::~NodeTaskDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::NodeTaskDesc::Init(void)
{
	this->Release();

	this->run_type = tml::ConstantUtil::SCENE::NODE_TASK_RUN_TYPE::NONE;
	this->node.reset();
	this->child_node.reset();

	tml::scene::ManagerTaskDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::scene::NodeTaskDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::scene::ManagerTaskDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// NodeTask Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"NODE_TASK");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::scene::NodeTask::NodeTask() :
	run_type_(tml::ConstantUtil::SCENE::NODE_TASK_RUN_TYPE::NONE)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::NodeTask::~NodeTask()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::NodeTask::Init(void)
{
	this->Release();

	this->run_type_ = tml::ConstantUtil::SCENE::NODE_TASK_RUN_TYPE::NONE;
	this->node_.reset();
	this->child_node_.reset();

	tml::scene::ManagerTask::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::scene::NodeTask::Create(const tml::scene::NodeTaskDesc &desc)
{
	this->Init();

	if (tml::scene::ManagerTask::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	this->run_type_ = desc.run_type;
	this->node_ = desc.node;
	this->child_node_ = desc.child_node;

	return (0);
}


/**
 * @brief OnRun関数
 */
void tml::scene::NodeTask::OnRun(void)
{
	switch (this->run_type_) {
	case tml::ConstantUtil::SCENE::NODE_TASK_RUN_TYPE::ADD_CHILD_NODE: {
		if (this->node_ != nullptr) {
			if (this->child_node_ != nullptr) {
				this->node_->AddChildNode(this->child_node_, false);
			}
		}

		break;
	}
	case tml::ConstantUtil::SCENE::NODE_TASK_RUN_TYPE::REMOVE_CHILD_NODE: {
		if (this->node_ != nullptr) {
			if (this->child_node_ != nullptr) {
				this->node_->RemoveChildNode(this->child_node_, false);
			} else {
				this->node_->RemoveChildNode(false);
			}
		} else {
			if (this->child_node_ != nullptr) {
				this->child_node_->RemoveChildNodeFromParentNode(false);
			}
		}

		break;
	}
	}

	this->SetRunFlag(false);

	return;
}
