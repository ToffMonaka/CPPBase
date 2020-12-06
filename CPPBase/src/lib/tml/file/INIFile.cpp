/**
 * @file
 * @brief INIFileコードファイル
 */


#include "INIFile.h"


/**
 * @brief コンストラクタ
 */
tml::INIFileData::INIFileData()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::INIFileData::~INIFileData()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::INIFileData::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::INIFileData::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::INIFileReadPlan::INIFileReadPlan() :
	one_buffer_size(1024U),
	newline_code_type(tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::INIFileReadPlan::~INIFileReadPlan()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::INIFileReadPlan::Init(void)
{
	this->file_path.clear();
	this->one_buffer_size = 1024U;
	this->newline_code_type = tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::INIFileWritePlan::INIFileWritePlan() :
	one_buffer_size(1024U),
	add_flag(false),
	newline_code_type(tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::INIFileWritePlan::~INIFileWritePlan()
{
	return;
}


/**
 * @brief Init関数
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
 * @brief コンストラクタ
 */
tml::INIFile::INIFile()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::INIFile::~INIFile()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::INIFile::Release(void)
{
	tml::File::Release();

	return;
}


/**
 * @brief Init関数
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
 * @brief Read関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::INIFile::Read(void)
{
	return (-1);
}


/**
 * @brief Write関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::INIFile::Write(void)
{
	return (-1);
}
