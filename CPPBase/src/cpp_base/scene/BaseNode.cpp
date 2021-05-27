/**
 * @file
 * @brief BaseNode�R�[�h�t�@�C��
 */


#include "BaseNode.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
cpp_base::scene::BaseNodeDesc::BaseNodeDesc() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::scene::BaseNodeDesc::~BaseNodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::scene::BaseNodeDesc::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	tml::scene::BaseNodeDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::BaseNodeDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::scene::BaseNodeDesc::ReadValue(ini_file) < 0) {
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
 * @brief SetManager�֐�
 * @param mgr (manager)
 */
void cpp_base::scene::BaseNodeDesc::SetManager(cpp_base::scene::Manager *mgr)
{
	this->mgr_ = mgr;

	tml::scene::BaseNodeDesc::SetManager(mgr);

	return;
}


/**
 * @brief �R���X�g���N�^
 */
cpp_base::scene::BaseNode::BaseNode() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::scene::BaseNode::~BaseNode()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void cpp_base::scene::BaseNode::Release(void)
{
	tml::scene::BaseNode::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::scene::BaseNode::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	tml::scene::BaseNode::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::BaseNode::Create(const cpp_base::scene::BaseNodeDesc &desc)
{
	if (desc.GetManager() == nullptr) {
		this->Init();

		return (-1);
	}

	this->Init();

	if (tml::scene::BaseNode::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	this->mgr_ = desc.GetManager();

	return (0);
}
