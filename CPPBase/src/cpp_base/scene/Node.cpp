/**
 * @file
 * @brief Nodeコードファイル
 */


#include "Node.h"
#include "../input/Manager.h"
#include "../graphic/Manager.h"
#include "../sound/Manager.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
cpp_base::scene::NodeDesc::NodeDesc() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::NodeDesc::~NodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::NodeDesc::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	tml::scene::NodeDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::NodeDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::scene::NodeDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Node Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"NODE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief OnSetManager関数
 * @param mgr (manager)
 */
void cpp_base::scene::NodeDesc::OnSetManager(tml::Manager *mgr)
{
	this->mgr_ = dynamic_cast<cpp_base::scene::Manager *>(mgr);

	tml::scene::NodeDesc::OnSetManager(this->mgr_);

	return;
}


/**
 * @brief コンストラクタ
 */
cpp_base::scene::Node::Node() :
	desc_(nullptr),
	mgr_(nullptr),
	input_mgr_(nullptr),
	graphic_mgr_(nullptr),
	sound_mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::Node::~Node()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::scene::Node::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::Node::Init(void)
{
	this->Release();

	this->input_mgr_ = nullptr;
	this->graphic_mgr_ = nullptr;
	this->sound_mgr_ = nullptr;

	tml::scene::Node::Init();

	return;
}


/**
 * @brief OnCreate関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Node::OnCreate(void)
{
	if (tml::scene::Node::OnCreate() < 0) {
		return (-1);
	}

	this->input_mgr_ = this->desc_->GetManager()->GetInputManager();
	this->graphic_mgr_ = this->desc_->GetManager()->GetGraphicManager();
	this->sound_mgr_ = this->desc_->GetManager()->GetSoundManager();

	return (0);
}


/**
 * @brief OnCreateDeferred関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Node::OnCreateDeferred(void)
{
	if (tml::scene::Node::OnCreateDeferred() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnStart関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Node::OnStart(void)
{
	return (0);
}


/**
 * @brief OnEnd関数
 */
void cpp_base::scene::Node::OnEnd(void)
{
	return;
}


/**
 * @brief OnUpdate関数
 */
void cpp_base::scene::Node::OnUpdate(void)
{
	return;
}


/**
 * @brief OnSetDesc関数
 * @param desc (desc)
 */
void cpp_base::scene::Node::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const cpp_base::scene::NodeDesc *>(desc);

	tml::scene::Node::OnSetDesc(this->desc_);

	return;
}


/**
 * @brief OnSetManager関数
 * @param mgr (manager)
 */
void cpp_base::scene::Node::OnSetManager(tml::Manager *mgr)
{
	this->mgr_ = dynamic_cast<cpp_base::scene::Manager *>(mgr);

	tml::scene::Node::OnSetManager(this->mgr_);

	return;
}
