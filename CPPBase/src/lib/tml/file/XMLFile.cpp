/**
 * @file
 * @brief XMLFileコードファイル
 */


#include "XMLFile.h"
#include "../string/StringUtil.h"


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
 * @brief SetParentNode関数
 * @param parent_node (parent_node)
 */
void tml::XMLFileDataNode::SetParentNode(tml::XMLFileDataNode *parent_node)
{
	if (parent_node == this) {
		return;
	}

	this->parent_node_ = parent_node;

	return;
}


/**
 * @brief AddChildNode関数
 * @param child_node (child_node)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::XMLFileDataNode::AddChildNode(tml::shared_ptr<tml::XMLFileDataNode> &child_node)
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
 * @param child_node (child_node)
 */
void tml::XMLFileDataNode::RemoveChildNode(tml::shared_ptr<tml::XMLFileDataNode> &child_node)
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
	this->root_node_.reset();

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
 * @param xml_doc (xml_document)
 */
void tml::XMLFileData::SetRootNodeRecursivePart(tml::shared_ptr<tml::XMLFileDataNode> &parent_node, const rapidxml::xml_node<> *xml_node)
{
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

	std::wstring tmp_file_str;

	tml::StringUtil::Join(tmp_file_str, txt_file.data.line_string_container, L"");

	std::string file_str;

	tml::StringUtil::GetString(file_str, tmp_file_str.c_str());

	tml::DynamicBuffer xml_buf;

	xml_buf.SetSize(file_str.length() + sizeof(CHAR));
	xml_buf.WriteArray(reinterpret_cast<const BYTE *>(file_str.c_str()), file_str.length(), file_str.length());
	xml_buf.WriteCHAR(0);

	CHAR *xml_str = reinterpret_cast<CHAR *>(xml_buf.Get());

	tml::unique_ptr<rapidxml::xml_document<>> xml_doc = tml::make_unique<rapidxml::xml_document<>>(1U);

	try {
		xml_doc->parse<rapidxml::parse_no_data_nodes | rapidxml::parse_trim_whitespace>(xml_str);
	} catch (rapidxml::parse_error &err) {
		std::cout << err.what() << std::endl;

		return (-1);
	}

	this->data.SetRootNode(xml_doc.get());

	if (this->data.GetRootrNode() == nullptr) {
		return (-1);
	}

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

	if (!this->data.GetRootrNode()->GetChildNodeContainer().empty()) {
	}

	txt_file.write_desc.parent_data = write_desc_dat;

	if (txt_file.Write() < 0) {
		return (-1);
	}

	return (0);
}
