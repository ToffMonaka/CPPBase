/**
 * @file
 * @brief ModelLayerShaderStructuredBufferコードファイル
 */


#include "ModelLayerShaderStructuredBuffer.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::ModelLayerShaderStructuredBufferDesc::ModelLayerShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ModelLayerShaderStructuredBufferDesc::~ModelLayerShaderStructuredBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ModelLayerShaderStructuredBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::ModelLayerShaderStructuredBuffer::ModelLayerShaderStructuredBuffer() :
	element_ary_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ModelLayerShaderStructuredBuffer::~ModelLayerShaderStructuredBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::ModelLayerShaderStructuredBuffer::Release(void)
{
	tml::MemoryUtil::Release(&this->element_ary_);

	tml::graphic::ShaderStructuredBuffer::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ModelLayerShaderStructuredBuffer::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBuffer::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::ModelLayerShaderStructuredBuffer::Create(const tml::graphic::ModelLayerShaderStructuredBufferDesc &desc)
{
	this->Init();

	if (tml::graphic::ShaderStructuredBuffer::Create(desc, sizeof(tml::graphic::ModelLayerShaderStructuredBuffer::ELEMENT)) < 0) {
		this->Init();

		return (-1);
	}

	this->element_ary_ = tml::MemoryUtil::Get<tml::graphic::ModelLayerShaderStructuredBuffer::ELEMENT>(desc.element_limit);

	return (0);
}


/**
 * @brief 要素セット関数
 * @param index …インデックス
 * @param light …ライト
 * @param draw_shadow_flg …描画シャドウフラグ(false=描画シャドウ無し,true=描画シャドウ有り)
 * @param v_mat …ビュー行列
 */
/*
void tml::graphic::ModelLayerShaderStructuredBuffer::SetElement(const UINT index, tml::graphic::ModelLayer *light, const bool draw_shadow_flg, const XMMATRIX &v_mat)
{
	auto element = this->GetElement(index);

	if (element == NULLP) { //要素無しの時
		return;
	}

	element->type = static_cast<UINT>(light->GetType());
	element->flg = light->GetFlag();
	XMStoreFloat3(&element->v_pos, XMVector3Transform(XMLoadFloat3(&light->GetPosition().Get().GetPosition()), v_mat));
	XMStoreFloat3(&element->v_dir_vec, XMVector3TransformNormal(XMLoadFloat3(&light->GetPosition().Get().GetZAxisVector()), v_mat));
	element->col = light->GetColor();
	element->mul_val = light->GetMulValue();
	element->add_val = light->GetAddValue();
	element->exponent = light->GetExponent();
	element->cut_val = light->GetCutValue();
	element->soft_val = light->GetSoftValue();
	element->atten_val = light->GetAttenuateValue();
	element->rng = light->GetRange();
	element->inv_rng = (light->GetRange() > 0.0f) ? 1.0f / light->GetRange() : 0.0f;
	element->rng_exponent = light->GetRangeExponent();
	element->draw_shadow_flg = draw_shadow_flg;

	return;
}
*/
