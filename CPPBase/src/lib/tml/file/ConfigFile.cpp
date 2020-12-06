/**
 * @file
 * @brief ConfigFile�R�[�h�t�@�C��
 */


#include "ConfigFile.h"


/**
 * @brief �R���X�g���N�^
 */
tml::ConfigFileData::ConfigFileData()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::ConfigFileData::~ConfigFileData()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::ConfigFileData::Release(void)
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::ConfigFileData::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::ConfigFileReadPlan::ConfigFileReadPlan() :
	one_buffer_size(1024U),
	newline_code_type(tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::ConfigFileReadPlan::~ConfigFileReadPlan()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::ConfigFileReadPlan::Init(void)
{
	this->file_path.clear();
	this->one_buffer_size = 1024U;
	this->newline_code_type = tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF;

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::ConfigFileWritePlan::ConfigFileWritePlan() :
	one_buffer_size(1024U),
	add_flag(false),
	newline_code_type(tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::ConfigFileWritePlan::~ConfigFileWritePlan()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::ConfigFileWritePlan::Init(void)
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
tml::ConfigFile::ConfigFile()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::ConfigFile::~ConfigFile()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::ConfigFile::Release(void)
{
	tml::File::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::ConfigFile::Init(void)
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
INT tml::ConfigFile::Read(void)
{
	return (-1);
}


/**
 * @brief Write�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::ConfigFile::Write(void)
{
	return (-1);
}
