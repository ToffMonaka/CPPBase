/**
 * @file
 * @brief Field2DNodeコードファイル
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
 * @brief コンストラクタ
 */
cpp_base::scene::Field2DNodeDesc::Field2DNodeDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::Field2DNodeDesc::~Field2DNodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::Field2DNodeDesc::Init(void)
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
 * @brief コンストラクタ
 */
cpp_base::scene::Field2DNode::Field2DNode() :
	desc_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::Field2DNode::~Field2DNode()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::scene::Field2DNode::Release(void)
{
	return;
}


/**
 * @brief Init関数
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
 * @brief OnCreate関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Field2DNode::OnCreate(void)
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
INT cpp_base::scene::Field2DNode::OnCreateDeferred(void)
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

	{// GroundNode Create
		tml::shared_ptr<tml::scene::Node> node;
		cpp_base::scene::Field2DGroundNodeDesc node_desc;

		node_desc.SetManager(this->GetManager());

		if (this->GetManager()->GetResource<cpp_base::scene::Field2DGroundNode>(node, node_desc) == nullptr) {
			return (-1);
		}

		this->AddGroundNode(node);
	}

	{// PlayerNode Create
		tml::shared_ptr<tml::scene::Node> node;
		cpp_base::scene::Field2DPlayerNodeDesc node_desc;

		node_desc.SetManager(this->GetManager());
		node_desc.transform_2d = tml::Transform2D(tml::XMFLOAT2EX(0.0f, -128.0f));

		if (this->GetManager()->GetResource<cpp_base::scene::Field2DPlayerNode>(node, node_desc) == nullptr) {
			return (-1);
		}

		this->AddPlayerNode(node);
	}

	{// MobNode Create
		tml::shared_ptr<tml::scene::Node> node;
		cpp_base::scene::Field2DMobNodeDesc node_desc;

		node_desc.SetManager(this->GetManager());
		node_desc.transform_2d = tml::Transform2D(tml::XMFLOAT2EX(0.0f, 128.0f));

		if (this->GetManager()->GetResource<cpp_base::scene::Field2DMobNode>(node, node_desc) == nullptr) {
			return (-1);
		}

		this->AddMobNode(node);
	}

	return (0);
}


/**
 * @brief OnEnd関数
 */
void cpp_base::scene::Field2DNode::OnEnd(void)
{
	return;
}


/**
 * @brief OnUpdate関数
 */
void cpp_base::scene::Field2DNode::OnUpdate(void)
{
	return;
}


/**
 * @brief OnSetDesc関数
 * @param desc (desc)
 */
void cpp_base::scene::Field2DNode::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const cpp_base::scene::Field2DNodeDesc *>(desc);

	cpp_base::scene::Node::OnSetDesc(this->desc_);

	return;
}


/**
 * @brief AddGroundNode関数
 * @param ground_node (ground_node)
 * @param deferred_flg (deferred_flag)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Field2DNode::AddGroundNode(const tml::shared_ptr<tml::scene::Node> &ground_node, const bool deferred_flg)
{
	this->ground_layout_node_->RemoveChildNode(deferred_flg);

	return (this->ground_layout_node_->AddChildNode(ground_node, deferred_flg));
}


/**
 * @brief RemoveGroundNode関数
 * @param deferred_flg (deferred_flag)
 */
void cpp_base::scene::Field2DNode::RemoveGroundNode(const bool deferred_flg)
{
	this->ground_layout_node_->RemoveChildNode(deferred_flg);

	return;
}


/**
 * @brief AddPlayerNode関数
 * @param pl_node (player_node)
 * @param deferred_flg (deferred_flag)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Field2DNode::AddPlayerNode(const tml::shared_ptr<tml::scene::Node> &pl_node, const bool deferred_flg)
{
	this->pl_layout_node_->RemoveChildNode(deferred_flg);

	return (this->pl_layout_node_->AddChildNode(pl_node, deferred_flg));
}


/**
 * @brief RemovePlayerNode関数
 * @param deferred_flg (deferred_flag)
 */
void cpp_base::scene::Field2DNode::RemovePlayerNode(const bool deferred_flg)
{
	this->pl_layout_node_->RemoveChildNode(deferred_flg);

	return;
}


/**
 * @brief AddMobNode関数
 * @param mob_node (mob_node)
 * @param deferred_flg (deferred_flag)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Field2DNode::AddMobNode(const tml::shared_ptr<tml::scene::Node> &mob_node, const bool deferred_flg)
{
	return (this->mob_layout_node_->AddChildNode(mob_node, deferred_flg));
}


/**
 * @brief RemoveMobNode関数
 * @param deferred_flg (deferred_flag)
 */
void cpp_base::scene::Field2DNode::RemoveMobNode(const bool deferred_flg)
{
	this->mob_layout_node_->RemoveChildNode(deferred_flg);

	return;
}


/**
 * @brief AddBulletNode関数
 * @param bullet_node (bullet_node)
 * @param deferred_flg (deferred_flag)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Field2DNode::AddBulletNode(const tml::shared_ptr<tml::scene::Node> &bullet_node, const bool deferred_flg)
{
	return (this->bullet_layout_node_->AddChildNode(bullet_node, deferred_flg));
}


/**
 * @brief RemoveBulletNode関数
 * @param deferred_flg (deferred_flag)
 */
void cpp_base::scene::Field2DNode::RemoveBulletNode(const bool deferred_flg)
{
	this->bullet_layout_node_->RemoveChildNode(deferred_flg);

	return;
}
