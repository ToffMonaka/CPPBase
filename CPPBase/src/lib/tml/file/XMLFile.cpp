/**
 * @file
 * @brief XMLFileコードファイル
 */


#include "XMLFile.h"
#include "../string/StringUtil.h"


/**
 * @brief コンストラクタ
 */
tml::XMLFileData::XMLFileData()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::XMLFileData::~XMLFileData()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::XMLFileData::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::XMLFileReadDescData::XMLFileReadDescData()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::XMLFileReadDescData::~XMLFileReadDescData()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::XMLFileReadDescData::Init(void)
{
	this->Release();

	tml::TextFileReadDescData::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::XMLFileWriteDescData::XMLFileWriteDescData()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::XMLFileWriteDescData::~XMLFileWriteDescData()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::XMLFileWriteDescData::Init(void)
{
	this->Release();

	tml::TextFileWriteDescData::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::XMLFile::XMLFile()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::XMLFile::~XMLFile()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::XMLFile::Init(void)
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
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::XMLFile::Read(void)
{
	auto read_desc_dat = this->read_desc.GetDataByParent();

	tml::TextFile txt_file;

	txt_file.read_desc.parent_data = read_desc_dat;

	if (txt_file.Read() < 0) {
		return (-1);
	}

	this->data.Init();

	if (txt_file.data.line_string_container.empty()) {
		return (0);
	}

	std::wstring file_str;
	std::string tmp_file_str;

	tml::StringUtil::Join(file_str, txt_file.data.line_string_container, L"");

	tml::StringUtil::GetString(tmp_file_str, file_str.c_str());

	tml::DynamicBuffer xml_buf;

	xml_buf.SetSize(tmp_file_str.size() + sizeof(CHAR));
	xml_buf.WriteArray(reinterpret_cast<const BYTE *>(tmp_file_str.c_str()), tmp_file_str.size(), tmp_file_str.size());
	xml_buf.WriteCHAR(0);

	CHAR *xml_str = reinterpret_cast<CHAR *>(xml_buf.Get());

	tml::unique_ptr<rapidxml::xml_document<>> xml_doc = tml::make_unique<rapidxml::xml_document<>>(1U);

	try {
		xml_doc->parse<rapidxml::parse_default>(xml_str);
	} catch (rapidxml::parse_error &err) {
		std::cout << err.what() << std::endl;

		return (-1);
	}

	int a = 0;

	return (0);
}


/**
 * @brief Write関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::XMLFile::Write(void)
{
	auto write_desc_dat = this->write_desc.GetDataByParent();

	if (write_desc_dat->file_path.empty()) {
		return (-1);
	}

	tml::TextFile txt_file;

	txt_file.write_desc.parent_data = write_desc_dat;

	if (txt_file.Write() < 0) {
		return (-1);
	}

	return (0);
}
