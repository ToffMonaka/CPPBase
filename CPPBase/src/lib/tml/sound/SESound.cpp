/**
 * @file
 * @brief SESound�R�[�h�t�@�C��
 */


#include "SESound.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::sound::SESoundDesc::SESoundDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::sound::SESoundDesc::~SESoundDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::sound::SESoundDesc::Init(void)
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
 * @brief �R���X�g���N�^
 */
tml::sound::SESound::SESound()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::sound::SESound::~SESound()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::sound::SESound::Init(void)
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
INT tml::sound::SESound::Create(const tml::sound::SESoundDesc &desc)
{
	this->Init();

	if (tml::sound::Sound::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
