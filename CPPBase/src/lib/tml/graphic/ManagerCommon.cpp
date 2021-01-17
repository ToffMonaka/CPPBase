/**
 * @file
 * @brief ManagerCommonコードファイル
 */


#include "ManagerCommon.h"
#include "Manager.h"
#include "RasterizerState.h"
#include "BlendState.h"
#include "DepthState.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::ManagerCommon::ManagerCommon()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ManagerCommon::~ManagerCommon()
{
	return;
}


/**
 * @brief 初期化関数
 */
void tml::graphic::ManagerCommon::Init(void)
{
	this->default_rasterizer_state.reset();
	this->wireframe_rasterizer_state.reset();
	this->front_culling_rasterizer_state.reset();
	this->back_culling_rasterizer_state.reset();

	for (UINT rt_i = 0U; rt_i < 2U; ++rt_i) {
		this->default_blend_state_array[rt_i].reset();
		this->alignment_blend_state_array[rt_i].reset();
		this->add_blend_state_array[rt_i].reset();
		this->sub_blend_state_array[rt_i].reset();
		this->mul_blend_state_array[rt_i].reset();
		this->reverse_blend_state_array[rt_i].reset();
		this->total_blend_state_array[rt_i].reset();
	}

	this->default_depth_state.reset();
	this->reference_depth_state.reset();

	return;
}


/**
 * @brief Create関数
 * @param mgr (manager)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::ManagerCommon::Create(tml::graphic::Manager *mgr)
{
	this->Init();

	{// DefaultRasterizerState Create
		tml::graphic::RasterizerStateDesc desc;

		desc.SetRasterizerStateDesc(tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE::DEFAULT);

		this->default_rasterizer_state = mgr->GetResource<tml::graphic::RasterizerState>(desc);

		if (this->default_rasterizer_state == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// WireframeRasterizerState Create
		tml::graphic::RasterizerStateDesc desc;

		desc.SetRasterizerStateDesc(tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE::WIREFRAME);

		this->wireframe_rasterizer_state = mgr->GetResource<tml::graphic::RasterizerState>(desc);

		if (this->wireframe_rasterizer_state == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// FrontCullingRasterizerState Create
		tml::graphic::RasterizerStateDesc desc;

		desc.SetRasterizerStateDesc(tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE::FRONT_CULLING);

		this->front_culling_rasterizer_state = mgr->GetResource<tml::graphic::RasterizerState>(desc);

		if (this->front_culling_rasterizer_state == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// BackCullingRasterizerState Create
		tml::graphic::RasterizerStateDesc desc;

		desc.SetRasterizerStateDesc(tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE::BACK_CULLING);

		this->back_culling_rasterizer_state = mgr->GetResource<tml::graphic::RasterizerState>(desc);

		if (this->back_culling_rasterizer_state == nullptr) {
			this->Init();

			return (-1);
		}
	}

	for (UINT rt_i = 0U; rt_i < 2U; ++rt_i) {
		{// DefaultBlendState Create
			tml::graphic::BlendStateDesc desc;

			desc.SetBlendStateDesc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::DEFAULT, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::DEFAULT, rt_i);

			this->default_blend_state_array[rt_i] = mgr->GetResource<tml::graphic::BlendState>(desc);

			if (this->default_blend_state_array[rt_i] == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// AlignmentBlendState Create
			tml::graphic::BlendStateDesc desc;

			desc.SetBlendStateDesc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::ALIGNMENT, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::DST, rt_i);

			this->alignment_blend_state_array[rt_i] = mgr->GetResource<tml::graphic::BlendState>(desc);

			if (this->alignment_blend_state_array[rt_i] == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// AddBlendState Create
			tml::graphic::BlendStateDesc desc;

			desc.SetBlendStateDesc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::ADD, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::DST, rt_i);

			this->add_blend_state_array[rt_i] = mgr->GetResource<tml::graphic::BlendState>(desc);

			if (this->add_blend_state_array[rt_i] == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// SubBlendState Create
			tml::graphic::BlendStateDesc desc;

			desc.SetBlendStateDesc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::SUB, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::DST, rt_i);

			this->sub_blend_state_array[rt_i] = mgr->GetResource<tml::graphic::BlendState>(desc);

			if (this->sub_blend_state_array[rt_i] == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// MulBlendState Create
			tml::graphic::BlendStateDesc desc;

			desc.SetBlendStateDesc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::MUL, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::DST, rt_i);

			this->mul_blend_state_array[rt_i] = mgr->GetResource<tml::graphic::BlendState>(desc);

			if (this->mul_blend_state_array[rt_i] == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// ReverseBlendState Create
			tml::graphic::BlendStateDesc desc;

			desc.SetBlendStateDesc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::REVERSE, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::DST, rt_i);

			this->reverse_blend_state_array[rt_i] = mgr->GetResource<tml::graphic::BlendState>(desc);

			if (this->reverse_blend_state_array[rt_i] == nullptr) {
				this->Init();

				return (-1);
			}
		}

		{// TotalBlendState Create
			tml::graphic::BlendStateDesc desc;

			desc.SetBlendStateDesc(tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_TYPE::TOTAL, tml::ConstantUtil::GRAPHIC::BLEND_STATE_DESC_ALPHA_TYPE::TOTAL, rt_i);

			this->total_blend_state_array[rt_i] = mgr->GetResource<tml::graphic::BlendState>(desc);

			if (this->total_blend_state_array[rt_i] == nullptr) {
				this->Init();

				return (-1);
			}
		}
	}

	{// DefaultDepthState Create
		tml::graphic::DepthStateDesc desc;

		desc.SetDepthStateDesc(tml::ConstantUtil::GRAPHIC::DEPTH_STATE_DESC_TYPE::DEFAULT);

		this->default_depth_state = mgr->GetResource<tml::graphic::DepthState>(desc);

		if (this->default_depth_state == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// ReferenceDepthState Create
		tml::graphic::DepthStateDesc desc;

		desc.SetDepthStateDesc(tml::ConstantUtil::GRAPHIC::DEPTH_STATE_DESC_TYPE::REFERENCE);

		this->reference_depth_state = mgr->GetResource<tml::graphic::DepthState>(desc);

		if (this->reference_depth_state == nullptr) {
			this->Init();

			return (-1);
		}
	}

	return (0);
}
