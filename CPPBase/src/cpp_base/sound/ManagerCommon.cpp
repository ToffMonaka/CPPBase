/**
 * @file
 * @brief ManagerCommonコードファイル
 */


#include "ManagerCommon.h"
#include "../../lib/tml/sound/BGMSound.h"
#include "../../lib/tml/sound/SESound.h"
#include "../constant/ConstantUtil_FILE_PATH.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
cpp_base::sound::ManagerCommon::ManagerCommon() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::sound::ManagerCommon::~ManagerCommon()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::sound::ManagerCommon::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	this->title_bgm_sound.reset();
	this->select_bgm_sound.reset();
	this->start_se_sound.reset();

	return;
}


/**
 * @brief Create関数
 * @param mgr (manager)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::sound::ManagerCommon::Create(cpp_base::sound::Manager *mgr)
{
	if (mgr == nullptr) {
		this->Init();

		return (-1);
	}

	this->Init();

	this->mgr_ = mgr;

	{// TitleBGMSound Create
		tml::sound::BGMSoundDesc sound_desc;

		sound_desc.SetManager(this->mgr_);
		sound_desc.deferred_create_flag = true;
		sound_desc.sound_file_read_desc.data.file_path = cpp_base::ConstantUtil::FILE_PATH::TITLE_BGM_SOUND;

		if (this->mgr_->GetResource<tml::sound::BGMSound>(this->title_bgm_sound, sound_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// SelectBGMSound Create
		tml::sound::BGMSoundDesc sound_desc;

		sound_desc.SetManager(this->mgr_);
		sound_desc.deferred_create_flag = true;
		sound_desc.sound_file_read_desc.data.file_path = cpp_base::ConstantUtil::FILE_PATH::SELECT_BGM_SOUND;

		if (this->mgr_->GetResource<tml::sound::BGMSound>(this->select_bgm_sound, sound_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	{// StartSESound Create
		tml::sound::SESoundDesc sound_desc;

		sound_desc.SetManager(this->mgr_);
		sound_desc.deferred_create_flag = true;
		sound_desc.sound_file_read_desc.data.file_path = cpp_base::ConstantUtil::FILE_PATH::START_SE_SOUND;

		if (this->mgr_->GetResource<tml::sound::SESound>(this->start_se_sound, sound_desc) == nullptr) {
			this->Init();

			return (-1);
		}
	}

	return (0);
}
