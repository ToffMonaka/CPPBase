/**
 * @file
 * @brief XMLFileコードファイル
 */


#include "XMLFile.h"
#include "../string/StringUtil.h"


const tml::shared_ptr<tml::XMLFileDataNode> tml::XMLFileDataNode::empty_child_node;


/**
 * @brief コンストラクタ
 */
tml::XMLFileDataNode::XMLFileDataNode() :
	parent_node_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::XMLFileDataNode::~XMLFileDataNode()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::XMLFileDataNode::Release(void)
{
	for (auto &child_node : this->child_node_cont_) {
		child_node->SetParentNode(nullptr);
	}

	this->child_node_cont_.clear();

	return;
}


/**
 * @brief Init関数
 */
void tml::XMLFileDataNode::Init(void)
{
	this->Release();

	this->name.clear();
	this->value_container.clear();
	this->string.clear();
	this->parent_node_ = nullptr;

	return;
}


/**
 * @brief GetChildNodeRecursivePart関数
 * @param child_node_cont (child_node_container)
 * @param child_node_name (child_node_name)
 * @return child_node (child_node)
 */
const tml::shared_ptr<tml::XMLFileDataNode> &tml::XMLFileDataNode::GetChildNodeRecursivePart(const std::list<tml::shared_ptr<tml::XMLFileDataNode>> &child_node_cont, const WCHAR *child_node_name)
{
	for (auto &child_node : child_node_cont) {
		if (child_node->name == child_node_name) {
			return (child_node);
		}

		auto &child_child_node = this->GetChildNodeRecursivePart(child_node->GetChildNodeContainer(), child_node_name);

		if (child_child_node != nullptr) {
			return (child_child_node);
		}
	}

	return (this->empty_child_node);
}


/**
 * @brief AddChildNode関数
 * @param child_node (child_node)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::XMLFileDataNode::AddChildNode(const tml::shared_ptr<tml::XMLFileDataNode> &child_node)
{
	if ((child_node == nullptr)
	|| (child_node.get() == this)) {
		return (-1);
	}

	if (child_node->GetParentNode() != nullptr) {
		return (-1);
	}

	auto child_node_itr = std::find(this->child_node_cont_.begin(), this->child_node_cont_.end(), child_node);

	if (child_node_itr != this->child_node_cont_.end()) {
		return (-1);
	}

	child_node->SetParentNode(this);

	this->child_node_cont_.push_back(child_node);

	return (0);
}


/**
 * @brief RemoveChildNode関数
 */
void tml::XMLFileDataNode::RemoveChildNode(void)
{
	std::list<tml::shared_ptr<tml::XMLFileDataNode>> child_node_cont = this->child_node_cont_;

	for (auto &child_node : child_node_cont) {
		this->RemoveChildNode(child_node);
	}

	return;
}


/**
 * @brief RemoveChildNode関数
 * @param child_node (child_node)
 */
void tml::XMLFileDataNode::RemoveChildNode(const tml::shared_ptr<tml::XMLFileDataNode> &child_node)
{
	if ((child_node == nullptr)
	|| (child_node.get() == this)) {
		return;
	}

	if (child_node->GetParentNode() == nullptr) {
		return;
	}

	auto child_node_itr = std::find(this->child_node_cont_.begin(), this->child_node_cont_.end(), child_node);

	if (child_node_itr == this->child_node_cont_.end()) {
		return;
	}

	child_node->SetParentNode(nullptr);

	this->child_node_cont_.erase(child_node_itr);

	return;
}


/**
 * @brief RemoveChildNodeFromParentNode関数
 */
void tml::XMLFileDataNode::RemoveChildNodeFromParentNode(void)
{
	if (this->parent_node_ == nullptr) {
		return;
	}

	tml::shared_ptr<tml::XMLFileDataNode> tmp_child_node;

	for (auto &child_node : this->parent_node_->child_node_cont_) {
		if (child_node.get() == this) {
			tmp_child_node = child_node;

			break;
		}
	}

	if (tmp_child_node == nullptr) {
		return;
	}

	this->parent_node_->RemoveChildNode(tmp_child_node);

	return;
}


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
 * @brief Release関数
 */
void tml::XMLFileData::Release(void)
{
	if (this->root_node_ != nullptr) {
		this->root_node_.reset();
	}

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
 * @brief SetRootNode関数
 * @param xml_doc (xml_document)
 */
void tml::XMLFileData::SetRootNode(const rapidxml::xml_document<> *xml_doc)
{
	if (this->root_node_ != nullptr) {
		return;
	}

	this->root_node_ = tml::make_shared<tml::XMLFileDataNode>(1U);

	this->root_node_->name = L"root";

	if (xml_doc != nullptr) {
		this->SetRootNodeRecursivePart(this->root_node_, xml_doc->first_node());
	}

	return;
}


/**
 * @brief SetRootNodeRecursivePart関数
 * @param parent_node (parent_node)
 * @param xml_node (xml_node)
 */
void tml::XMLFileData::SetRootNodeRecursivePart(const tml::shared_ptr<tml::XMLFileDataNode> &parent_node, const rapidxml::xml_node<> *xml_node)
{
	static const std::wstring newline_code_str = L"\r\n";
	static const std::wstring old_newline_code_str = L"\t";

	if (xml_node == nullptr) {
		return;
	}

	tml::shared_ptr<tml::XMLFileDataNode> child_node = tml::make_shared<tml::XMLFileDataNode>(1U);

	tml::StringUtil::GetString(child_node->name, xml_node->name());

	for (rapidxml::xml_attribute<> *xml_node_attr = xml_node->first_attribute(); xml_node_attr; xml_node_attr = xml_node_attr->next_attribute()) {
		std::pair<std::wstring, std::wstring> val;

		tml::StringUtil::GetString(val.first, xml_node_attr->name());
		tml::StringUtil::GetString(val.second, xml_node_attr->value());

		child_node->value_container.insert(val);
	}

	tml::StringUtil::GetString(child_node->string, xml_node->value());

	size_t child_node_str_index = child_node->string.find(old_newline_code_str);

	while (child_node_str_index != std::wstring::npos) {
		child_node->string.replace(child_node_str_index, old_newline_code_str.length(), newline_code_str);

		child_node_str_index = child_node->string.find(old_newline_code_str, child_node_str_index + newline_code_str.length());
	}

	parent_node->AddChildNode(child_node);

	this->SetRootNodeRecursivePart(child_node, xml_node->first_node());
	this->SetRootNodeRecursivePart(parent_node, xml_node->next_sibling());

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
 * @return result (result)<br>
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
		this->data.SetRootNode(nullptr);

		return (0);
	}

	std::wstring tmp_str;

	tml::StringUtil::Join(tmp_str, txt_file.data.line_string_container, L"");

	std::string str;

	tml::StringUtil::GetString(str, tmp_str.c_str());

	tml::DynamicBuffer xml_buf;

	xml_buf.SetSize(str.length() + sizeof(CHAR));
	xml_buf.WriteArray(reinterpret_cast<const BYTE *>(str.c_str()), str.length(), str.length());
	xml_buf.WriteChar(0);

	CHAR *xml_str = reinterpret_cast<CHAR *>(xml_buf.Get());

	tml::unique_ptr<rapidxml::xml_document<>> xml_doc = tml::make_unique<rapidxml::xml_document<>>(1U);

	try {
		xml_doc->parse<rapidxml::parse_no_data_nodes | rapidxml::parse_trim_whitespace>(xml_str);
	} catch (rapidxml::parse_error &err) {
		if (tml::ConstantUtil::LIBRARY::DEBUG_FLAG) {
			tml::Log(L"Error: XML Parse\n");

			std::cout << err.what() << std::endl;
		}

		return (-1);
	}

	this->data.SetRootNode(xml_doc.get());

	return (0);
}


/**
 * @brief Write関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::XMLFile::Write(void)
{
	static const std::wstring empty_str = L"";
	static const std::wstring header_str = L"<?xml version=\"1.0\" encoding=\"shift_jis\" ?>";

	auto write_desc_dat = this->write_desc.GetDataByParent();

	if (write_desc_dat->file_path.empty()) {
		return (-1);
	}

	tml::TextFile txt_file;

	if (this->data.GetRootNode() == nullptr) {
		return (-1);
	} else if (!this->data.GetRootNode()->GetChildNodeContainer().empty()) {
		txt_file.data.line_string_container.push_back(header_str);

		for (auto &child_node : this->data.GetRootNode()->GetChildNodeContainer()) {
			this->WriteRecursivePart(txt_file, child_node, 0U);
		}

		txt_file.data.line_string_container.push_back(empty_str);
	}

	txt_file.write_desc.parent_data = write_desc_dat;

	if (txt_file.Write() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief WriteRecursivePart関数
 * @param txt_file (text_file)
 * @param node (node)
 * @param tab_cnt (tab_count)
 */
void tml::XMLFile::WriteRecursivePart(tml::TextFile &txt_file, const tml::shared_ptr<tml::XMLFileDataNode> &node, const size_t tab_cnt)
{
	static const std::wstring tab_str = L"\t";
	static const std::wstring node_start_start_str = L"<";
	static const std::wstring node_end_start_str = L"</";
	static const std::wstring node_end_str = L">";
	static const std::wstring space_str = L" ";
	static const std::wstring equal_str = L"=";
	static const std::wstring dq_str = L"\"";

	std::wstring total_tab_str;

	for (size_t tab_i = 0U; tab_i < tab_cnt; ++tab_i) {
		total_tab_str += tab_str;
	}

	std::wstring start_line_str;
	
	start_line_str = total_tab_str;
	start_line_str += node_start_start_str;
	start_line_str += node->name;

	for (auto &val : node->value_container) {
		start_line_str += space_str;
		start_line_str += val.first;
		start_line_str += equal_str;
		start_line_str += dq_str;
		start_line_str += val.second;
		start_line_str += dq_str;
	}

	start_line_str += node_end_str;

	txt_file.data.line_string_container.push_back(start_line_str);

	if (!node->string.empty()) {
		std::wstring middle_line_str;
	
		middle_line_str = total_tab_str;
		middle_line_str += tab_str;
		middle_line_str += node->string;

		txt_file.data.line_string_container.push_back(middle_line_str);
	}

	for (auto &child_node : node->GetChildNodeContainer()) {
		this->WriteRecursivePart(txt_file, child_node, tab_cnt + 1U);
	}

	std::wstring end_line_str;

	end_line_str = total_tab_str;
	end_line_str += node_end_start_str;
	end_line_str += node->name;
	end_line_str += node_end_str;

	txt_file.data.line_string_container.push_back(end_line_str);

	return;
}
