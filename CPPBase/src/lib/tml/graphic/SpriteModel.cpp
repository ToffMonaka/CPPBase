/**
 * @file
 * @brief SpriteModelコードファイル
 */


#include "SpriteModel.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::SpriteModelLayer::SpriteModelLayer()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::SpriteModelLayer::~SpriteModelLayer()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::SpriteModelLayer::Release(void)
{
	tml::graphic::ModelLayer::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::SpriteModelLayer::Init(void)
{
	this->Release();

	tml::graphic::ModelLayer::Init();

	return;
}


/**
 * @brief Create関数
 * @param mgr (manager)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::SpriteModelLayer::Create(tml::graphic::Manager *mgr)
{
	this->Init();

	if (tml::graphic::ModelLayer::Create(mgr) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::SpriteModelStage::SpriteModelStage()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::SpriteModelStage::~SpriteModelStage()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::SpriteModelStage::Release(void)
{
	tml::graphic::ModelStage::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::SpriteModelStage::Init(void)
{
	this->Release();

	tml::graphic::ModelStage::Init();

	return;
}


/**
 * @brief Create関数
 * @param mgr (manager)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::SpriteModelStage::Create(tml::graphic::Manager *mgr)
{
	this->Init();

	if (tml::graphic::ModelStage::Create(mgr) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::SpriteModelDesc::SpriteModelDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::SpriteModelDesc::~SpriteModelDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::SpriteModelDesc::Init(void)
{
	tml::graphic::ModelDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::SpriteModelDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::graphic::ModelDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// SpriteModel Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"SPRITE_MODEL");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::SpriteModel::SpriteModel()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::SpriteModel::~SpriteModel()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::SpriteModel::Release(void)
{
	tml::graphic::Model::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::SpriteModel::Init(void)
{
	this->Release();

	tml::graphic::Model::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @param pos (position)<br>
 * nullptr=指定無し
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::SpriteModel::Create(const tml::graphic::SpriteModelDesc &desc, tml::shared_ptr<tml::XMPosition> *pos)
{
	this->Init();

	if (tml::graphic::Model::Create(desc, tml::ConstantUtil::GRAPHIC::MODEL_TYPE::SPRITE, pos) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
