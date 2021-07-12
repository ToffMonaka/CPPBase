/**
 * @file
 * @brief Canvas�R�[�h�t�@�C��
 */


#include "Canvas.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::CanvasDesc::CanvasDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::CanvasDesc::~CanvasDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::CanvasDesc::Init(void)
{
	this->Release();

	tml::graphic::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::CanvasDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::graphic::ManagerResourceDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Canvas Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"CANVAS");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Canvas::Canvas() :
	type_(tml::ConstantUtil::GRAPHIC::CANVAS_TYPE::NONE),
	rt_tex_clear_flg_(false),
	dt_tex_clear_flg_(false),
	vp_x_(0.0f),
	vp_y_(0.0f),
	vp_w_(1.0f),
	vp_h_(1.0f)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Canvas::~Canvas()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Canvas::Init(void)
{
	this->type_ = tml::ConstantUtil::GRAPHIC::CANVAS_TYPE::NONE;
	this->rt_tex_.reset();
	this->rt_tex_clear_flg_ = false;
	this->dt_tex_.reset();
	this->dt_tex_clear_flg_ = false;
	this->vp_.Init();
	this->vp_x_ = 0.0f;
	this->vp_y_ = 0.0f;
	this->vp_w_ = 1.0f;
	this->vp_h_ = 1.0f;

	tml::graphic::ManagerResource::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @param type (type)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::Canvas::Create(const tml::graphic::CanvasDesc &desc, const tml::ConstantUtil::GRAPHIC::CANVAS_TYPE type)
{
	if (type == tml::ConstantUtil::GRAPHIC::CANVAS_TYPE::NONE) {
		return (-1);
	}

	if (tml::graphic::ManagerResource::Create(desc, tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::CANVAS, static_cast<UINT>(type)) < 0) {
		return (-1);
	}

	this->type_ = type;

	return (0);
}


/**
 * @brief SetRenderTargetTexture�֐�
 * @param rt_tex (render_target_texture)
 */
void tml::graphic::Canvas::SetRenderTargetTexture(const tml::shared_ptr<tml::graphic::Texture> &rt_tex)
{
	this->rt_tex_ = rt_tex;

	return;
}


/**
 * @brief SetDepthTargetTexture�֐�
 * @param dt_tex (depth_target_texture)
 */
void tml::graphic::Canvas::SetDepthTargetTexture(const tml::shared_ptr<tml::graphic::Texture> &dt_tex)
{
	this->dt_tex_ = dt_tex;

	return;
}


/**
 * @brief Draw�֐�
 */
void tml::graphic::Canvas::Draw(void)
{
	return;
}
