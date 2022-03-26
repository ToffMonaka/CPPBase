/**
 * @file
 * @brief BGMSoundコードファイル
 */


#include "BGMSound.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::sound::BGMSoundDesc::BGMSoundDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::sound::BGMSoundDesc::~BGMSoundDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::sound::BGMSoundDesc::Init(void)
{
	this->Release();

	tml::sound::SoundDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::sound::BGMSoundDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::sound::SoundDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// BGMSound Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"BGM_SOUND");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::sound::BGMSound::BGMSound() :
	desc_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::sound::BGMSound::~BGMSound()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::sound::BGMSound::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::sound::BGMSound::Init(void)
{
	this->Release();

	tml::sound::Sound::Init();

	return;
}


/**
 * @brief OnCreate関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::sound::BGMSound::OnCreate(void)
{
	if (tml::sound::Sound::OnCreate() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnCreateDeferred関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::sound::BGMSound::OnCreateDeferred(void)
{
	if (tml::sound::Sound::OnCreateDeferred() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnSetDesc関数
 * @param desc (desc)
 */
void tml::sound::BGMSound::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::sound::BGMSoundDesc *>(desc);

	tml::sound::Sound::OnSetDesc(this->desc_);

	return;
}
