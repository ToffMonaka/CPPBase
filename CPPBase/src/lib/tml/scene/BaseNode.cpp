/**
 * @file
 * @brief BaseNode�R�[�h�t�@�C��
 */


#include "BaseNode.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::scene::BaseNodeDesc::BaseNodeDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::scene::BaseNodeDesc::~BaseNodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::scene::BaseNodeDesc::Init(void)
{
	this->Release();

	tml::scene::NodeDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param ini_file (ini_file)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::scene::BaseNodeDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::scene::NodeDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// BaseNode Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"BASE_NODE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief �R���X�g���N�^
 */
tml::scene::BaseNode::BaseNode()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::scene::BaseNode::~BaseNode()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::scene::BaseNode::Release(void)
{
	tml::scene::Node::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::scene::BaseNode::Init(void)
{
	this->Release();

	tml::scene::Node::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::scene::BaseNode::Create(const tml::scene::BaseNodeDesc &desc)
{
	this->Init();

	if (tml::scene::Node::Create(desc, tml::ConstantUtil::SCENE::NODE_TYPE::BASE) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief OnStart�֐�
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::scene::BaseNode::OnStart(void)
{
	return (0);
}


/**
 * @brief OnEnd�֐�
 */
void tml::scene::BaseNode::OnEnd(void)
{
	return;
}


/**
 * @brief OnUpdate�֐�
 */
void tml::scene::BaseNode::OnUpdate(void)
{
	return;
}
