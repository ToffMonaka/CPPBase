/**
 * @file
 * @brief Node�R�[�h�t�@�C��
 */


#include "Node.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
cpp_base::scene::NodeDesc::NodeDesc() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::scene::NodeDesc::~NodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::scene::NodeDesc::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	tml::scene::NodeDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param ini_file (ini_file)
 * @return result (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::NodeDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::scene::NodeDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Node Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"NODE");

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
void cpp_base::scene::NodeDesc::SetManager(cpp_base::scene::Manager *mgr)
{
	this->mgr_ = mgr;

	tml::scene::NodeDesc::SetManager(mgr);

	return;
}


/**
 * @brief �R���X�g���N�^
 */
cpp_base::scene::Node::Node() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::scene::Node::~Node()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void cpp_base::scene::Node::Release(void)
{
	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::scene::Node::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	tml::scene::Node::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::Node::Create(const cpp_base::scene::NodeDesc &desc)
{
	if (desc.GetManager() == nullptr) {
		this->Init();

		return (-1);
	}

	this->Init();

	if (tml::scene::Node::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	this->mgr_ = desc.GetManager();

	return (0);
}


/**
 * @brief OnStart�֐�
 * @return result (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::Node::OnStart(void)
{
	return (0);
}


/**
 * @brief OnEnd�֐�
 */
void cpp_base::scene::Node::OnEnd(void)
{
	return;
}


/**
 * @brief OnUpdate�֐�
 */
void cpp_base::scene::Node::OnUpdate(void)
{
	return;
}
