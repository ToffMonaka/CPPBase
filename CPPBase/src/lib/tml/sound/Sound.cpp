/**
 * @file
 * @brief Sound�R�[�h�t�@�C��
 */


#include "Sound.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::sound::SoundDesc::SoundDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::sound::SoundDesc::~SoundDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::sound::SoundDesc::Init(void)
{
	this->Release();

	tml::sound::ResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::sound::SoundDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::sound::ResourceDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Sound Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"SOUND");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief �R���X�g���N�^
 */
tml::sound::Sound::Sound() :
	type_(tml::ConstantUtil::SOUND::SOUND_TYPE::NONE)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::sound::Sound::~Sound()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::sound::Sound::Init(void)
{
	this->type_ = tml::ConstantUtil::SOUND::SOUND_TYPE::NONE;

	tml::sound::Resource::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @param type (type)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::sound::Sound::Create(const tml::sound::SoundDesc &desc, const tml::ConstantUtil::SOUND::SOUND_TYPE type)
{
	if (type == tml::ConstantUtil::SOUND::SOUND_TYPE::NONE) {
		return (-1);
	}

	if (tml::sound::Resource::Create(desc, tml::ConstantUtil::SOUND::RESOURCE_TYPE::SOUND) < 0) {
		return (-1);
	}

	this->type_ = type;

	return (0);
}
