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

private:
	tml::XMLFileDataNode *parent_node_;
	std::list<tml::shared_ptr<tml::XMLFileDataNode>> child_node_cont_;

public:
	std::wstring name;
	std::map<std::wstring, std::wstring> value_container;
	std::wstring string;

protected:
	void Release(void);

public:
	XMLFileDataNode();
	virtual ~XMLFileDataNode();

	virtual void Init(void);

	tml::XMLFileDataNode *GetParentNode(void);
	void SetParentNode(tml::XMLFileDataNode *);
	const std::list<tml::shared_ptr<tml::XMLFileDataNode>> &GetChildNodeContainer(void);
	INT AddChildNode(tml::shared_ptr<tml::XMLFileDataNode> &);
	void RemoveChildNode(tml::shared_ptr<tml::XMLFileDataNode> &);
};
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
 * @brief GetChildNodeContainer関数
 * @return child_node_container (child_node_container)
 */
inline const std::list<tml::shared_ptr<tml::XMLFileDataNode>> &tml::XMLFileDataNode::GetChildNodeContainer(void)
{
	return (this->child_node_cont_);
}


namespace tml {
/**
 * @brief XMLFileDataクラス
 */
class XMLFileData
{
public:
	tml::shared_ptr<tml::XMLFileDataNode> root_node;

protected:
	void Release(void);

private:
	void SetRootNodeRecursivePart(tml::shared_ptr<tml::XMLFileDataNode> &, rapidxml::xml_node<> *);

public:
	XMLFileData();
	virtual ~XMLFileData();

	virtual void Init(void);

	void SetRootNode(const rapidxml::xml_document<> &);
};
}


namespace tml {
/**
 * @brief XMLFileReadDescDataクラス
 */
class XMLFileReadDescData : public tml::TextFileReadDescData
{
public:

protected:
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
	tml::TextFileReadDescData::Release();

	return;
}


namespace tml {
/**
 * @brief XMLFileWriteDescDataクラス
 */
class XMLFileWriteDescData : public tml::TextFileWriteDescData
{
public:

protected:
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
	tml::TextFileWriteDescData::Release();

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

protected:
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
	tml::File::Release();

	return;
}
