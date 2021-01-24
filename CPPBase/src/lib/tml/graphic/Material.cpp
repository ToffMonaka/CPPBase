/**
 * @file
 * @brief Materialコードファイル
 */


#include "Material.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::MaterialDesc::MaterialDesc() :
	diffuse_color(0.0f),
	diffuse_mul_value(0.0f),
	transparent_mul_value(0.0f),
	burn_mul_value(0.0f),
	emissive_mul_value(0.0f),
	bloom_mul_value(0.0f),
	specular_mul_value(0.0f),
	specular_exp_value(1.0f),
	rim_mul_value(0.0f),
	rim_exp_value(1.0f),
	light_flag(false),
	fog_flag(false)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::MaterialDesc::~MaterialDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::MaterialDesc::Init(void)
{
	this->diffuse_color = 0.0f;
	this->diffuse_mul_value = 0.0f;
	this->transparent_mul_value = 0.0f;
	this->burn_mul_value = 0.0f;
	this->emissive_mul_value = 0.0f;
	this->bloom_mul_value = 0.0f;
	this->specular_mul_value = 0.0f;
	this->specular_exp_value = 1.0f;
	this->rim_mul_value = 0.0f;
	this->rim_exp_value = 1.0f;
	this->light_flag = false;
	this->fog_flag = false;

	tml::graphic::ResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::MaterialDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::graphic::ResourceDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Material Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"MATERIAL");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Material::Material() :
	diffuse_col_(0.0f),
	diffuse_mul_val_(0.0f),
	transparent_mul_val_(0.0f),
	burn_mul_val_(0.0f),
	emissive_mul_val_(0.0f),
	bloom_mul_val_(0.0f),
	specular_mul_val_(0.0f),
	specular_exp_val_(1.0f),
	rim_mul_val_(0.0f),
	rim_exp_val_(1.0f),
	light_flg_(false),
	fog_flg_(false)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Material::~Material()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::Material::Release(void)
{
	tml::graphic::Resource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Material::Init(void)
{
	this->Release();

	this->diffuse_col_ = 0.0f;
	this->diffuse_mul_val_ = 0.0f;
	this->transparent_mul_val_ = 0.0f;
	this->burn_mul_val_ = 0.0f;
	this->emissive_mul_val_ = 0.0f;
	this->bloom_mul_val_ = 0.0f;
	this->specular_mul_val_ = 0.0f;
	this->specular_exp_val_ = 1.0f;
	this->rim_mul_val_ = 0.0f;
	this->rim_exp_val_ = 1.0f;
	this->light_flg_ = false;
	this->fog_flg_ = false;

	tml::graphic::Resource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Material::Create(const tml::graphic::MaterialDesc &desc)
{
	this->Init();

	if (tml::graphic::Resource::Create(desc, tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::MATERIAL) < 0) {
		this->Init();

		return (-1);
	}

	this->diffuse_col_ = desc.diffuse_color;
	this->diffuse_mul_val_ = desc.diffuse_mul_value;
	this->transparent_mul_val_ = desc.transparent_mul_value;
	this->burn_mul_val_ = desc.burn_mul_value;
	this->emissive_mul_val_ = desc.emissive_mul_value;
	this->bloom_mul_val_ = desc.bloom_mul_value;
	this->specular_mul_val_ = desc.specular_mul_value;
	this->specular_exp_val_ = desc.specular_exp_value;
	this->rim_mul_val_ = desc.rim_mul_value;
	this->rim_exp_val_ = desc.rim_exp_value;
	this->light_flg_ = desc.light_flag;
	this->fog_flg_ = desc.fog_flag;

	return (0);
}
