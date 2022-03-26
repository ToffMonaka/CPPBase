/**
 * @file
 * @brief Field2DGroundNodeコードファイル
 */


#include "Field2DGroundNode.h"
#include "../../lib/tml/graphic/Texture.h"
#include "../../lib/tml/graphic/Sampler.h"
#include "../../lib/tml/graphic/GroundModel2D.h"
#include "../constant/ConstantUtil_FILE_PATH.h"
#include "../graphic/Manager.h"
#include "Manager.h"
#include "Field2DNode.h"


/**
 * @brief コンストラクタ
 */
cpp_base::scene::Field2DGroundNodeDesc::Field2DGroundNodeDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::Field2DGroundNodeDesc::~Field2DGroundNodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::Field2DGroundNodeDesc::Init(void)
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
INT cpp_base::scene::Field2DGroundNodeDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (cpp_base::scene::NodeDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Field2DGroundNode Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"FIELD_2D_GROUND_NODE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
cpp_base::scene::Field2DGroundNode::Field2DGroundNode() :
	desc_(nullptr),
	field_node_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::Field2DGroundNode::~Field2DGroundNode()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::scene::Field2DGroundNode::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::Field2DGroundNode::Init(void)
{
	this->Release();

	this->field_node_ = nullptr;

	this->model.reset();

	cpp_base::scene::Node::Init();

	return;
}


/**
 * @brief OnCreate関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Field2DGroundNode::OnCreate(void)
{
	if (cpp_base::scene::Node::OnCreate() < 0) {
		return (-1);
	}

	{// Model Create
		tml::graphic::GroundModel2DDesc model_desc;

		model_desc.SetManager(this->GetGraphicManager());
		model_desc.map_desc = tml::make_shared<tml::graphic::MapDesc>(1U);
		model_desc.map_desc->SetManager(this->GetGraphicManager());
		model_desc.map_desc->map_file_read_desc.data.file_path = cpp_base::ConstantUtil::FILE_PATH::GROUND_2D_MAP;
		model_desc.map_desc->map_directory_path = L"res";
		model_desc.draw_priority = 0;

		if (this->GetGraphicManager()->GetResource<tml::graphic::GroundModel2D>(this->model, model_desc) == nullptr) {
			return (-1);
		}
	}

	return (0);
}


/**
 * @brief OnCreateDeferred関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Field2DGroundNode::OnCreateDeferred(void)
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
INT cpp_base::scene::Field2DGroundNode::OnStart(void)
{
	this->field_node_ = dynamic_cast<cpp_base::scene::Field2DNode *>(this->GetParentNode(L"field"));

	if (this->field_node_ == nullptr) {
		return (-1);
	}

	this->SetModel(0U, this->model);

	return (0);
}


/**
 * @brief OnEnd関数
 */
void cpp_base::scene::Field2DGroundNode::OnEnd(void)
{
	return;
}


/**
 * @brief OnUpdate関数
 */
void cpp_base::scene::Field2DGroundNode::OnUpdate(void)
{
	return;
}


/**
 * @brief OnSetDesc関数
 * @param desc (desc)
 */
void cpp_base::scene::Field2DGroundNode::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const cpp_base::scene::Field2DGroundNodeDesc *>(desc);

	cpp_base::scene::Node::OnSetDesc(this->desc_);

	return;
}
