/**
 * @file
 * @brief SESoundコードファイル
 */


#include "SESound.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::sound::SESoundDesc::SESoundDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::sound::SESoundDesc::~SESoundDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::sound::SESoundDesc::Init(void)
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
INT tml::sound::SESoundDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::sound::SoundDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// SESound Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"SE_SOUND");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::sound::SESound::SESound() :
	desc_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::sound::SESound::~SESound()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::sound::SESound::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::sound::SESound::Init(void)
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
INT tml::sound::SESound::OnCreate(void)
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
INT tml::sound::SESound::OnCreateDeferred(void)
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
void tml::sound::SESound::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::sound::SESoundDesc *>(desc);

	tml::sound::Sound::OnSetDesc(this->desc_);

	return;
}
