/**
 * @file
 * @brief File�R�[�h�t�@�C��
 */


#include "File.h"


/**
 * @brief �R���X�g���N�^
 */
tml::FileReadDescData::FileReadDescData()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::FileReadDescData::~FileReadDescData()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::FileReadDescData::Init(void)
{
	this->Release();

	this->file_path.clear();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::FileWriteDescData::FileWriteDescData()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::FileWriteDescData::~FileWriteDescData()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::FileWriteDescData::Init(void)
{
	this->Release();

	this->file_path.clear();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::File::File()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::File::~File()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::File::Init(void)
{
	this->Release();

	return;
}
