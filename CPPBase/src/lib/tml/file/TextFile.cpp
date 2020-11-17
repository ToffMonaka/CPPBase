/**
 * @file
 * @brief TextFile�R�[�h�t�@�C��
 */


#include "TextFile.h"
#include <fstream>


/**
 * @brief �R���X�g���N�^
 */
tml::TextFileReadPlan::TextFileReadPlan()
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

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::TextFileWritePlan::TextFileWritePlan()
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
	this->line_str_cont_.clear();

	tml::File::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::TextFile::Init(void)
{
	this->Release();

	this->read_plan.Init();
	this->write_plan.Init();

	tml::File::Init();

	return;
}


/**
 * @brief Read�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::TextFile::Read(void)
{
	std::ifstream ifs;

	ifs.open(this->read_plan.file_path.c_str(), std::ios_base::in);

	if (!ifs) {
	    return (-1);
	}

	std::vector<std::wstring> line_str_cont;

	ifs.close();

	this->line_str_cont_ = line_str_cont;

	return (0);
}


/**
 * @brief Write�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::TextFile::Write(void)
{
	std::ofstream ofs;

	ofs.open(this->write_plan.file_path.c_str(), std::ios_base::out);

	if (!ofs) {
	    return (-1);
	}

	if (this->line_str_cont_.size() <= 0U) {
		ofs.close();

		return (0);
	}

	ofs.close();

	return (0);
}
