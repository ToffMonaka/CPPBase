/**
 * @file
 * @brief Test2DStageNodeコードファイル
 */


#include "Test2DStageNode.h"
#include "../../lib/tml/scene/Node.h"
#include "../constant/ConstantUtil_FILE_PATH.h"
#include "../graphic/Manager.h"
#include "Manager.h"
#include "Field2DNode.h"


/**
 * @brief コンストラクタ
 */
cpp_base::scene::Test2DStageNodeDesc::Test2DStageNodeDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::Test2DStageNodeDesc::~Test2DStageNodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::Test2DStageNodeDesc::Init(void)
{
	this->Release();

	cpp_base::scene::NodeDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Test2DStageNodeDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (cpp_base::scene::NodeDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Test2DStageNode Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"TEST_2D_STAGE_NODE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
cpp_base::scene::Test2DStageNode::Test2DStageNode() :
	desc_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::Test2DStageNode::~Test2DStageNode()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::scene::Test2DStageNode::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::Test2DStageNode::Init(void)
{
	this->Release();

	this->field_layout_node_.reset();

	cpp_base::scene::Node::Init();

	return;
}


/**
 * @brief OnCreate関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Test2DStageNode::OnCreate(void)
{
	if (cpp_base::scene::Node::OnCreate() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnCreateDeferred関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Test2DStageNode::OnCreateDeferred(void)
{
	if (cpp_base::scene::Node::OnCreateDeferred() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnStart関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Test2DStageNode::OnStart(void)
{
	{// FieldLayoutNode Create
		this->field_layout_node_ = this->GetChildNode(L"field_layout");

		if (this->field_layout_node_ == nullptr) {
			return (-1);
		}
	}

	{// FieldNode Create
		tml::shared_ptr<tml::scene::Node> node;

		if (this->GetManager()->GetNode(node, tml::XMLFileReadDesc(cpp_base::ConstantUtil::FILE_PATH::FIELD_2D_NODE_PREFAB)) == nullptr) {
			return (-1);
		}

		this->AddFieldNode(node);
	}

	return (0);
}


/**
 * @brief OnEnd関数
 */
void cpp_base::scene::Test2DStageNode::OnEnd(void)
{
	return;
}


/**
 * @brief OnUpdate関数
 */
void cpp_base::scene::Test2DStageNode::OnUpdate(void)
{
	return;
}


/**
 * @brief OnSetDesc関数
 * @param desc (desc)
 */
void cpp_base::scene::Test2DStageNode::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const cpp_base::scene::Test2DStageNodeDesc *>(desc);

	cpp_base::scene::Node::OnSetDesc(this->desc_);

	return;
}


/**
 * @brief AddFieldNode関数
 * @param field_node (field_node)
 * @param deferred_flg (deferred_flag)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Test2DStageNode::AddFieldNode(const tml::shared_ptr<tml::scene::Node> &field_node, const bool deferred_flg)
{
	this->field_layout_node_->RemoveChildNode(deferred_flg);

	return (this->field_layout_node_->AddChildNode(field_node, deferred_flg));
}


/**
 * @brief RemoveFieldNode関数
 * @param deferred_flg (deferred_flag)
 */
void cpp_base::scene::Test2DStageNode::RemoveFieldNode(const bool deferred_flg)
{
	this->field_layout_node_->RemoveChildNode(deferred_flg);

	return;
}
