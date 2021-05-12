/**
 * @file
 * @brief Manager�R�[�h�t�@�C��
 */


#include "Manager.h"
#include "../input/Manager.h"
#include "../graphic/Manager.h"
#include "../sound/Manager.h"


/**
 * @brief �R���X�g���N�^
 */
cpp_base::scene::ManagerDesc::ManagerDesc() :
	input_manager2(nullptr),
	graphic_manager2(nullptr),
	sound_manager2(nullptr)

{
	this->InitResourceCount();
	this->InitEventCount();

	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::scene::ManagerDesc::~ManagerDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::scene::ManagerDesc::Init(void)
{
	this->Release();

	this->input_manager2 = nullptr;
	this->graphic_manager2 = nullptr;
	this->sound_manager2 = nullptr;

	tml::scene::ManagerDesc::Init();

	this->InitResourceCount();
	this->InitEventCount();

	return;
}


/**
 * @brief InitResourceCount�֐�
 */
void cpp_base::scene::ManagerDesc::InitResourceCount(void)
{
	tml::scene::ManagerDesc::InitResourceCount();

	return;
}


/**
 * @brief InitEventCount�֐�
 */
void cpp_base::scene::ManagerDesc::InitEventCount(void)
{
	tml::scene::ManagerDesc::InitEventCount();

	return;
}


/**
 * @brief SetInputManager�֐�
 * @param input_mgr (input_manager)
 */
void cpp_base::scene::ManagerDesc::SetInputManager(cpp_base::input::Manager *input_mgr)
{
	this->input_manager = input_mgr;
	this->input_manager2 = input_mgr;

	return;
}


/**
 * @brief SetGraphicManager�֐�
 * @param graphic_mgr (graphic_manager)
 */
void cpp_base::scene::ManagerDesc::SetGraphicManager(cpp_base::graphic::Manager *graphic_mgr)
{
	this->graphic_manager = graphic_mgr;
	this->graphic_manager2 = graphic_mgr;

	return;
}


/**
 * @brief SetSoundManager�֐�
 * @param sound_mgr (sound_manager)
 */
void cpp_base::scene::ManagerDesc::SetSoundManager(cpp_base::sound::Manager *sound_mgr)
{
	this->sound_manager = sound_mgr;
	this->sound_manager2 = sound_mgr;

	return;
}


/**
 * @brief �R���X�g���N�^
 */
cpp_base::scene::Manager::Manager() :
	input_mgr2_(nullptr),
	graphic_mgr2_(nullptr),
	sound_mgr2_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::scene::Manager::~Manager()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void cpp_base::scene::Manager::Release(void)
{
	this->DeleteCommon2();

	tml::scene::Manager::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::scene::Manager::Init(void)
{
	this->Release();

	this->input_mgr2_ = nullptr;
	this->graphic_mgr2_ = nullptr;
	this->sound_mgr2_ = nullptr;

	tml::scene::Manager::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::Manager::Create(const cpp_base::scene::ManagerDesc &desc)
{
	if ((desc.input_manager2 != desc.input_manager)
	|| (desc.graphic_manager2 != desc.graphic_manager)
	|| (desc.sound_manager2 != desc.sound_manager)) {
		this->Init();

		return (-1);
	}

	this->Init();

	if (tml::scene::Manager::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	this->input_mgr2_ = desc.input_manager2;
	this->graphic_mgr2_ = desc.graphic_manager2;
	this->sound_mgr2_ = desc.sound_manager2;

	if (this->CreateCommon2() < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief CreateCommon2�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::Manager::CreateCommon2(void)
{
	if (this->common2.Create(this) < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief DeleteCommon2�֐�
 */
void cpp_base::scene::Manager::DeleteCommon2(void)
{
	this->common2.Init();

	return;
}
