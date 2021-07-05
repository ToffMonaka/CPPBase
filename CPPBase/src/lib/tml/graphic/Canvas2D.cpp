/**
 * @file
 * @brief Canvas2D�R�[�h�t�@�C��
 */


#include "Canvas2D.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Canvas2DDesc::Canvas2DDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Canvas2DDesc::~Canvas2DDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Canvas2DDesc::Init(void)
{
	this->Release();

	tml::graphic::CanvasDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::Canvas2DDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::graphic::CanvasDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Canvas2D Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"CANVAS_2D");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Canvas2D::Canvas2D()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Canvas2D::~Canvas2D()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::graphic::Canvas2D::Release(void)
{
	tml::graphic::Canvas::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Canvas2D::Init(void)
{
	this->Release();

	tml::graphic::Canvas::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::Canvas2D::Create(const tml::graphic::Canvas2DDesc &desc)
{
	this->Init();

	if (tml::graphic::Canvas::Create(desc, tml::ConstantUtil::GRAPHIC::CANVAS_TYPE::_2D) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
