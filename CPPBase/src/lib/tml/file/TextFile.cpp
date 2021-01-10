/**
 * @file
 * @brief TextFile�R�[�h�t�@�C��
 */


#include "TextFile.h"
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
	return;
}


/**
 * @brief Init�֐�
 */
void tml::TextFileData::Init(void)
{
	this->string_container.clear();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::TextFileReadPlanData::TextFileReadPlanData() :
	newline_code_type(tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::TextFileReadPlanData::~TextFileReadPlanData()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::TextFileReadPlanData::Init(void)
{
	this->newline_code_type = tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF;

	tml::BinaryFileReadPlanData::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::TextFileReadPlan::TextFileReadPlan() :
	parent_data(nullptr)
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
	this->data.Init();
	this->parent_data = nullptr;

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::TextFileWritePlanData::TextFileWritePlanData() :
	newline_code_type(tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF),
	add_newline_code_count(1U)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::TextFileWritePlanData::~TextFileWritePlanData()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::TextFileWritePlanData::Init(void)
{
	this->newline_code_type = tml::ConstantUtil::NEWLINE_CODE::TYPE::CRLF;
	this->add_newline_code_count = 1U;

	tml::BinaryFileWritePlanData::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::TextFileWritePlan::TextFileWritePlan() :
	parent_data(nullptr)
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
	this->data.Init();
	this->parent_data = nullptr;

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
	auto read_plan_dat = this->read_plan.GetDataByParent();

	tml::BinaryFile bin_file;

	bin_file.read_plan.parent_data = read_plan_dat;

	if (bin_file.Read()) {
		return (-1);
	}

	this->data.Init();

	if (bin_file.data.file_buffer.GetSize() <= 0U) {
		return (0);
	}

	bin_file.data.file_buffer.Set(bin_file.data.file_buffer.GetSize() + sizeof(CHAR), true);
	bin_file.data.file_buffer.WriteCHAR(0);

	std::wstring buf_str;
	CHAR *tmp_buf_str = reinterpret_cast<CHAR *>(bin_file.data.file_buffer.Get());

	tml::StringUtil::GetString(buf_str, tmp_buf_str);

	tml::StringUtil::Split(this->data.string_container, buf_str.c_str(), tml::ConstantUtil::NEWLINE_CODE::GetString(read_plan_dat->newline_code_type));

	return (0);
}


/**
 * @brief Write�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::TextFile::Write(void)
{
	auto write_plan_dat = this->write_plan.GetDataByParent();

	if (write_plan_dat->file_path.empty()) {
		return (-1);
	}

	std::wstring buf_str;
	std::string tmp_buf_str;

	tml::StringUtil::Join(buf_str, this->data.string_container, tml::ConstantUtil::NEWLINE_CODE::GetString(write_plan_dat->newline_code_type));

	if (!buf_str.empty()) {
		if ((write_plan_dat->add_flag)
		&& (write_plan_dat->add_newline_code_count > 0U)) {
			std::wstring add_newline_code_str;

			for (size_t add_newline_code_i = 0U; add_newline_code_i < write_plan_dat->add_newline_code_count; ++add_newline_code_i) {
				add_newline_code_str += tml::ConstantUtil::NEWLINE_CODE::GetString(write_plan_dat->newline_code_type);
			}

			buf_str.insert(0U, add_newline_code_str);
		}
	}

	tml::StringUtil::GetString(tmp_buf_str, buf_str.c_str());

	tml::BinaryFile bin_file;

	bin_file.data.file_buffer.Set(tmp_buf_str.length());
	bin_file.data.file_buffer.WriteArray(reinterpret_cast<const BYTE *>(tmp_buf_str.c_str()), tmp_buf_str.length(), tmp_buf_str.length());

	bin_file.write_plan.parent_data = write_plan_dat;

	if (bin_file.Write()) {
		return (-1);
	}

	return (0);
}
