/**
 * @file
 * @brief ManagerCommonコードファイル
 */


#include "ManagerCommon.h"
#include "../../lib/tml/graphic/Texture.h"
#include "../../lib/tml/graphic/Sampler.h"
#include "../../lib/tml/graphic/Font.h"
#include "../../lib/tml/graphic/Atlas.h"
#include "../constant/ConstantUtil_FILE_PATH.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
cpp_base::graphic::ManagerCommon::ManagerCommon() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::graphic::ManagerCommon::~ManagerCommon()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::graphic::ManagerCommon::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	this->background_texture.reset();
	this->empty_background_texture.reset();
	this->common_font.reset();
	this->common_atlas.reset();

	return;
}


/**
 * @brief Create関数
 * @param mgr (manager)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::graphic::ManagerCommon::Create(cpp_base::graphic::Manager *mgr)
{
	if (mgr == nullptr) {
		this->Init();

		return (-1);
	}

	this->Init();

	this->mgr_ = mgr;

	{// BackgroundTexture Create
		tml::graphic::TextureDesc tex_desc;

		tex_desc.SetManager(this->mgr_);
		tex_desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR);
		tex_desc.image_file_read_desc_container[0].data.file_path = cpp_base::ConstantUtil::FILE_PATH::BACKGROUND_IMAGE;

		if (this->mgr_->GetResource<tml::graphic::Texture>(this->background_texture, tex_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// EmptyBackgroundTexture Create
		tml::graphic::TextureDesc tex_desc;

		tex_desc.SetManager(this->mgr_);
		tex_desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR);
		tex_desc.image_file_read_desc_container[0].data.file_path = cpp_base::ConstantUtil::FILE_PATH::EMPTY_BACKGROUND_IMAGE;

		if (this->mgr_->GetResource<tml::graphic::Texture>(this->empty_background_texture, tex_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// CommonFont Create
		tml::graphic::FontDesc font_desc;

		font_desc.SetManager(this->mgr_);
		font_desc.SetFontDesc(tml::XMUINT2EX(0U, 16U), L"ＭＳ ゴシック");

		if (this->mgr_->GetResource<tml::graphic::Font>(this->common_font, font_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// CommonAtlas Create
		tml::graphic::AtlasDesc atlas_desc;

		atlas_desc.SetManager(this->mgr_);
		atlas_desc.atlas_file_read_desc.data.file_path = cpp_base::ConstantUtil::FILE_PATH::COMMON_ATLAS;
		atlas_desc.atlas_directory_path = L"res";

		if (this->mgr_->GetResource<tml::graphic::Atlas>(this->common_atlas, atlas_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	return (0);
}
