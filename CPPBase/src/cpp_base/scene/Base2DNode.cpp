/**
 * @file
 * @brief Base2DNode�R�[�h�t�@�C��
 */


#include "Base2DNode.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
cpp_base::scene::Base2DNodeDesc::Base2DNodeDesc() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::scene::Base2DNodeDesc::~Base2DNodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::scene::Base2DNodeDesc::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	tml::scene::Base2DNodeDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::Base2DNodeDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::scene::Base2DNodeDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Base2DNode Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"BASE_2D_NODE");

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
void cpp_base::scene::Base2DNodeDesc::SetManager(cpp_base::scene::Manager *mgr)
{
	this->mgr_ = mgr;

	tml::scene::Base2DNodeDesc::SetManager(mgr);

	return;
}


/**
 * @brief �R���X�g���N�^
 */
cpp_base::scene::Base2DNode::Base2DNode() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::scene::Base2DNode::~Base2DNode()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void cpp_base::scene::Base2DNode::Release(void)
{
	tml::scene::Base2DNode::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::scene::Base2DNode::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	tml::scene::Base2DNode::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::Base2DNode::Create(const cpp_base::scene::Base2DNodeDesc &desc)
{
	if (desc.GetManager() == nullptr) {
		this->Init();

		return (-1);
	}

	this->Init();

	if (tml::scene::Base2DNode::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	this->mgr_ = desc.GetManager();

	return (0);
}
