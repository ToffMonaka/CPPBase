/**
 * @file
 * @brief BlendStateコードファイル
 */


#include "BlendState.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::BlendStateDesc::BlendStateDesc() :
	blend_state_desc(CD3D11_DEFAULT()),
	factor_array{}
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::BlendStateDesc::~BlendStateDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::BlendStateDesc::Init(void)
{
	this->blend_state_desc = CD3D11_BLEND_DESC(CD3D11_DEFAULT());
	this->factor_array.fill(0.0f);

	tml::graphic::ResourceDesc::Init();

	return;
}


/**
 * @brief SetBlendStateDesc関数
 * @param type (type)
 * @param a_type (alpha_type)
 * @param rt_cnt (render_target_count)
 */
void tml::graphic::BlendStateDesc::SetBlendStateDesc(const tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE type, const tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE a_type, const UINT rt_cnt)
{
	auto &desc = this->blend_state_desc;

	desc = CD3D11_BLEND_DESC(CD3D11_DEFAULT());

	if (type == tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::DEFAULT) {
		return;
	}

	UINT tmp_rt_cnt = 0U;

	if ((rt_cnt <= 0U)
	|| (rt_cnt >= tml::ConstantUtil::GRAPHIC::RENDER_TARGET_LIMIT)) {
		tmp_rt_cnt = 1U;

		desc.IndependentBlendEnable = false;
	} else {
		tmp_rt_cnt = rt_cnt;

		desc.IndependentBlendEnable = true;
	}

	switch (type) {
	case tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::ALIGNMENT: {
		for (UINT rt_i = 0U; rt_i < tmp_rt_cnt; ++rt_i) {
			auto &rt_desc = desc.RenderTarget[rt_i];

			rt_desc.BlendEnable = true;
			rt_desc.SrcBlend = D3D11_BLEND_SRC_ALPHA;
			rt_desc.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			rt_desc.BlendOp = D3D11_BLEND_OP_ADD;
			rt_desc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		}

		break;
	}
	case tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::ADD: {
		for (UINT rt_i = 0U; rt_i < tmp_rt_cnt; ++rt_i) {
			auto &rt_desc = desc.RenderTarget[rt_i];

			rt_desc.BlendEnable = true;
			rt_desc.SrcBlend = D3D11_BLEND_SRC_ALPHA;
			rt_desc.DestBlend = D3D11_BLEND_ONE;
			rt_desc.BlendOp = D3D11_BLEND_OP_ADD;
			rt_desc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		}

		break;
	}
	case tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::SUB: {
		for (UINT rt_i = 0U; rt_i < tmp_rt_cnt; ++rt_i) {
			auto &rt_desc = desc.RenderTarget[rt_i];

			rt_desc.BlendEnable = true;
			rt_desc.SrcBlend = D3D11_BLEND_SRC_ALPHA;
			rt_desc.DestBlend = D3D11_BLEND_ONE;
			rt_desc.BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
			rt_desc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		}

		break;
	}
	case tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::MUL: {
		for (UINT rt_i = 0U; rt_i < tmp_rt_cnt; ++rt_i) {
			auto &rt_desc = desc.RenderTarget[rt_i];

			rt_desc.BlendEnable = true;
			rt_desc.SrcBlend = D3D11_BLEND_ZERO;
			rt_desc.DestBlend = D3D11_BLEND_SRC_COLOR;
			rt_desc.BlendOp = D3D11_BLEND_OP_ADD;
			rt_desc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		}

		break;
	}
	case tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::REVERSE: {
		for (UINT rt_i = 0U; rt_i < tmp_rt_cnt; ++rt_i) {
			auto &rt_desc = desc.RenderTarget[rt_i];

			rt_desc.BlendEnable = true;
			rt_desc.SrcBlend = D3D11_BLEND_INV_DEST_COLOR;
			rt_desc.DestBlend = D3D11_BLEND_ZERO;
			rt_desc.BlendOp = D3D11_BLEND_OP_ADD;
			rt_desc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		}

		break;
	}
	case tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::TOTAL: {
		for (UINT rt_i = 0U; rt_i < tmp_rt_cnt; ++rt_i) {
			auto &rt_desc = desc.RenderTarget[rt_i];

			rt_desc.BlendEnable = true;
			rt_desc.SrcBlend = D3D11_BLEND_ONE;
			rt_desc.DestBlend = D3D11_BLEND_ONE;
			rt_desc.BlendOp = D3D11_BLEND_OP_ADD;
			rt_desc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		}

		break;
	}
	}

	switch (a_type) {
	case tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::DEFAULT: {
		for (UINT rt_i = 0U; rt_i < tmp_rt_cnt; ++rt_i) {
			auto &rt_desc = desc.RenderTarget[rt_i];

			rt_desc.SrcBlendAlpha = D3D11_BLEND_ONE;
			rt_desc.DestBlendAlpha = D3D11_BLEND_ZERO;
			rt_desc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
		}

		break;
	}
	case tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::SRC: {
		for (UINT rt_i = 0U; rt_i < tmp_rt_cnt; ++rt_i) {
			auto &rt_desc = desc.RenderTarget[rt_i];

			rt_desc.SrcBlendAlpha = D3D11_BLEND_ONE;
			rt_desc.DestBlendAlpha = D3D11_BLEND_ZERO;
			rt_desc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
		}

		break;
	}
	case tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::DST: {
		for (UINT rt_i = 0U; rt_i < tmp_rt_cnt; ++rt_i) {
			auto &rt_desc = desc.RenderTarget[rt_i];

			rt_desc.SrcBlendAlpha = D3D11_BLEND_ZERO;
			rt_desc.DestBlendAlpha = D3D11_BLEND_ONE;
			rt_desc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
		}

		break;
	}
	case tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::TOTAL: {
		for (UINT rt_i = 0U; rt_i < tmp_rt_cnt; ++rt_i) {
			auto &rt_desc = desc.RenderTarget[rt_i];

			rt_desc.SrcBlendAlpha = D3D11_BLEND_ONE;
			rt_desc.DestBlendAlpha = D3D11_BLEND_ONE;
			rt_desc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
		}

		break;
	}
	}

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::BlendState::BlendState() :
	bs_(nullptr),
	factor_ary_{}
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::BlendState::~BlendState()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::BlendState::Release(void)
{
	if (this->bs_ != nullptr) {
		this->bs_->Release();

		this->bs_ = nullptr;
	}

	tml::graphic::Resource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::BlendState::Init(void)
{
	this->Release();

	this->factor_ary_.fill(0.0f);

	tml::graphic::Resource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::BlendState::Create(tml::graphic::BlendStateDesc &desc)
{
	this->Init();

	if (tml::graphic::Resource::Create(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::BLEND_STATE, desc) < 0) {
		this->Init();

		return (-1);
	}

	if (FAILED(this->GetManager()->GetDevice()->CreateBlendState(&desc.blend_state_desc, &this->bs_))) {
		this->Init();

		return (-1);
	}

	this->factor_ary_ = desc.factor_array;

	return (0);
}
