/**
 * @file
 * @brief Field2DNode�R�[�h�t�@�C��
 */


#include "Field2DNode.h"
#include "../../lib/tml/scene/Node.h"
#include "../graphic/Manager.h"
#include "Manager.h"
#include "Field2DGroundNode.h"
#include "Field2DPlayerNode.h"
#include "Field2DMobNode.h"
#include "Field2DBulletNode.h"


/**
 * @brief �R���X�g���N�^
 */
cpp_base::scene::Field2DNodeDesc::Field2DNodeDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::scene::Field2DNodeDesc::~Field2DNodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::scene::Field2DNodeDesc::Init(void)
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
INT cpp_base::scene::Field2DNodeDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (cpp_base::scene::NodeDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Field2DNode Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"FIELD_2D_NODE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief �R���X�g���N�^
 */
cpp_base::scene::Field2DNode::Field2DNode()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::scene::Field2DNode::~Field2DNode()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void cpp_base::scene::Field2DNode::Release(void)
{
	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::scene::Field2DNode::Init(void)
{
	this->Release();

	this->ground_layout_node_.reset();
	this->pl_layout_node_.reset();
	this->mob_layout_node_.reset();
	this->bullet_layout_node_.reset();

	cpp_base::scene::Node::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::Field2DNode::Create(const cpp_base::scene::Field2DNodeDesc &desc)
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
INT cpp_base::scene::Field2DNode::OnStart(void)
{
	{// GroundLayoutNode Create
		this->ground_layout_node_ = this->GetChildNode(L"ground_layout");

		if (this->ground_layout_node_ == nullptr) {
			return (-1);
		}
	}

	{// PlayerLayoutNode Create
		this->pl_layout_node_ = this->GetChildNode(L"pl_layout");

		if (this->pl_layout_node_ == nullptr) {
			return (-1);
		}
	}

	{// MobLayoutNode Create
		this->mob_layout_node_ = this->GetChildNode(L"mob_layout");

		if (this->mob_layout_node_ == nullptr) {
			return (-1);
		}
	}

	{// BulletLayoutNode Create
		this->bullet_layout_node_ = this->GetChildNode(L"bullet_layout");

		if (this->bullet_layout_node_ == nullptr) {
			return (-1);
		}
	}

	tml::shared_ptr<tml::scene::Node> ground_node;

	{// GroundNode Create
		cpp_base::scene::Field2DGroundNodeDesc node_desc;

		node_desc.SetManager(this->GetManager());

		if (this->GetManager()->GetResource<cpp_base::scene::Field2DGroundNode>(ground_node, node_desc) == nullptr) {
			return (-1);
		}
	}

	this->AddGroundNode(ground_node);

	tml::shared_ptr<tml::scene::Node> pl_node;

	{// PlayerNode Create
		cpp_base::scene::Field2DPlayerNodeDesc node_desc;

		node_desc.SetManager(this->GetManager());

		if (this->GetManager()->GetResource<cpp_base::scene::Field2DPlayerNode>(pl_node, node_desc) == nullptr) {
			return (-1);
		}
	}

	this->AddPlayerNode(pl_node);

	tml::shared_ptr<tml::scene::Node> mob_node;

	{// MobNode Create
		cpp_base::scene::Field2DMobNodeDesc node_desc;

		node_desc.SetManager(this->GetManager());

		if (this->GetManager()->GetResource<cpp_base::scene::Field2DMobNode>(mob_node, node_desc) == nullptr) {
			return (-1);
		}
	}

	this->AddMobNode(mob_node);

	return (0);
}


/**
 * @brief OnEnd�֐�
 */
void cpp_base::scene::Field2DNode::OnEnd(void)
{
	this->ground_layout_node_.reset();
	this->pl_layout_node_.reset();
	this->mob_layout_node_.reset();
	this->bullet_layout_node_.reset();

	return;
}


/**
 * @brief OnUpdate�֐�
 */
void cpp_base::scene::Field2DNode::OnUpdate(void)
{
	return;
}


/**
 * @brief AddGroundNode�֐�
 * @param ground_node (ground_node)
 * @param event_flg (event_flag)
 * @return result (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::Field2DNode::AddGroundNode(const tml::shared_ptr<tml::scene::Node> &ground_node, const bool event_flg)
{
	this->ground_layout_node_->RemoveChildNode(event_flg);

	return (this->ground_layout_node_->AddChildNode(ground_node, event_flg));
}


/**
 * @brief RemoveGroundNode�֐�
 * @param event_flg (event_flag)
 */
void cpp_base::scene::Field2DNode::RemoveGroundNode(const bool event_flg)
{
	this->ground_layout_node_->RemoveChildNode(event_flg);

	return;
}


/**
 * @brief AddPlayerNode�֐�
 * @param pl_node (player_node)
 * @param event_flg (event_flag)
 * @return result (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::Field2DNode::AddPlayerNode(const tml::shared_ptr<tml::scene::Node> &pl_node, const bool event_flg)
{
	this->pl_layout_node_->RemoveChildNode(event_flg);

	return (this->pl_layout_node_->AddChildNode(pl_node, event_flg));
}


/**
 * @brief RemovePlayerNode�֐�
 * @param event_flg (event_flag)
 */
void cpp_base::scene::Field2DNode::RemovePlayerNode(const bool event_flg)
{
	this->pl_layout_node_->RemoveChildNode(event_flg);

	return;
}


/**
 * @brief AddMobNode�֐�
 * @param mob_node (mob_node)
 * @param event_flg (event_flag)
 * @return result (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::Field2DNode::AddMobNode(const tml::shared_ptr<tml::scene::Node> &mob_node, const bool event_flg)
{
	return (this->mob_layout_node_->AddChildNode(mob_node, event_flg));
}


/**
 * @brief RemoveMobNode�֐�
 * @param event_flg (event_flag)
 */
void cpp_base::scene::Field2DNode::RemoveMobNode(const bool event_flg)
{
	this->mob_layout_node_->RemoveChildNode(event_flg);

	return;
}


/**
 * @brief AddBulletNode�֐�
 * @param bullet_node (bullet_node)
 * @param event_flg (event_flag)
 * @return result (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::Field2DNode::AddBulletNode(const tml::shared_ptr<tml::scene::Node> &bullet_node, const bool event_flg)
{
	return (this->bullet_layout_node_->AddChildNode(bullet_node, event_flg));
}


/**
 * @brief RemoveBulletNode�֐�
 * @param event_flg (event_flag)
 */
void cpp_base::scene::Field2DNode::RemoveBulletNode(const bool event_flg)
{
	this->bullet_layout_node_->RemoveChildNode(event_flg);

	return;
}
