/**
 * @file
 * @brief Field2DBulletNode�R�[�h�t�@�C��
 */


#include "Field2DBulletNode.h"
#include "../../lib/tml/math/MathUtil.h"
#include "../../lib/tml/graphic/Texture.h"
#include "../../lib/tml/graphic/Sampler.h"
#include "../../lib/tml/graphic/FigureModel2D.h"
#include "../constant/ConstantUtil_FILE_PATH.h"
#include "../graphic/Manager.h"
#include "Manager.h"
#include "Field2DNode.h"


/**
 * @brief �R���X�g���N�^
 */
cpp_base::scene::Field2DBulletNodeDesc::Field2DBulletNodeDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::scene::Field2DBulletNodeDesc::~Field2DBulletNodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::scene::Field2DBulletNodeDesc::Init(void)
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
INT cpp_base::scene::Field2DBulletNodeDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (cpp_base::scene::NodeDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Field2DBulletNode Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"FIELD_2D_MOB_NODE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief �R���X�g���N�^
 */
cpp_base::scene::Field2DBulletNode::Field2DBulletNode() :
	desc_(nullptr),
	field_node_(nullptr),
	update_time_(0.0)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::scene::Field2DBulletNode::~Field2DBulletNode()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void cpp_base::scene::Field2DBulletNode::Release(void)
{
	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::scene::Field2DBulletNode::Init(void)
{
	this->Release();

	this->field_node_ = nullptr;
	this->update_time_ = tml::TIME_REAL(0.0);

	this->model.reset();

	cpp_base::scene::Node::Init();

	return;
}


/**
 * @brief OnCreate�֐�
 * @return result (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::Field2DBulletNode::OnCreate(void)
{
	if (cpp_base::scene::Node::OnCreate() < 0) {
		return (-1);
	}

	{// Model Create
		tml::graphic::FigureModel2DDesc model_desc;

		model_desc.SetManager(this->GetGraphicManager());
		model_desc.diffuse_texture_desc = tml::make_shared<tml::graphic::TextureDesc>(1U);
		model_desc.diffuse_texture_desc->SetManager(this->GetGraphicManager());
		model_desc.diffuse_texture_desc->atlas_texture = this->GetGraphicManager()->common2.common_atlas->GetTexture();
		model_desc.diffuse_texture_desc->atlas_rect = (*this->GetGraphicManager()->common2.common_atlas->GetRect(L"bullet_2d_img.png"));
		model_desc.draw_priority = 4;

		if (this->GetGraphicManager()->GetResource<tml::graphic::FigureModel2D>(this->model, model_desc) == nullptr) {
			return (-1);
		}
	}

	return (0);
}


/**
 * @brief OnCreateDeferred�֐�
 * @return result (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::Field2DBulletNode::OnCreateDeferred(void)
{
	if (cpp_base::scene::Node::OnCreateDeferred() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnStart�֐�
 * @return result (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::Field2DBulletNode::OnStart(void)
{
	this->field_node_ = dynamic_cast<cpp_base::scene::Field2DNode *>(this->GetParentNode(L"field"));

	if (this->field_node_ == nullptr) {
		return (-1);
	}

	this->update_time_ = tml::TIME_REAL(0.0);

	this->SetModel(0U, this->model);

	return (0);
}


/**
 * @brief OnEnd�֐�
 */
void cpp_base::scene::Field2DBulletNode::OnEnd(void)
{
	return;
}


/**
 * @brief OnUpdate�֐�
 */
void cpp_base::scene::Field2DBulletNode::OnUpdate(void)
{
	this->update_time_ += this->GetManager()->GetFrameRate().GetElapsedTime();

	if (this->update_time_.count() >= 3.0) {
		this->RemoveChildNodeFromParentNode();
	}

	this->transform_2d.Move(this->transform_2d.GetYAxisVector(), 5.0f);

	return;
}


/**
 * @brief OnSetDesc�֐�
 * @param desc (desc)
 */
void cpp_base::scene::Field2DBulletNode::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const cpp_base::scene::Field2DBulletNodeDesc *>(desc);

	cpp_base::scene::Node::OnSetDesc(this->desc_);

	return;
}
