/**
 * @file
 * @brief Manager�R�[�h�t�@�C��
 */


#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::input::ManagerDesc::ManagerDesc()
{
	this->InitResourceCount();
	this->InitEventCount();

	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::input::ManagerDesc::~ManagerDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::input::ManagerDesc::Init(void)
{
	this->Release();

	tml::ManagerDesc::Init();

	this->InitResourceCount();
	this->InitEventCount();

	return;
}


/**
 * @brief InitResourceCount�֐�
 */
void tml::input::ManagerDesc::InitResourceCount(void)
{
	tml::ManagerDesc::InitResourceCount();

	this->resource_count_container.resize(tml::ConstantUtil::INPUT::RESOURCE_TYPE_COUNT);

	return;
}


/**
 * @brief InitEventCount�֐�
 */
void tml::input::ManagerDesc::InitEventCount(void)
{
	tml::ManagerDesc::InitEventCount();

	this->event_count_container.resize(tml::ConstantUtil::INPUT::EVENT_TYPE_COUNT);
	this->event_count_container[static_cast<UINT>(tml::ConstantUtil::INPUT::EVENT_TYPE::DEVICE)] = tml::ConstantUtil::INPUT::DEVICE_EVENT_TYPE_COUNT;

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::input::Manager::Manager() :
	mouse_device_pos_(0),
	mouse_device_code_stat_ary_{},
	keyboard_device_code_stat_ary_{}
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::input::Manager::~Manager()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::input::Manager::Release(void)
{
	this->DeleteCommon();
	this->DeleteResourceContainer();

	tml::Manager::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::input::Manager::Init(void)
{
	this->Release();

	this->mouse_device_pos_ = 0;
	this->mouse_device_code_stat_ary_.fill(false);
	this->keyboard_device_code_stat_ary_.fill(false);

	tml::Manager::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::input::Manager::Create(const tml::input::ManagerDesc &desc)
{
	this->Init();

	if (tml::Manager::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	POINT mouse_device_sys_pos;

	GetCursorPos(&mouse_device_sys_pos);
	ScreenToClient(this->GetWindowHandle(), &mouse_device_sys_pos);

	this->mouse_device_pos_ = tml::XMINT2EX(mouse_device_sys_pos.x, mouse_device_sys_pos.y);

	{// Factory Set
	}

	if (this->CreateCommon() < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief Update�֐�
 */
void tml::input::Manager::Update(void)
{
	tml::Manager::Update();

	return;
}


/**
 * @brief CreateCommon�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::input::Manager::CreateCommon(void)
{
	if (this->common.Create(this) < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief DeleteCommon�֐�
 */
void tml::input::Manager::DeleteCommon(void)
{
	this->common.Init();

	return;
}
