/**
 * @file
 * @brief TextFile�R�[�h�t�@�C��
 */


#include "TextFile.h"
#include "BinaryFile.h"
#include "../string/StringUtil.h"


/**
 * @brief �R���X�g���N�^
 */
tml::TextFileData::TextFileData()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::TextFileData::~TextFileData()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::TextFileData::Release(void)
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::TextFileData::Init(void)
{
	this->Release();

	this->string_container.clear();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::TextFileReadPlan::TextFileReadPlan() :
	one_buffer_size(1024U),
	newline_code_type(tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::TextFileReadPlan::~TextFileReadPlan()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::TextFileReadPlan::Init(void)
{
	this->file_path.clear();
	this->one_buffer_size = 1024U;
	this->newline_code_type = tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF;

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::TextFileWritePlan::TextFileWritePlan() :
	one_buffer_size(1024U),
	add_flag(false),
	newline_code_type(tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::TextFileWritePlan::~TextFileWritePlan()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::TextFileWritePlan::Init(void)
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
INT tml::TextFile::Read(void)
{
	tml::BinaryFile bin_file;

	bin_file.read_plan.file_path = this->read_plan.file_path;
	bin_file.read_plan.one_buffer_size = this->read_plan.one_buffer_size;

	if (bin_file.Read()) {
		return (-1);
	}

	bin_file.data.buffer.Set(bin_file.data.buffer.GetSize() + sizeof(CHAR), true);
	bin_file.data.buffer.WriteCHAR(0);

	std::wstring buf_str;
	CHAR *tmp_buf_str = reinterpret_cast<CHAR *>(bin_file.data.buffer.Get());

	tml::StringUtil::GetString(buf_str, tmp_buf_str);

	tml::StringUtil::Split(this->data.string_container, buf_str.c_str(), tml::ConstantUtil::NEWLINE_CODE::GetString(this->read_plan.newline_code_type));

	return (0);
}


/**
 * @brief Write�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::TextFile::Write(void)
{
	std::wstring buf_str;
	std::string tmp_buf_str;

	tml::StringUtil::Join(buf_str, this->data.string_container, tml::ConstantUtil::NEWLINE_CODE::GetString(this->write_plan.newline_code_type));

	tml::StringUtil::GetString(tmp_buf_str, buf_str.c_str());

	tml::BinaryFile bin_file;

	bin_file.data.buffer.Set(tmp_buf_str.length());
	bin_file.data.buffer.WriteArray(reinterpret_cast<const BYTE *>(tmp_buf_str.c_str()), tmp_buf_str.length(), tmp_buf_str.length());

	bin_file.write_plan.file_path = this->write_plan.file_path;
	bin_file.write_plan.one_buffer_size = this->write_plan.one_buffer_size;
	bin_file.write_plan.add_flag = this->write_plan.add_flag;

	if (bin_file.Write()) {
		return (-1);
	}

	return (0);
}
