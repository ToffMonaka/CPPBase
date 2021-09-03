/**
 * @file
 * @brief Managerコードファイル
 */


#include "Manager.h"
#include "../input/Manager.h"
#include "../graphic/Manager.h"
#include "../sound/Manager.h"
#include "Scene.h"
#include "InitScene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "StageScene.h"
#include "Node.h"
#include "DebugNode.h"
#include "Test2DStageNode.h"
#include "Field2DNode.h"
#include "Field2DGroundNode.h"
#include "Field2DPlayerNode.h"
#include "Field2DMobNode.h"


/**
 * @brief コンストラクタ
 */
cpp_base::scene::ManagerDesc::ManagerDesc() :
	input_mgr_(nullptr),
	graphic_mgr_(nullptr),
	sound_mgr_(nullptr)
{
	this->InitResourceCount();
	this->InitEventCount();

	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::ManagerDesc::~ManagerDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::ManagerDesc::Init(void)
{
	this->Release();

	this->input_mgr_ = nullptr;
	this->graphic_mgr_ = nullptr;
	this->sound_mgr_ = nullptr;

	tml::scene::ManagerDesc::Init();

	this->InitResourceCount();
	this->InitEventCount();

	return;
}


/**
 * @brief InitResourceCount関数
 */
void cpp_base::scene::ManagerDesc::InitResourceCount(void)
{
	tml::scene::ManagerDesc::InitResourceCount();

	this->resource_count_container.resize(cpp_base::ConstantUtil::SCENE::RESOURCE_TYPE_COUNT);

	return;
}


/**
 * @brief InitEventCount関数
 */
void cpp_base::scene::ManagerDesc::InitEventCount(void)
{
	tml::scene::ManagerDesc::InitEventCount();

	this->event_count_container.resize(cpp_base::ConstantUtil::SCENE::EVENT_TYPE_COUNT);

	return;
}


/**
 * @brief SetInputManager関数
 * @param input_mgr (input_manager)
 */
void cpp_base::scene::ManagerDesc::SetInputManager(cpp_base::input::Manager *input_mgr)
{
	this->input_mgr_ = input_mgr;

	tml::scene::ManagerDesc::SetInputManager(input_mgr);

	return;
}


/**
 * @brief SetGraphicManager関数
 * @param graphic_mgr (graphic_manager)
 */
void cpp_base::scene::ManagerDesc::SetGraphicManager(cpp_base::graphic::Manager *graphic_mgr)
{
	this->graphic_mgr_ = graphic_mgr;

	tml::scene::ManagerDesc::SetGraphicManager(graphic_mgr);

	return;
}


/**
 * @brief SetSoundManager関数
 * @param sound_mgr (sound_manager)
 */
void cpp_base::scene::ManagerDesc::SetSoundManager(cpp_base::sound::Manager *sound_mgr)
{
	this->sound_mgr_ = sound_mgr;

	tml::scene::ManagerDesc::SetSoundManager(sound_mgr);

	return;
}


/**
 * @brief コンストラクタ
 */
cpp_base::scene::Manager::Manager() :
	input_mgr_(nullptr),
	graphic_mgr_(nullptr),
	sound_mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::Manager::~Manager()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::scene::Manager::Release(void)
{
	this->common2.Init();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::Manager::Init(void)
{
	this->Release();

	this->input_mgr_ = nullptr;
	this->graphic_mgr_ = nullptr;
	this->sound_mgr_ = nullptr;

	tml::scene::Manager::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Manager::Create(const cpp_base::scene::ManagerDesc &desc)
{
	if ((desc.GetInputManager() == nullptr)
	|| (desc.GetGraphicManager() == nullptr)
	|| (desc.GetSoundManager() == nullptr)) {
		this->Init();

		return (-1);
	}

	this->Init();

	if (tml::scene::Manager::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	this->input_mgr_ = desc.GetInputManager();
	this->graphic_mgr_ = desc.GetGraphicManager();
	this->sound_mgr_ = desc.GetSoundManager();

	{// ResourceFactory Set
		this->factory->AddResourceFunction(tml::ConstantUtil::SCENE::CLASS_NAME::SCENE,
			[this] (const tml::INIFileReadDesc &conf_file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::ManagerResource> {
				tml::shared_ptr<tml::ManagerResource> res;

				cpp_base::scene::SceneDesc desc;

				desc.SetManager(this);
				desc.Read(conf_file_read_desc);

				if (this->GetResource<cpp_base::scene::Scene>(res, desc, dst_result) == nullptr) {
					return (res);
				}

				return (res);
			}
		);

		this->factory->AddResourceFunction(cpp_base::ConstantUtil::SCENE::CLASS_NAME::INIT_SCENE,
			[this] (const tml::INIFileReadDesc &conf_file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::ManagerResource> {
				tml::shared_ptr<tml::ManagerResource> res;

				cpp_base::scene::InitSceneDesc desc;

				desc.SetManager(this);
				desc.Read(conf_file_read_desc);

				if (this->GetResource<cpp_base::scene::InitScene>(res, desc, dst_result) == nullptr) {
					return (res);
				}

				return (res);
			}
		);

		this->factory->AddResourceFunction(cpp_base::ConstantUtil::SCENE::CLASS_NAME::TITLE_SCENE,
			[this] (const tml::INIFileReadDesc &conf_file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::ManagerResource> {
				tml::shared_ptr<tml::ManagerResource> res;

				cpp_base::scene::TitleSceneDesc desc;

				desc.SetManager(this);
				desc.Read(conf_file_read_desc);

				if (this->GetResource<cpp_base::scene::TitleScene>(res, desc, dst_result) == nullptr) {
					return (res);
				}

				return (res);
			}
		);

		this->factory->AddResourceFunction(cpp_base::ConstantUtil::SCENE::CLASS_NAME::SELECT_SCENE,
			[this] (const tml::INIFileReadDesc &conf_file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::ManagerResource> {
				tml::shared_ptr<tml::ManagerResource> res;

				cpp_base::scene::SelectSceneDesc desc;

				desc.SetManager(this);
				desc.Read(conf_file_read_desc);

				if (this->GetResource<cpp_base::scene::SelectScene>(res, desc, dst_result) == nullptr) {
					return (res);
				}

				return (res);
			}
		);

		this->factory->AddResourceFunction(cpp_base::ConstantUtil::SCENE::CLASS_NAME::STAGE_SCENE,
			[this] (const tml::INIFileReadDesc &conf_file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::ManagerResource> {
				tml::shared_ptr<tml::ManagerResource> res;

				cpp_base::scene::StageSceneDesc desc;

				desc.SetManager(this);
				desc.Read(conf_file_read_desc);

				if (this->GetResource<cpp_base::scene::StageScene>(res, desc, dst_result) == nullptr) {
					return (res);
				}

				return (res);
			}
		);

		this->factory->AddResourceFunction(tml::ConstantUtil::SCENE::CLASS_NAME::NODE,
			[this] (const tml::INIFileReadDesc &conf_file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::ManagerResource> {
				tml::shared_ptr<tml::ManagerResource> res;

				cpp_base::scene::NodeDesc desc;

				desc.SetManager(this);
				desc.Read(conf_file_read_desc);

				if (this->GetResource<cpp_base::scene::Node>(res, desc, dst_result) == nullptr) {
					return (res);
				}

				return (res);
			}
		);

		this->factory->AddResourceFunction(cpp_base::ConstantUtil::SCENE::CLASS_NAME::TEST_2D_STAGE_NODE,
			[this] (const tml::INIFileReadDesc &conf_file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::ManagerResource> {
				tml::shared_ptr<tml::ManagerResource> res;

				cpp_base::scene::Test2DStageNodeDesc desc;

				desc.SetManager(this);
				desc.Read(conf_file_read_desc);

				if (this->GetResource<cpp_base::scene::Test2DStageNode>(res, desc, dst_result) == nullptr) {
					return (res);
				}

				return (res);
			}
		);

		this->factory->AddResourceFunction(cpp_base::ConstantUtil::SCENE::CLASS_NAME::FIELD_2D_NODE,
			[this] (const tml::INIFileReadDesc &conf_file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::ManagerResource> {
				tml::shared_ptr<tml::ManagerResource> res;

				cpp_base::scene::Field2DNodeDesc desc;

				desc.SetManager(this);
				desc.Read(conf_file_read_desc);

				if (this->GetResource<cpp_base::scene::Field2DNode>(res, desc, dst_result) == nullptr) {
					return (res);
				}

				return (res);
			}
		);

		this->factory->AddResourceFunction(cpp_base::ConstantUtil::SCENE::CLASS_NAME::FIELD_2D_GROUND_NODE,
			[this] (const tml::INIFileReadDesc &conf_file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::ManagerResource> {
				tml::shared_ptr<tml::ManagerResource> res;

				cpp_base::scene::Field2DGroundNodeDesc desc;

				desc.SetManager(this);
				desc.Read(conf_file_read_desc);

				if (this->GetResource<cpp_base::scene::Field2DGroundNode>(res, desc, dst_result) == nullptr) {
					return (res);
				}

				return (res);
			}
		);

		this->factory->AddResourceFunction(cpp_base::ConstantUtil::SCENE::CLASS_NAME::FIELD_2D_PLAYER_NODE,
			[this] (const tml::INIFileReadDesc &conf_file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::ManagerResource> {
				tml::shared_ptr<tml::ManagerResource> res;

				cpp_base::scene::Field2DPlayerNodeDesc desc;

				desc.SetManager(this);
				desc.Read(conf_file_read_desc);

				if (this->GetResource<cpp_base::scene::Field2DPlayerNode>(res, desc, dst_result) == nullptr) {
					return (res);
				}

				return (res);
			}
		);

		this->factory->AddResourceFunction(cpp_base::ConstantUtil::SCENE::CLASS_NAME::FIELD_2D_MOB_NODE,
			[this] (const tml::INIFileReadDesc &conf_file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::ManagerResource> {
				tml::shared_ptr<tml::ManagerResource> res;

				cpp_base::scene::Field2DMobNodeDesc desc;

				desc.SetManager(this);
				desc.Read(conf_file_read_desc);

				if (this->GetResource<cpp_base::scene::Field2DMobNode>(res, desc, dst_result) == nullptr) {
					return (res);
				}

				return (res);
			}
		);
	}

	{// EventFactory Set
	}

	if (this->common2.Create(this) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
