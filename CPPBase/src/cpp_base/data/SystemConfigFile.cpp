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
	return;
}


/**
 * @brief Init関数
 */
void cpp_base::SystemConfigFileData::Init(void)
{
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

	if (ini_file.data.value_container.empty()) {
		return (0);
	}

	std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	std::wstring *val = nullptr;

	{// APPLICATION Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"APPLICATION");

		if (val_name_cont != nullptr) {
			val = ini_file.data.GetValue((*val_name_cont), L"MEM_ALLOCATOR_SIZE");

			if (val != nullptr) {
				tml::StringUtil::GetValue(this->data.application_memory_allocator_size, val->c_str());
			}

			val = ini_file.data.GetValue((*val_name_cont), L"LOCALE_NAME");

			if (val != nullptr) {
				tml::StringUtil::GetString(this->data.application_locale_name, val->c_str());
			}
		}
	}

	{// WINDOW Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"WINDOW");

		if (val_name_cont != nullptr) {
			val = ini_file.data.GetValue((*val_name_cont), L"X");

			if (val != nullptr) {
				tml::StringUtil::GetValue(this->data.window_x, val->c_str());
			}

			val = ini_file.data.GetValue((*val_name_cont), L"Y");

			if (val != nullptr) {
				tml::StringUtil::GetValue(this->data.window_y, val->c_str());
			}

			val = ini_file.data.GetValue((*val_name_cont), L"W");

			if (val != nullptr) {
				tml::StringUtil::GetValue(this->data.window_width, val->c_str());
			}

			val = ini_file.data.GetValue((*val_name_cont), L"H");

			if (val != nullptr) {
				tml::StringUtil::GetValue(this->data.window_height, val->c_str());
			}
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
	if (this->write_plan.file_path.empty()) {
		return (-1);
	}

	tml::TextFile txt_file;

	const std::wstring empty_str = L"";
	const std::wstring section_start_str = L"[";
	const std::wstring section_end_str = L"]";
	const std::wstring equal_str = L"=";
	std::wstring val;

	{// APPLICATION Section Write
		txt_file.data.string_container.push_back(section_start_str + L"MEM_ALLOCATOR_SIZE" + section_end_str);
		txt_file.data.string_container.push_back(empty_str + L"MEM_ALLOCATOR_SIZE" + equal_str + tml::StringUtil::GetString(val, this->data.application_memory_allocator_size));
		txt_file.data.string_container.push_back(empty_str + L"LOCALE_NAME" + equal_str + tml::StringUtil::GetString(val, this->data.application_locale_name.c_str()));
		txt_file.data.string_container.push_back(empty_str);
	}

	{// WINDOW Section Write
		txt_file.data.string_container.push_back(section_start_str + L"WINDOW" + section_end_str);
		txt_file.data.string_container.push_back(empty_str + L"X" + equal_str + tml::StringUtil::GetString(val, this->data.window_x));
		txt_file.data.string_container.push_back(empty_str + L"Y" + equal_str + tml::StringUtil::GetString(val, this->data.window_y));
		txt_file.data.string_container.push_back(empty_str + L"W" + equal_str + tml::StringUtil::GetString(val, this->data.window_width));
		txt_file.data.string_container.push_back(empty_str + L"H" + equal_str + tml::StringUtil::GetString(val, this->data.window_height));
		txt_file.data.string_container.push_back(empty_str);
	}

	txt_file.write_plan.file_path = this->write_plan.file_path;
	txt_file.write_plan.one_buffer_size = this->write_plan.one_buffer_size;
	txt_file.write_plan.add_flag = this->write_plan.add_flag;
	txt_file.write_plan.newline_code_type = this->write_plan.newline_code_type;
	txt_file.write_plan.add_newline_code_count = this->write_plan.add_newline_code_count;

	if (txt_file.Write()) {
		return (-1);
	}

	return (0);
}
