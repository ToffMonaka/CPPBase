/**
 * @file
 * @brief Field2DNodeコードファイル
 */


#include "Field2DNode.h"
#include "../../lib/tml/graphic/Canvas2D.h"
#include "../../lib/tml/scene/Node.h"
#include "../graphic/Manager.h"
#include "Manager.h"
#include "Field2DGroundNode.h"
#include "Field2DPlayerNode.h"
#include "Field2DMobNode.h"


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
 * @param ini_file (ini_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Field2DNodeDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (cpp_base::scene::NodeDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Field2DNode Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"FIELD_2D_NODE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
cpp_base::scene::Field2DNode::Field2DNode()
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

	this->canvas_2d.reset();
	this->ground_layout_node.reset();
	this->ground_node.reset();
	this->player_layout_node.reset();
	this->player_node.reset();
	this->mob_layout_node.reset();
	this->mob_node.reset();

	cpp_base::scene::Node::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
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
 * @brief OnStart関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Field2DNode::OnStart(void)
{
	{// Canvas2D Create
		if (this->GetGraphicManager()->GetResource<tml::graphic::Canvas2D>(this->canvas_2d, L"Canvas2D") == nullptr) {
			return (-1);
		}
	}

	{// GroundLayoutNode Create
		this->ground_layout_node = this->GetChildNode(L"ground_layout");

		if (this->ground_layout_node == nullptr) {
			return (-1);
		}
	}

	{// GroundNode Create
		if (this->GetManager()->factory.node_by_ini_file.Get(this->ground_node, cpp_base::ConstantUtil::SCENE::CLASS_NAME::FIELD_2D_GROUND_NODE, tml::INIFileReadDesc()) == nullptr) {
			return (-1);
		}

		this->ground_layout_node->AddChildNode(this->ground_node);
	}

	{// PlayerLayoutNode Create
		this->player_layout_node = this->GetChildNode(L"pl_layout");

		if (this->player_layout_node == nullptr) {
			return (-1);
		}
	}

	{// PlayerNode Create
		if (this->GetManager()->factory.node_by_ini_file.Get(this->player_node, cpp_base::ConstantUtil::SCENE::CLASS_NAME::FIELD_2D_PLAYER_NODE, tml::INIFileReadDesc()) == nullptr) {
			return (-1);
		}

		this->player_layout_node->AddChildNode(this->player_node);
	}

	{// MobLayoutNode Create
		this->mob_layout_node = this->GetChildNode(L"mob_layout");

		if (this->mob_layout_node == nullptr) {
			return (-1);
		}
	}

	{// MobNode Create
		if (this->GetManager()->factory.node_by_ini_file.Get(this->mob_node, cpp_base::ConstantUtil::SCENE::CLASS_NAME::FIELD_2D_MOB_NODE, tml::INIFileReadDesc()) == nullptr) {
			return (-1);
		}

		this->mob_layout_node->AddChildNode(this->mob_node);
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
