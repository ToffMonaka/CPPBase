/**
 * @file
 * @brief XMLFile�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantInclude_RapidXMLBase.h"
#include "TextFile.h"
#include "XMLFileNode.h"


namespace tml {
/**
 * @brief XMLFileData�N���X
 */
class XMLFileData
{
public: XMLFileData(const tml::XMLFileData &) = delete;
public: tml::XMLFileData &operator =(const tml::XMLFileData &) = delete;

private:
	tml::shared_ptr<tml::XMLFileNode> root_node_;

public:

private:
	void Release(void);

	void SetRootNodeRecursivePart(const tml::shared_ptr<tml::XMLFileNode> &, const rapidxml::xml_node<> *);

public:
	XMLFileData();
	virtual ~XMLFileData();

	virtual void Init(void);

	const tml::shared_ptr<tml::XMLFileNode> &GetRootNode(void);
	void SetRootNode(const rapidxml::xml_document<> *);
};
}


/**
 * @brief GetRootNode�֐�
 * @return root_node (root_node)
 */
inline const tml::shared_ptr<tml::XMLFileNode> &tml::XMLFileData::GetRootNode(void)
{
	return (this->root_node_);
}


namespace tml {
/**
 * @brief XMLFileReadDescData�N���X
 */
class XMLFileReadDescData : public tml::TextFileReadDescData
{
protected: virtual void InterfaceDummy(void) {return;};

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
 * @brief Release�֐�
 */
inline void tml::XMLFileReadDescData::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief XMLFileWriteDescData�N���X
 */
class XMLFileWriteDescData : public tml::TextFileWriteDescData
{
protected: virtual void InterfaceDummy(void) {return;};

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
 * @brief Release�֐�
 */
inline void tml::XMLFileWriteDescData::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief XMLFile�N���X
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
	void Release(void);

	void WriteRecursivePart(tml::TextFile &, const tml::shared_ptr<tml::XMLFileNode> &, const size_t);

protected:
	virtual INT OnRead(void);
	virtual INT OnWrite(void);

public:
	XMLFile();
	virtual ~XMLFile();

	virtual void Init(void);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::XMLFile::Release(void)
{
	return;
}
