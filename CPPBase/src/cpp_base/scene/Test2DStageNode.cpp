/**
 * @file
 * @brief Test2DStageNode�R�[�h�t�@�C��
 */


#include "Test2DStageNode.h"
#include "../../lib/tml/scene/Node.h"
#include "../constant/ConstantUtil_FILE_PATH.h"
#include "../graphic/Manager.h"
#include "Manager.h"
#include "Field2DNode.h"


/**
 * @brief �R���X�g���N�^
 */
cpp_base::scene::Test2DStageNodeDesc::Test2DStageNodeDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::scene::Test2DStageNodeDesc::~Test2DStageNodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::scene::Test2DStageNodeDesc::Init(void)
{
	this->Release();

	cpp_base::scene::NodeDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0����=���s
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
 * @brief �R���X�g���N�^
 */
cpp_base::scene::Test2DStageNode::Test2DStageNode()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::scene::Test2DStageNode::~Test2DStageNode()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void cpp_base::scene::Test2DStageNode::Release(void)
{
	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::scene::Test2DStageNode::Init(void)
{
	this->Release();

	this->field_layout_node_.reset();

	cpp_base::scene::Node::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::Test2DStageNode::Create(const cpp_base::scene::Test2DStageNodeDesc &desc)
{
	this->Init();

	if (cpp_base::scene::Node::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief OnStart�֐�
 * @return result (result)<br>
 * 0����=���s
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
 * @brief OnEnd�֐�
 */
void cpp_base::scene::Test2DStageNode::OnEnd(void)
{
	return;
}


/**
 * @brief OnUpdate�֐�
 */
void cpp_base::scene::Test2DStageNode::OnUpdate(void)
{
	return;
}


/**
 * @brief AddFieldNode�֐�
 * @param field_node (field_node)
 * @param event_flg (event_flag)
 * @return result (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::Test2DStageNode::AddFieldNode(const tml::shared_ptr<tml::scene::Node> &field_node, const bool event_flg)
{
	this->field_layout_node_->RemoveChildNode(event_flg);

	return (this->field_layout_node_->AddChildNode(field_node, event_flg));
}


/**
 * @brief RemoveFieldNode�֐�
 * @param event_flg (event_flag)
 */
void cpp_base::scene::Test2DStageNode::RemoveFieldNode(const bool event_flg)
{
	this->field_layout_node_->RemoveChildNode(event_flg);

	return;
}
