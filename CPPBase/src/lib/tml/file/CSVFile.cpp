/**
 * @file
 * @brief CSVFile�R�[�h�t�@�C��
 */


#include "CSVFile.h"


/**
 * @brief �R���X�g���N�^
 */
tml::CSVFileData::CSVFileData()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::CSVFileData::~CSVFileData()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::CSVFileData::Release(void)
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::CSVFileData::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::CSVFileReadPlan::CSVFileReadPlan() :
	one_buffer_size(1024U),
	newline_code_type(tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::CSVFileReadPlan::~CSVFileReadPlan()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::CSVFileReadPlan::Init(void)
{
	this->file_path.clear();
	this->one_buffer_size = 1024U;
	this->newline_code_type = tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF;

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::CSVFileWritePlan::CSVFileWritePlan() :
	one_buffer_size(1024U),
	add_flag(false),
	newline_code_type(tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::CSVFileWritePlan::~CSVFileWritePlan()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::CSVFileWritePlan::Init(void)
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
tml::CSVFile::CSVFile()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::CSVFile::~CSVFile()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::CSVFile::Release(void)
{
	tml::File::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::CSVFile::Init(void)
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
INT tml::CSVFile::Read(void)
{
	return (-1);
}


/**
 * @brief Write�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::CSVFile::Write(void)
{
	return (-1);
}
