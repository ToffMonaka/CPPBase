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
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0����=���s
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
 * @brief �R���X�g���N�^
 */
tml::sound::SESound::SESound() :
	desc_(nullptr)
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
 * @brief Release�֐�
 */
void tml::sound::SESound::Release(void)
{
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
 * @brief OnCreate�֐�
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::sound::SESound::OnCreate(void)
{
	if (tml::sound::Sound::OnCreate() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnCreateDeferred�֐�
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::sound::SESound::OnCreateDeferred(void)
{
	if (tml::sound::Sound::OnCreateDeferred() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnSetDesc�֐�
 * @param desc (desc)
 */
void tml::sound::SESound::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::sound::SESoundDesc *>(desc);

	tml::sound::Sound::OnSetDesc(this->desc_);

	return;
}
