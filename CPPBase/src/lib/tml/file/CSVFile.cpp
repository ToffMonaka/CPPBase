/**
 * @file
 * @brief CSVFileコードファイル
 */


#include "CSVFile.h"


/**
 * @brief コンストラクタ
 */
tml::CSVFileData::CSVFileData()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::CSVFileData::~CSVFileData()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::CSVFileData::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::CSVFileData::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::CSVFileReadPlan::CSVFileReadPlan() :
	one_buffer_size(1024U),
	newline_code_type(tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::CSVFileReadPlan::~CSVFileReadPlan()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::CSVFileReadPlan::Init(void)
{
	this->file_path.clear();
	this->one_buffer_size = 1024U;
	this->newline_code_type = tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::CSVFileWritePlan::CSVFileWritePlan() :
	one_buffer_size(1024U),
	add_flag(false),
	newline_code_type(tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::CSVFileWritePlan::~CSVFileWritePlan()
{
	return;
}


/**
 * @brief Init関数
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
 * @brief コンストラクタ
 */
tml::CSVFile::CSVFile()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::CSVFile::~CSVFile()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::CSVFile::Release(void)
{
	tml::File::Release();

	return;
}


/**
 * @brief Init関数
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
 * @brief Read関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::CSVFile::Read(void)
{
	return (-1);
}


/**
 * @brief Write関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::CSVFile::Write(void)
{
	return (-1);
}
