/**
 * @file
 * @brief Materialコードファイル
 */


#include "Material.h"
#include "GraphicManager.h"


/**
 * @brief コンストラクタ
 */
tml::MaterialDesc::MaterialDesc() :
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
tml::MaterialDesc::~MaterialDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::MaterialDesc::Init(void)
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

	tml::GraphicResourceDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::Material::Material() :
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
tml::Material::~Material()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::Material::Release(void)
{
	tml::GraphicResource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::Material::Init(void)
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

	tml::GraphicResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::Material::Create(tml::MaterialDesc &desc)
{
	this->Init();

	if (tml::GraphicResource::Create(desc) < 0) {
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
