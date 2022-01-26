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
	application_frame_rate_limit(60U),
	window_position(0U),
	window_size(1280U, 800U),
	graphic_frame_rate_limit(60U),
	graphic_vsync_flag(true),
	sound_bgm_volume(0.5f),
	sound_bgm_mute_flag(false),
	sound_se_volume(0.5f),
	sound_se_mute_flag(false)
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
 * @brief Init関数
 */
void cpp_base::SystemConfigFileData::Init(void)
{
	this->Release();

	this->application_frame_rate_limit = 60U;
	this->window_position = 0U;
	this->window_size = tml::XMUINT2EX(1280U, 800U);
	this->graphic_frame_rate_limit = 60U;
	this->graphic_vsync_flag = true;
	this->sound_bgm_volume = 0.5f;
	this->sound_bgm_mute_flag = false;
	this->sound_se_volume = 0.5f;
	this->sound_se_mute_flag = false;

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
 * @brief Init関数
 */
void cpp_base::SystemConfigFile::Init(void)
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
INT cpp_base::SystemConfigFile::OnRead(void)
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

	{// Application Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"APP");

		if (val_name_cont != nullptr) {
			val = conf_file.data.GetValue((*val_name_cont), L"FRAME_RATE_LIMIT");

			if (val != nullptr) {
				tml::StringUtil::GetValue(this->data.application_frame_rate_limit, val->c_str());
			}
		}
	}

	{// Window Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"WND");

		if (val_name_cont != nullptr) {
			val = conf_file.data.GetValue((*val_name_cont), L"X");

			if (val != nullptr) {
				tml::StringUtil::GetValue(this->data.window_position.x, val->c_str());
			}

			val = conf_file.data.GetValue((*val_name_cont), L"Y");

			if (val != nullptr) {
				tml::StringUtil::GetValue(this->data.window_position.y, val->c_str());
			}

			val = conf_file.data.GetValue((*val_name_cont), L"W");

			if (val != nullptr) {
				tml::StringUtil::GetValue(this->data.window_size.x, val->c_str());
			}

			val = conf_file.data.GetValue((*val_name_cont), L"H");

			if (val != nullptr) {
				tml::StringUtil::GetValue(this->data.window_size.y, val->c_str());
			}
		}
	}

	{// Graphic Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"GRAPHIC");

		if (val_name_cont != nullptr) {
			val = conf_file.data.GetValue((*val_name_cont), L"FRAME_RATE_LIMIT");

			if (val != nullptr) {
				tml::StringUtil::GetValue(this->data.graphic_frame_rate_limit, val->c_str());
			}

			val = conf_file.data.GetValue((*val_name_cont), L"VSYNC_FLG");

			if (val != nullptr) {
				tml::StringUtil::GetValue(this->data.graphic_vsync_flag, val->c_str());
			}
		}
	}

	{// Sound Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"SOUND");

		if (val_name_cont != nullptr) {
			val = conf_file.data.GetValue((*val_name_cont), L"BGM_VOLUME");

			if (val != nullptr) {
				tml::StringUtil::GetValue(this->data.sound_bgm_volume, val->c_str());
			}

			val = conf_file.data.GetValue((*val_name_cont), L"BGM_MUTE_FLG");

			if (val != nullptr) {
				tml::StringUtil::GetValue(this->data.sound_bgm_mute_flag, val->c_str());
			}

			val = conf_file.data.GetValue((*val_name_cont), L"SE_VOLUME");

			if (val != nullptr) {
				tml::StringUtil::GetValue(this->data.sound_se_volume, val->c_str());
			}

			val = conf_file.data.GetValue((*val_name_cont), L"SE_MUTE_FLG");

			if (val != nullptr) {
				tml::StringUtil::GetValue(this->data.sound_se_mute_flag, val->c_str());
			}
		}
	}

	return (0);
}


/**
 * @brief OnWrite関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::SystemConfigFile::OnWrite(void)
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

	{// Application Section Write
		conf_file.data.line_string_container.push_back(section_start_str + L"APPLICATION" + section_end_str);
		conf_file.data.line_string_container.push_back(L"FRAME_RATE_LIMIT" + equal_str + tml::StringUtil::GetString(val, this->data.application_frame_rate_limit));
		conf_file.data.line_string_container.push_back(empty_str);
	}

	{// Window Section Write
		conf_file.data.line_string_container.push_back(section_start_str + L"WINDOW" + section_end_str);
		conf_file.data.line_string_container.push_back(L"X" + equal_str + tml::StringUtil::GetString(val, this->data.window_position.x));
		conf_file.data.line_string_container.push_back(L"Y" + equal_str + tml::StringUtil::GetString(val, this->data.window_position.y));
		conf_file.data.line_string_container.push_back(L"W" + equal_str + tml::StringUtil::GetString(val, this->data.window_size.x));
		conf_file.data.line_string_container.push_back(L"H" + equal_str + tml::StringUtil::GetString(val, this->data.window_size.y));
		conf_file.data.line_string_container.push_back(empty_str);
	}

	{// Graphic Section Write
		conf_file.data.line_string_container.push_back(section_start_str + L"GRAPHIC" + section_end_str);
		conf_file.data.line_string_container.push_back(L"FRAME_RATE_LIMIT" + equal_str + tml::StringUtil::GetString(val, this->data.graphic_frame_rate_limit));
		conf_file.data.line_string_container.push_back(L"VSYNC_FLG" + equal_str + tml::StringUtil::GetString(val, this->data.graphic_vsync_flag));
		conf_file.data.line_string_container.push_back(empty_str);
	}

	{// Sound Section Write
		conf_file.data.line_string_container.push_back(section_start_str + L"SOUND" + section_end_str);
		conf_file.data.line_string_container.push_back(L"BGM_VOLUME" + equal_str + tml::StringUtil::GetString(val, this->data.sound_bgm_volume));
		conf_file.data.line_string_container.push_back(L"BGM_MUTE_FLG" + equal_str + tml::StringUtil::GetString(val, this->data.sound_bgm_mute_flag));
		conf_file.data.line_string_container.push_back(L"SE_VOLUME" + equal_str + tml::StringUtil::GetString(val, this->data.sound_se_volume));
		conf_file.data.line_string_container.push_back(L"SE_MUTE_FLG" + equal_str + tml::StringUtil::GetString(val, this->data.sound_se_mute_flag));
		conf_file.data.line_string_container.push_back(empty_str);
	}

	conf_file.write_desc.parent_data = write_desc_dat;

	if (conf_file.Write() < 0) {
		return (-1);
	}

	return (0);
}
