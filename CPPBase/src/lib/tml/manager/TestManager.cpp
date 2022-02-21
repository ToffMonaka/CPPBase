/**
 * @file
 * @brief Manager�R�[�h�t�@�C��
 */


#include "TestManager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::test::ManagerDesc::ManagerDesc() :
	window_handle(nullptr),
	window_device_context_handle(nullptr),
	factory(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::test::ManagerDesc::~ManagerDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::test::ManagerDesc::Init(void)
{
	this->Release();

	this->window_handle = nullptr;
	this->window_device_context_handle = nullptr;
	this->factory = nullptr;

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::test::Manager::Manager() :
	wnd_handle_(nullptr),
	wnd_dc_handle_(nullptr),
	factory(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::test::Manager::~Manager()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::test::Manager::Release(void)
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::test::Manager::Init(void)
{
	this->Release();

	this->wnd_handle_ = nullptr;
	this->wnd_dc_handle_ = nullptr;
	this->factory = nullptr;

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::test::Manager::Create(const tml::test::ManagerDesc &desc)
{
	if ((desc.window_handle == nullptr)
	|| (desc.window_device_context_handle == nullptr)
	|| (desc.factory == nullptr)) {
		return (-1);
	}

	this->wnd_handle_ = desc.window_handle;
	this->wnd_dc_handle_ = desc.window_device_context_handle;
	this->factory = desc.factory;

	return (0);
}


/**
 * @brief Update�֐�
 */
void tml::test::Manager::Update(void)
{
	return;
}
