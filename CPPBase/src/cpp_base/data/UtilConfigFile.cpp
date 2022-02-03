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
	memory_allocator_size(1048576U),
	string_locale_name("Japanese"),
	file_cache_file_limit(128U),
	file_cache_file_buffer_limit(10240U)
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

	this->memory_allocator_size = 1048576U;
	this->string_locale_name = "Japanese";
	this->file_cache_file_limit = 128U;
	this->file_cache_file_buffer_limit = 10240U;

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
 * @brief OnRead関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::UtilConfigFile::OnRead(void)
{
	auto read_desc_dat = this->read_desc.GetDataByParent();

	tml::RawINIFile conf_file;

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

	{// Memory Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"MEM");

		if (val_name_cont != nullptr) {
			val = conf_file.data.GetValue((*val_name_cont), L"ALLOCATOR_SIZE");

			if (val != nullptr) {
				tml::StringUtil::GetValue(this->data.memory_allocator_size, val->c_str());
			}
		}
	}

	{// String Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"STR");

		if (val_name_cont != nullptr) {
			val = conf_file.data.GetValue((*val_name_cont), L"LOCALE_NAME");

			if (val != nullptr) {
				tml::StringUtil::GetStringRaw(this->data.string_locale_name, val->c_str());
			}
		}
	}

	/*
	{// Time Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"TIME");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	/*
	{// Math Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"MATH");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	/*
	{// Random Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"RAND");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	{// File Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"FILE");

		if (val_name_cont != nullptr) {
			val = conf_file.data.GetValue((*val_name_cont), L"CACHE_FILE_LIMIT");

			if (val != nullptr) {
				tml::StringUtil::GetValue(this->data.file_cache_file_limit, val->c_str());
			}

			val = conf_file.data.GetValue((*val_name_cont), L"CACHE_FILE_BUFFER_LIMIT");

			if (val != nullptr) {
				tml::StringUtil::GetValue(this->data.file_cache_file_buffer_limit, val->c_str());
			}
		}
	}

	/*
	{// Thread Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"TH");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief OnWrite関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::UtilConfigFile::OnWrite(void)
{
	static const std::wstring empty_str = L"";
	static const std::wstring section_start_str = L"[";
	static const std::wstring section_end_str = L"]";
	static const std::wstring equal_str = L"=";

	auto write_desc_dat = this->write_desc.GetDataByParent();

	if (write_desc_dat->file_path.empty()) {
		return (-1);
	}

	tml::RawTextFile conf_file;

	std::wstring val;

	{// Memory Section Write
		conf_file.data.line_string_container.push_back(section_start_str + L"MEM" + section_end_str);
		conf_file.data.line_string_container.push_back(L"ALLOCATOR_SIZE" + equal_str + tml::StringUtil::GetString(val, this->data.memory_allocator_size));
		conf_file.data.line_string_container.push_back(empty_str);
	}

	{// String Section Write
		conf_file.data.line_string_container.push_back(section_start_str + L"STR" + section_end_str);
		conf_file.data.line_string_container.push_back(L"LOCALE_NAME" + equal_str + tml::StringUtil::GetStringRaw(val, this->data.string_locale_name.c_str()));
		conf_file.data.line_string_container.push_back(empty_str);
	}

	{// Time Section Write
		conf_file.data.line_string_container.push_back(section_start_str + L"TIME" + section_end_str);
		conf_file.data.line_string_container.push_back(empty_str);
	}

	{// Math Section Write
		conf_file.data.line_string_container.push_back(section_start_str + L"MATH" + section_end_str);
		conf_file.data.line_string_container.push_back(empty_str);
	}

	{// Random Section Write
		conf_file.data.line_string_container.push_back(section_start_str + L"RAND" + section_end_str);
		conf_file.data.line_string_container.push_back(empty_str);
	}

	{// File Section Write
		conf_file.data.line_string_container.push_back(section_start_str + L"FILE" + section_end_str);
		conf_file.data.line_string_container.push_back(L"CACHE_FILE_LIMIT" + equal_str + tml::StringUtil::GetString(val, this->data.file_cache_file_limit));
		conf_file.data.line_string_container.push_back(L"CACHE_FILE_BUFFER_LIMIT" + equal_str + tml::StringUtil::GetString(val, this->data.file_cache_file_buffer_limit));
		conf_file.data.line_string_container.push_back(empty_str);
	}

	{// Thread Section Write
		conf_file.data.line_string_container.push_back(section_start_str + L"TH" + section_end_str);
		conf_file.data.line_string_container.push_back(empty_str);
	}

	conf_file.write_desc.parent_data = write_desc_dat;

	if (conf_file.Write() < 0) {
		return (-1);
	}

	return (0);
}
