/**
 * @file
 * @brief Canvasコードファイル
 */


#include "Canvas.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::CanvasDesc::CanvasDesc()
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
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
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
 * @brief コンストラクタ
 */
tml::graphic::Canvas::Canvas() :
	type_(tml::ConstantUtil::GRAPHIC::CANVAS_TYPE::NONE)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Canvas::~Canvas()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::Canvas::Release(void)
{
	tml::graphic::ManagerResource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Canvas::Init(void)
{
	this->type_ = tml::ConstantUtil::GRAPHIC::CANVAS_TYPE::NONE;

	tml::graphic::ManagerResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @param type (type)
 * @return res (result)<br>
 * 0未満=失敗
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
