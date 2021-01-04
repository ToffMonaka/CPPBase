/**
 * @file
 * @brief Materialヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMath.h"
#include "GraphicResource.h"


namespace tml {
/**
 * @brief MaterialDescクラス
 */
class MaterialDesc : public tml::GraphicResourceDesc
{
public:
	tml::XMFLOAT3EX diffuse_color;
	FLOAT diffuse_mul_value;
	FLOAT transparent_mul_value;
	FLOAT burn_mul_value;
	FLOAT emissive_mul_value;
	FLOAT bloom_mul_value;
	FLOAT specular_mul_value;
	FLOAT specular_exp_value;
	FLOAT rim_mul_value;
	FLOAT rim_exp_value;
	bool light_flag;
	bool fog_flag;

public:
	MaterialDesc();
	virtual ~MaterialDesc();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief Materialクラス
 */
class Material : public tml::GraphicResource
{
public: Material(const tml::Material &) = delete;
public: tml::Material &operator =(const tml::Material &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	tml::XMFLOAT3EX diffuse_col_;
	FLOAT diffuse_mul_val_;
	FLOAT transparent_mul_val_;
	FLOAT burn_mul_val_;
	FLOAT emissive_mul_val_;
	FLOAT bloom_mul_val_;
	FLOAT specular_mul_val_;
	FLOAT specular_exp_val_;
	FLOAT rim_mul_val_;
	FLOAT rim_exp_val_;
	bool light_flg_;
	bool fog_flg_;

private:
	void Release(void);

public:
	Material();
	virtual ~Material();

	virtual void Init(void);
	INT Create(const tml::MaterialDesc &);

	const tml::XMFLOAT3EX &GetDiffuseColor(void) const;
	void SetDiffuseColor(const tml::XMFLOAT3EX &);
	FLOAT GetDiffuseMulValue(void) const;
	void SetDiffuseMulValue(const FLOAT);
	FLOAT GetTransparentMulValue(void) const;
	void SetTransparentMulValue(const FLOAT);
	FLOAT GetBurnMulValue(void) const;
	void SetBurnMulValue(const FLOAT);
	FLOAT GetEmissiveMulValue(void) const;
	void SetEmissiveMulValue(const FLOAT);
	FLOAT GetBloomMulValue(void) const;
	void SetBloomMulValue(const FLOAT);
	FLOAT GetSpecularMulValue(void) const;
	void SetSpecularMulValue(const FLOAT);
	FLOAT GetSpecularExpValue(void) const;
	void SetSpecularExpValue(const FLOAT);
	FLOAT GetRimMulValue(void) const;
	void SetRimMulValue(const FLOAT);
	FLOAT GetRimExpValue(void) const;
	void SetRimExpValue(const FLOAT);
};
}


/**
 * @brief GetDiffuseColor関数
 * @return diffuse_col (diffuse_color)
 */
inline const tml::XMFLOAT3EX &tml::Material::GetDiffuseColor(void) const
{
	return (this->diffuse_col_);
}


/**
 * @brief SetDiffuseColor関数
 * @param diffuse_col (diffuse_color)
 */
inline void tml::Material::SetDiffuseColor(const tml::XMFLOAT3EX &diffuse_col)
{
	this->diffuse_col_ = diffuse_col;

	return;
}


/**
 * @brief GetDiffuseMulValue関数
 * @return diffuse_mul_val (diffuse_mul_value)
 */
inline FLOAT tml::Material::GetDiffuseMulValue(void) const
{
	return (this->diffuse_mul_val_);
}


/**
 * @brief SetDiffuseMulValue関数
 * @param diffuse_mul_val (diffuse_mul_value)
 */
inline void tml::Material::SetDiffuseMulValue(const FLOAT diffuse_mul_val)
{
	this->diffuse_mul_val_ = diffuse_mul_val;
	
	return;
}


/**
 * @brief GetTransparentMulValue関数
 * @return transparent_mul_val (transparent_mul_value)
 */
inline FLOAT tml::Material::GetTransparentMulValue(void) const
{
	return (this->transparent_mul_val_);
}


/**
 * @brief SetTransparentMulValue関数
 * @param transparent_mul_val (transparent_mul_value)
 */
inline void tml::Material::SetTransparentMulValue(const FLOAT transparent_mul_val)
{
	this->transparent_mul_val_ = transparent_mul_val;
	
	return;
}


/**
 * @brief GetBurnMulValue関数
 * @return burn_mul_val (burn_mul_value)
 */
inline FLOAT tml::Material::GetBurnMulValue(void) const
{
	return (this->burn_mul_val_);
}


/**
 * @brief SetBurnMulValue関数
 * @param burn_mul_val (burn_mul_value)
 */
inline void tml::Material::SetBurnMulValue(const FLOAT burn_mul_val)
{
	this->burn_mul_val_ = burn_mul_val;
	
	return;
}


/**
 * @brief GetEmissiveMulValue関数
 * @return emissive_mul_val (emissive_mul_value)
 */
inline FLOAT tml::Material::GetEmissiveMulValue(void) const
{
	return (this->emissive_mul_val_);
}


/**
 * @brief SetEmissiveMulValue関数
 * @param emissive_mul_val (emissive_mul_value)
 */
inline void tml::Material::SetEmissiveMulValue(const FLOAT emissive_mul_val)
{
	this->emissive_mul_val_ = emissive_mul_val;
	
	return;
}


/**
 * @brief GetBloomMulValue関数
 * @return bloom_mul_val (bloom_mul_value)
 */
inline FLOAT tml::Material::GetBloomMulValue(void) const
{
	return (this->bloom_mul_val_);
}


/**
 * @brief SetBloomMulValue関数
 * @param bloom_mul_val (bloom_mul_value)
 */
inline void tml::Material::SetBloomMulValue(const FLOAT bloom_mul_val)
{
	this->bloom_mul_val_ = bloom_mul_val;
	
	return;
}


/**
 * @brief GetSpecularMulValue関数
 * @return specular_mul_val (specular_mul_value)
 */
inline FLOAT tml::Material::GetSpecularMulValue(void) const
{
	return (this->specular_mul_val_);
}


/**
 * @brief SetSpecularMulValue関数
 * @param specular_mul_val (specular_mul_value)
 */
inline void tml::Material::SetSpecularMulValue(const FLOAT specular_mul_val)
{
	this->specular_mul_val_ = specular_mul_val;
	
	return;
}


/**
 * @brief GetSpecularExpValue関数
 * @return specular_exp_val (specular_exp_value)
 */
inline FLOAT tml::Material::GetSpecularExpValue(void) const
{
	return (this->specular_exp_val_);
}


/**
 * @brief SetSpecularExpValue関数
 * @param specular_exp_val (specular_exp_value)
 */
inline void tml::Material::SetSpecularExpValue(const FLOAT specular_exp_val)
{
	this->specular_exp_val_ = specular_exp_val;
	
	return;
}


/**
 * @brief GetRimMulValue関数
 * @return rim_mul_val (rim_mul_value)
 */
inline FLOAT tml::Material::GetRimMulValue(void) const
{
	return (this->rim_mul_val_);
}


/**
 * @brief SetRimMulValue関数
 * @param rim_mul_val (rim_mul_value)
 */
inline void tml::Material::SetRimMulValue(const FLOAT rim_mul_val)
{
	this->rim_mul_val_ = rim_mul_val;
	
	return;
}


/**
 * @brief GetRimExpValue関数
 * @return rim_exp_val (rim_exp_value)
 */
inline FLOAT tml::Material::GetRimExpValue(void) const
{
	return (this->rim_exp_val_);
}


/**
 * @brief SetRimExpValue関数
 * @param rim_exp_val (rim_exp_value)
 */
inline void tml::Material::SetRimExpValue(const FLOAT rim_exp_val)
{
	this->rim_exp_val_ = rim_exp_val;
	
	return;
}
