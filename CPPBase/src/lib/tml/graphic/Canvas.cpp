/**
 * @file
 * @brief Canvasコードファイル
 */


#include "Canvas.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::CanvasDesc::CanvasDesc() :
	draw_priority(0)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::CanvasDesc::~CanvasDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::CanvasDesc::Init(void)
{
	this->Release();

	tml::graphic::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::CanvasDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::graphic::ManagerResourceDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Canvas Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"CANVAS");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Canvas::Canvas() :
	type_(tml::ConstantUtil::GRAPHIC::CANVAS_TYPE::NONE),
	dimension_type_(tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::NONE),
	draw_priority_(0),
	draw_set_flg_(false)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Canvas::~Canvas()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Canvas::Init(void)
{
	this->Release();

	this->type_ = tml::ConstantUtil::GRAPHIC::CANVAS_TYPE::NONE;
	this->dimension_type_ = tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::NONE;
	this->draw_priority_ = 0;
	this->draw_set_flg_ = false;

	tml::graphic::ManagerResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @param dimension_type (dimension_type)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Canvas::Create(const tml::graphic::CanvasDesc &desc, const tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE dimension_type)
{
	if (tml::graphic::ManagerResource::Create(desc) < 0) {
		return (-1);
	}

	this->type_ = static_cast<tml::ConstantUtil::GRAPHIC::CANVAS_TYPE>(this->GetResourceSubIndex());
	this->dimension_type_ = dimension_type;
	this->draw_priority_ = desc.draw_priority;

	return (0);
}


/**
 * @brief Draw関数
 */
void tml::graphic::Canvas::Draw(void)
{
	return;
}
