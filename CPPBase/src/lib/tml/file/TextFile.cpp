/**
 * @file
 * @brief TextFile�R�[�h�t�@�C��
 */


#include "TextFile.h"


/**
 * @brief �R���X�g���N�^
 */
tml::TextFile::TextFile()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::TextFile::~TextFile()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::TextFile::Release(void)
{
	tml::File::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::TextFile::Init(void)
{
	this->Release();

	tml::File::Init();

	return;
}


/**
 * @brief Read�֐�
 */
void tml::TextFile::Read(void)
{
	return;
}


/**
 * @brief Write�֐�
 */
void tml::TextFile::Write(void)
{
	return;
}
