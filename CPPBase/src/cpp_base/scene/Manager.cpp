/**
 * @file
 * @brief Managerコードファイル
 */


#include "Manager.h"
#include "../input/Manager.h"
#include "../graphic/Manager.h"
#include "../sound/Manager.h"
#include "BaseScene.h"
#include "InitScene.h"
#include "TitleScene.h"
#include "BaseNode.h"
#include "InitSceneNode.h"
#include "TitleSceneNode.h"


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

	return;
}


/**
 * @brief InitEventCount関数
 */
void cpp_base::scene::ManagerDesc::InitEventCount(void)
{
	tml::scene::ManagerDesc::InitEventCount();

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
	this->DeleteCommon2();

	tml::scene::Manager::Release();

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
 * @return res (result)<br>
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

	{// Factory Set
		this->scene_factory_by_ini_file.AddFunction(L"BaseScene",
			[this] (const tml::INIFileReadDesc &file_read_desc) -> tml::shared_ptr<tml::scene::Scene> {
				tml::shared_ptr<tml::scene::Scene> scene;

				cpp_base::scene::BaseSceneDesc desc;

				desc.SetManager(this);
				desc.Read(file_read_desc);

				if (this->GetResource<cpp_base::scene::BaseScene>(scene, desc) == nullptr) {
					return (scene);
				}

				return (scene);
			}
		);

		this->scene_factory_by_ini_file.AddFunction(L"InitScene",
			[this] (const tml::INIFileReadDesc &file_read_desc) -> tml::shared_ptr<tml::scene::Scene> {
				tml::shared_ptr<tml::scene::Scene> scene;

				cpp_base::scene::InitSceneDesc desc;

				desc.SetManager(this);
				desc.Read(file_read_desc);

				if (this->GetResource<cpp_base::scene::InitScene>(scene, desc) == nullptr) {
					return (scene);
				}

				return (scene);
			}
		);

		this->scene_factory_by_ini_file.AddFunction(L"TitleScene",
			[this] (const tml::INIFileReadDesc &file_read_desc) -> tml::shared_ptr<tml::scene::Scene> {
				tml::shared_ptr<tml::scene::Scene> scene;

				cpp_base::scene::TitleSceneDesc desc;

				desc.SetManager(this);
				desc.Read(file_read_desc);

				if (this->GetResource<cpp_base::scene::TitleScene>(scene, desc) == nullptr) {
					return (scene);
				}

				return (scene);
			}
		);

		this->node_factory_by_ini_file.AddFunction(L"BaseNode",
			[this] (const tml::INIFileReadDesc &file_read_desc) -> tml::shared_ptr<tml::scene::Node> {
				tml::shared_ptr<tml::scene::Node> node;

				cpp_base::scene::BaseNodeDesc desc;

				desc.SetManager(this);
				desc.Read(file_read_desc);

				if (this->GetResource<cpp_base::scene::BaseNode>(node, desc) == nullptr) {
					return (node);
				}

				return (node);
			}
		);

		this->node_factory_by_ini_file.AddFunction(L"InitSceneNode",
			[this] (const tml::INIFileReadDesc &file_read_desc) -> tml::shared_ptr<tml::scene::Node> {
				tml::shared_ptr<tml::scene::Node> node;

				cpp_base::scene::InitSceneNodeDesc desc;

				desc.SetManager(this);
				desc.Read(file_read_desc);

				if (this->GetResource<cpp_base::scene::InitSceneNode>(node, desc) == nullptr) {
					return (node);
				}

				return (node);
			}
		);

		this->node_factory_by_ini_file.AddFunction(L"TitleSceneNode",
			[this] (const tml::INIFileReadDesc &file_read_desc) -> tml::shared_ptr<tml::scene::Node> {
				tml::shared_ptr<tml::scene::Node> node;

				cpp_base::scene::TitleSceneNodeDesc desc;

				desc.SetManager(this);
				desc.Read(file_read_desc);

				if (this->GetResource<cpp_base::scene::TitleSceneNode>(node, desc) == nullptr) {
					return (node);
				}

				return (node);
			}
		);
	}

	if (this->CreateCommon2() < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief CreateCommon2関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Manager::CreateCommon2(void)
{
	if (this->common2.Create(this) < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief DeleteCommon2関数
 */
void cpp_base::scene::Manager::DeleteCommon2(void)
{
	this->common2.Init();

	return;
}
