/**
 * @file
 * @brief SystemConfigFileコードファイル
 */


#include "SystemConfigFile.h"
#include "../../lib/tml/string/StringUtil.h"


/**
 * @brief コンストラクタ
 */
cpp_base::SystemConfigFileData::SystemConfigFileData() :
	application_memory_allocator_size(1048576U),
	application_locale_name("Japanese"),
	window_x(0U),
	window_y(0U),
	window_width(1280U),
	window_height(800U)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::SystemConfigFileData::~SystemConfigFileData()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::SystemConfigFileData::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void cpp_base::SystemConfigFileData::Init(void)
{
	this->Release();

	this->application_memory_allocator_size = 1048576U;
	this->application_locale_name = "Japanese";
	this->window_x = 0U;
	this->window_y = 0U;
	this->window_width = 1280U;
	this->window_height = 800U;

	return;
}


/**
 * @brief コンストラクタ
 */
cpp_base::SystemConfigFileReadPlan::SystemConfigFileReadPlan()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::SystemConfigFileReadPlan::~SystemConfigFileReadPlan()
{
	return;
}


/**
 * @brief Init関数
 */
void cpp_base::SystemConfigFileReadPlan::Init(void)
{
	tml::INIFileReadPlan::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
cpp_base::SystemConfigFileWritePlan::SystemConfigFileWritePlan()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::SystemConfigFileWritePlan::~SystemConfigFileWritePlan()
{
	return;
}


/**
 * @brief Init関数
 */
void cpp_base::SystemConfigFileWritePlan::Init(void)
{
	tml::INIFileWritePlan::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
cpp_base::SystemConfigFile::SystemConfigFile()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::SystemConfigFile::~SystemConfigFile()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::SystemConfigFile::Release(void)
{
	tml::File::Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::SystemConfigFile::Init(void)
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
INT cpp_base::SystemConfigFile::Read(void)
{
	tml::INIFile ini_file;

	if (this->read_plan.file_path.empty()) {
		ini_file.read_plan.file_path = this->read_plan.file_path;
		ini_file.read_plan.file_buffer = std::move(this->read_plan.file_buffer);
		ini_file.read_plan.one_buffer_size = this->read_plan.one_buffer_size;
		ini_file.read_plan.newline_code_type = this->read_plan.newline_code_type;

		if (ini_file.Read()) {
			this->read_plan.file_buffer = std::move(ini_file.read_plan.file_buffer);

			return (-1);
		}

		this->read_plan.file_buffer = std::move(ini_file.read_plan.file_buffer);
	} else {
		ini_file.read_plan.file_path = this->read_plan.file_path;
		ini_file.read_plan.one_buffer_size = this->read_plan.one_buffer_size;
		ini_file.read_plan.newline_code_type = this->read_plan.newline_code_type;

		if (ini_file.Read()) {
			return (-1);
		}
	}

	this->data.Init();

	{// APPLICATION section set
		auto val_name_cont = ini_file.data.GetValueNameContainer(L"APPLICATION");

		if (val_name_cont != nullptr) {
			tml::StringUtil::GetValue(this->data.application_memory_allocator_size, tml::StringUtil::GetString(ini_file.data.GetValue((*val_name_cont), L"MEM_ALLOCATOR_SIZE")));
			tml::StringUtil::GetString(this->data.application_locale_name, tml::StringUtil::GetString(ini_file.data.GetValue((*val_name_cont), L"LOCALE_NAME")));
		}
	}

	{// WINDOW section set
		auto val_name_cont = ini_file.data.GetValueNameContainer(L"WINDOW");

		if (val_name_cont != nullptr) {
			tml::StringUtil::GetValue(this->data.window_x, tml::StringUtil::GetString(ini_file.data.GetValue((*val_name_cont), L"X")));
			tml::StringUtil::GetValue(this->data.window_y, tml::StringUtil::GetString(ini_file.data.GetValue((*val_name_cont), L"Y")));
			tml::StringUtil::GetValue(this->data.window_width, tml::StringUtil::GetString(ini_file.data.GetValue((*val_name_cont), L"W")));
			tml::StringUtil::GetValue(this->data.window_height, tml::StringUtil::GetString(ini_file.data.GetValue((*val_name_cont), L"H")));
		}
	}

	return (0);
}


/**
 * @brief Write関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::SystemConfigFile::Write(void)
{
	return (-1);
}
