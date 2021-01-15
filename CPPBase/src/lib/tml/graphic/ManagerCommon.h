/**
 * @file
 * @brief ManagerCommonヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../memory/MemoryUtil.h"
#include "Resource.h"


namespace tml {
namespace graphic {
class RasterizerState;
class BlendState;
class DepthState;
}
}


namespace tml {
namespace graphic {
/**
 * @brief ManagerCommonクラス
 */
class ManagerCommon
{
public: ManagerCommon(const tml::graphic::ManagerCommon &) = delete;
public: tml::graphic::ManagerCommon &operator =(const tml::graphic::ManagerCommon &) = delete;

public:
	tml::shared_ptr<tml::graphic::RasterizerState> default_rasterizer_state;
	tml::shared_ptr<tml::graphic::RasterizerState> wireframe_rasterizer_state;
	tml::shared_ptr<tml::graphic::RasterizerState> front_culling_rasterizer_state;
	tml::shared_ptr<tml::graphic::RasterizerState> back_culling_rasterizer_state;
	tml::shared_ptr<tml::graphic::BlendState> default_blend_state;
	std::array<tml::shared_ptr<tml::graphic::BlendState>, tml::ConstantUtil::GRAPHIC::RENDER_TARGET_LIMIT> alignment_blend_state_array;
	std::array<tml::shared_ptr<tml::graphic::BlendState>, tml::ConstantUtil::GRAPHIC::RENDER_TARGET_LIMIT> add_blend_state_array;
	std::array<tml::shared_ptr<tml::graphic::BlendState>, tml::ConstantUtil::GRAPHIC::RENDER_TARGET_LIMIT> sub_blend_state_array;
	std::array<tml::shared_ptr<tml::graphic::BlendState>, tml::ConstantUtil::GRAPHIC::RENDER_TARGET_LIMIT> mul_blend_state_array;
	std::array<tml::shared_ptr<tml::graphic::BlendState>, tml::ConstantUtil::GRAPHIC::RENDER_TARGET_LIMIT> reverse_blend_state_array;
	std::array<tml::shared_ptr<tml::graphic::BlendState>, tml::ConstantUtil::GRAPHIC::RENDER_TARGET_LIMIT> total_blend_state_array;
	tml::shared_ptr<tml::graphic::DepthState> default_depth_state;
	tml::shared_ptr<tml::graphic::DepthState> reference_depth_state;

public:
	ManagerCommon();
	virtual ~ManagerCommon();

	virtual void Init(void);
	INT Create(tml::graphic::Manager *);
};
}
}
