/**
 * @file
 * @brief ManagerCommonコードファイル
 */


#include "ManagerCommon.h"
#include "../../lib/tml/graphic/Texture.h"
#include "../../lib/tml/graphic/Sampler.h"
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

	this->bg_tex.reset();
	this->empty_bg_tex.reset();

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
		tml::graphic::TextureDesc desc;

		desc.SetManager(this->mgr_);
		desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR);
		desc.image_file_read_desc_container[0].data.file_path = cpp_base::ConstantUtil::FILE_PATH::BACKGROUND_IMAGE;

		if (this->mgr_->GetResource<tml::graphic::Texture>(this->bg_tex, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// EmptyBackgroundTexture Create
		tml::graphic::TextureDesc desc;

		desc.SetManager(this->mgr_);
		desc.SetTextureDesc(tml::ConstantUtil::GRAPHIC::TEXTURE_DESC_BIND_FLAG::SR);
		desc.image_file_read_desc_container[0].data.file_path = cpp_base::ConstantUtil::FILE_PATH::EMPTY_BACKGROUND_IMAGE;

		if (this->mgr_->GetResource<tml::graphic::Texture>(this->empty_bg_tex, desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	return (0);
}
