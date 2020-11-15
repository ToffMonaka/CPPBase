/**
 * @file
 * @brief BinaryFile�R�[�h�t�@�C��
 */


#include "BinaryFile.h"


/**
 * @brief �R���X�g���N�^
 */
tml::BinaryFile::BinaryFile()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::BinaryFile::~BinaryFile()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::BinaryFile::Release(void)
{
	tml::File::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::BinaryFile::Init(void)
{
	this->Release();

	tml::File::Init();

	return;
}


/**
 * @brief Read�֐�
 */
void tml::BinaryFile::Read(void)
{
	return;
}


/**
 * @brief Write�֐�
 */
void tml::BinaryFile::Write(void)
{
	return;
}
