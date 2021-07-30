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
 * @param ini_file (ini_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::sound::SESoundDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::sound::SoundDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// SESound Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"SE_SOUND");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::sound::SESound::SESound()
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
 * @brief Init関数
 */
void tml::sound::SESound::Init(void)
{
	this->Release();

	tml::sound::Sound::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::sound::SESound::Create(const tml::sound::SESoundDesc &desc)
{
	this->Init();

	if (tml::sound::Sound::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
