/**
 * @file
 * @brief BGMSound�R�[�h�t�@�C��
 */


#include "BGMSound.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::sound::BGMSoundDesc::BGMSoundDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::sound::BGMSoundDesc::~BGMSoundDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::sound::BGMSoundDesc::Init(void)
{
	this->Release();

	tml::sound::SoundDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param ini_file (ini_file)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::sound::BGMSoundDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::sound::SoundDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// BGMSound Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"BGM_SOUND");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief �R���X�g���N�^
 */
tml::sound::BGMSound::BGMSound()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::sound::BGMSound::~BGMSound()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::sound::BGMSound::Init(void)
{
	this->Release();

	tml::sound::Sound::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::sound::BGMSound::Create(const tml::sound::BGMSoundDesc &desc)
{
	this->Init();

	if (tml::sound::Sound::Create(desc, tml::ConstantUtil::SOUND::SOUND_TYPE::BGM) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
