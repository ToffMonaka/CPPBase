/**
 * @file
 * @brief Object2DNodeコードファイル
 */


#include "Object2DNode.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::scene::Object2DNodeDesc::Object2DNodeDesc() :
	size(0.0f),
	scale(1.0f),
	color(1.0f)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::Object2DNodeDesc::~Object2DNodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::Object2DNodeDesc::Init(void)
{
	this->Release();

	this->position.Init();
	this->size = 0.0f;
	this->scale = 1.0f;
	this->color = 1.0f;

	tml::scene::NodeDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::scene::Object2DNodeDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::scene::NodeDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Object2DNode Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"OBJ_2D_NODE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::scene::Object2DNode::Object2DNode() :
	size(0.0f),
	scale(1.0f),
	color(1.0f)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::Object2DNode::~Object2DNode()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::scene::Object2DNode::Release(void)
{
	tml::scene::Node::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::Object2DNode::Init(void)
{
	this->Release();

	this->position.Init();
	this->size = 0.0f;
	this->scale = 1.0f;
	this->color = 1.0f;

	tml::scene::Node::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::scene::Object2DNode::Create(const tml::scene::Object2DNodeDesc &desc)
{
	this->Init();

	if (tml::scene::Node::Create(desc, tml::ConstantUtil::SCENE::NODE_TYPE::OBJECT_2D) < 0) {
		this->Init();

		return (-1);
	}

	this->position = desc.position;
	this->size = desc.size;
	this->scale = desc.scale;
	this->color = desc.color;

	return (0);
}
