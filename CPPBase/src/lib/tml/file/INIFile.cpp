/**
 * @file
 * @brief INIFile�R�[�h�t�@�C��
 */


#include "INIFile.h"


/**
 * @brief �R���X�g���N�^
 */
tml::INIFileData::INIFileData()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::INIFileData::~INIFileData()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::INIFileData::Release(void)
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::INIFileData::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::INIFileReadPlan::INIFileReadPlan() :
	one_buffer_size(1024U),
	newline_code_type(tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::INIFileReadPlan::~INIFileReadPlan()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::INIFileReadPlan::Init(void)
{
	this->file_path.clear();
	this->one_buffer_size = 1024U;
	this->newline_code_type = tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF;

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::INIFileWritePlan::INIFileWritePlan() :
	one_buffer_size(1024U),
	add_flag(false),
	newline_code_type(tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::INIFileWritePlan::~INIFileWritePlan()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::INIFileWritePlan::Init(void)
{
	this->file_path.clear();
	this->one_buffer_size = 1024U;
	this->add_flag = false;
	this->newline_code_type = tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF;

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::INIFile::INIFile()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::INIFile::~INIFile()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::INIFile::Release(void)
{
	tml::File::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::INIFile::Init(void)
{
	this->Release();

	this->data.Init();
	this->read_plan.Init();
	this->write_plan.Init();

	return;
}


/**
 * @brief Read�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::INIFile::Read(void)
{
	return (-1);
}


/**
 * @brief Write�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::INIFile::Write(void)
{
	return (-1);
}
