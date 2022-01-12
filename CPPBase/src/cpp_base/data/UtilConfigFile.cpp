/**
 * @file
 * @brief UtilConfigFileコードファイル
 */


#include "UtilConfigFile.h"
#include "../../lib/tml/string/StringUtil.h"


/**
 * @brief コンストラクタ
 */
cpp_base::UtilConfigFileData::UtilConfigFileData() :
	util_memory_allocator_size(1048576U),
	util_locale_name("Japanese")
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::UtilConfigFileData::~UtilConfigFileData()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::UtilConfigFileData::Init(void)
{
	this->Release();

	this->util_memory_allocator_size = 1048576U;
	this->util_locale_name = "Japanese";

	return;
}


/**
 * @brief コンストラクタ
 */
cpp_base::UtilConfigFile::UtilConfigFile()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::UtilConfigFile::~UtilConfigFile()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::UtilConfigFile::Init(void)
{
	this->Release();

	this->data.Init();
	this->read_desc.Init();
	this->write_desc.Init();

	tml::File::Init();

	return;
}


/**
 * @brief Read関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::UtilConfigFile::Read(void)
{
	auto read_desc_dat = this->read_desc.GetDataByParent();

	tml::INIFile conf_file;

	conf_file.read_desc.parent_data = read_desc_dat;

	if (conf_file.Read() < 0) {
		return (-1);
	}

	this->data.Init();

	if (conf_file.data.value_container.empty()) {
		return (0);
	}

	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Util Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"UTIL");

		if (val_name_cont != nullptr) {
			val = conf_file.data.GetValue((*val_name_cont), L"MEM_ALLOCATOR_SIZE");

			if (val != nullptr) {
				tml::StringUtil::GetValue(this->data.util_memory_allocator_size, val->c_str());
			}

			val = conf_file.data.GetValue((*val_name_cont), L"LOCALE_NAME");

			if (val != nullptr) {
				tml::StringUtil::GetString(this->data.util_locale_name, val->c_str());
			}
		}
	}

	return (0);
}


/**
 * @brief Write関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::UtilConfigFile::Write(void)
{
	static const std::wstring empty_str = L"";
	static const std::wstring section_start_str = L"[";
	static const std::wstring section_end_str = L"]";
	static const std::wstring equal_str = L"=";

	auto write_desc_dat = this->write_desc.GetDataByParent();

	if (write_desc_dat->file_path.empty()) {
		return (-1);
	}

	tml::TextFile conf_file;

	std::wstring val;

	{// Util Section Write
		conf_file.data.line_string_container.push_back(section_start_str + L"UTIL" + section_end_str);
		conf_file.data.line_string_container.push_back(L"MEM_ALLOCATOR_SIZE" + equal_str + tml::StringUtil::GetString(val, this->data.util_memory_allocator_size));
		conf_file.data.line_string_container.push_back(L"LOCALE_NAME" + equal_str + tml::StringUtil::GetString(val, this->data.util_locale_name.c_str()));
		conf_file.data.line_string_container.push_back(empty_str);
	}

	conf_file.write_desc.parent_data = write_desc_dat;

	if (conf_file.Write() < 0) {
		return (-1);
	}

	return (0);
}
