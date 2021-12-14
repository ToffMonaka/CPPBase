/**
 * @file
 * @brief XMLFileヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantInclude_RapidXMLBase.h"
#include <map>
#include "TextFile.h"


namespace tml {
/**
 * @brief XMLFileDataNodeクラス
 */
class XMLFileDataNode
{
public: XMLFileDataNode(const tml::XMLFileDataNode &) = delete;
public: tml::XMLFileDataNode &operator =(const tml::XMLFileDataNode &) = delete;

public:
	static const tml::shared_ptr<tml::XMLFileDataNode> empty_child_node;

private:
	tml::XMLFileDataNode *parent_node_;
	std::list<tml::shared_ptr<tml::XMLFileDataNode>> child_node_cont_;

public:
	std::wstring name;
	std::map<std::wstring, std::wstring> value_container;
	std::wstring string;

private:
	void Release(void);

	const tml::shared_ptr<tml::XMLFileDataNode> &GetChildNodeRecursivePart(const std::list<tml::shared_ptr<tml::XMLFileDataNode>> &, const WCHAR *);

public:
	XMLFileDataNode();
	virtual ~XMLFileDataNode();

	virtual void Init(void);

	const std::wstring *GetValue(const WCHAR *) const;
	tml::XMLFileDataNode *GetParentNode(void);
	tml::XMLFileDataNode *GetParentNode(const WCHAR *);
	void SetParentNode(tml::XMLFileDataNode *);
	const std::list<tml::shared_ptr<tml::XMLFileDataNode>> &GetChildNodeContainer(void);
	const tml::shared_ptr<tml::XMLFileDataNode> &GetChildNode(void);
	const tml::shared_ptr<tml::XMLFileDataNode> &GetChildNode(const WCHAR *);
	INT AddChildNode(const tml::shared_ptr<tml::XMLFileDataNode> &);
	void RemoveChildNode(void);
	void RemoveChildNode(const tml::shared_ptr<tml::XMLFileDataNode> &);
	void RemoveChildNodeFromParentNode(void);
};
}


/**
 * @brief GetValue関数
 * @param val_name (value_name)
 * @return val (value)<br>
 * nullptr=失敗
 */
inline const std::wstring *tml::XMLFileDataNode::GetValue(const WCHAR *val_name) const
{
	auto val_itr = this->value_container.find(val_name);

	if (val_itr == this->value_container.end()) {
		return (nullptr);
	}

	return (&val_itr->second);
}


/**
 * @brief GetParentNode関数
 * @return parent_node (parent_node)
 */
inline tml::XMLFileDataNode *tml::XMLFileDataNode::GetParentNode(void)
{
	return (this->parent_node_);
}


/**
 * @brief GetParentNode関数
 * @param parent_node_name (parent_node_name)
 * @return parent_node (parent_node)
 */
inline tml::XMLFileDataNode *tml::XMLFileDataNode::GetParentNode(const WCHAR *parent_node_name)
{
	auto parent_node = this->parent_node_;

	while (parent_node != nullptr) {
		if (parent_node->name == parent_node_name) {
			break;
		}

		parent_node = parent_node->GetParentNode();
	}

	return (parent_node);
}


/**
 * @brief SetParentNode関数
 * @param parent_node (parent_node)
 */
inline void tml::XMLFileDataNode::SetParentNode(tml::XMLFileDataNode *parent_node)
{
	if (parent_node == this) {
		return;
	}

	this->parent_node_ = parent_node;

	return;
}


/**
 * @brief GetChildNodeContainer関数
 * @return child_node_container (child_node_container)
 */
inline const std::list<tml::shared_ptr<tml::XMLFileDataNode>> &tml::XMLFileDataNode::GetChildNodeContainer(void)
{
	return (this->child_node_cont_);
}


/**
 * @brief GetChildNode関数
 * @return child_node (child_node)<br>
 * nullptr=失敗
 */
inline const tml::shared_ptr<tml::XMLFileDataNode> &tml::XMLFileDataNode::GetChildNode(void)
{
	if (this->child_node_cont_.empty()) {
		return (this->empty_child_node);
	}

	return (this->child_node_cont_.front());
}


/**
 * @brief GetChildNode関数
 * @param child_node_name (child_node_name)
 * @return child_node (child_node)<br>
 * nullptr=失敗
 */
inline const tml::shared_ptr<tml::XMLFileDataNode> &tml::XMLFileDataNode::GetChildNode(const WCHAR *child_node_name)
{
	if ((child_node_name == nullptr)
	|| (child_node_name[0] == 0)) {
		return (this->empty_child_node);
	}

	return (this->GetChildNodeRecursivePart(this->child_node_cont_, child_node_name));
}


namespace tml {
/**
 * @brief XMLFileDataクラス
 */
class XMLFileData
{
public: XMLFileData(const tml::XMLFileData &) = delete;
public: tml::XMLFileData &operator =(const tml::XMLFileData &) = delete;

private:
	tml::shared_ptr<tml::XMLFileDataNode> root_node_;

public:

private:
	void Release(void);

	void SetRootNodeRecursivePart(const tml::shared_ptr<tml::XMLFileDataNode> &, const rapidxml::xml_node<> *);

public:
	XMLFileData();
	virtual ~XMLFileData();

	virtual void Init(void);

	const tml::shared_ptr<tml::XMLFileDataNode> &GetRootNode(void);
	void SetRootNode(const rapidxml::xml_document<> *);
};
}


/**
 * @brief GetRootNode関数
 * @return root_node (root_node)
 */
inline const tml::shared_ptr<tml::XMLFileDataNode> &tml::XMLFileData::GetRootNode(void)
{
	return (this->root_node_);
}


namespace tml {
/**
 * @brief XMLFileReadDescDataクラス
 */
class XMLFileReadDescData : public tml::TextFileReadDescData
{
public:

private:
	void Release(void);

public:
	XMLFileReadDescData();
	virtual ~XMLFileReadDescData();

	virtual void Init(void);
};

using XMLFileReadDesc = tml::FileReadDesc<tml::XMLFileReadDescData>;
}


/**
 * @brief Release関数
 */
inline void tml::XMLFileReadDescData::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief XMLFileWriteDescDataクラス
 */
class XMLFileWriteDescData : public tml::TextFileWriteDescData
{
public:

private:
	void Release(void);

public:
	XMLFileWriteDescData();
	virtual ~XMLFileWriteDescData();

	virtual void Init(void);
};

using XMLFileWriteDesc = tml::FileWriteDesc<tml::XMLFileWriteDescData>;
}


/**
 * @brief Release関数
 */
inline void tml::XMLFileWriteDescData::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief XMLFileクラス
 */
class XMLFile : public tml::File
{
public: XMLFile(const tml::XMLFile &) = delete;
public: tml::XMLFile &operator =(const tml::XMLFile &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	tml::XMLFileData data;
	tml::XMLFileReadDesc read_desc;
	tml::XMLFileWriteDesc write_desc;

private:
	void WriteRecursivePart(tml::TextFile &, const tml::shared_ptr<tml::XMLFileDataNode> &, const size_t);

private:
	void Release(void);

public:
	XMLFile();
	virtual ~XMLFile();

	virtual void Init(void);

	virtual INT Read(void);
	virtual INT Write(void);
};
}


/**
 * @brief Release関数
 */
inline void tml::XMLFile::Release(void)
{
	return;
}
