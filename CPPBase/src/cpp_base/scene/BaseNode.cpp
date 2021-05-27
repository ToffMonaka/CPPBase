/**
 * @file
 * @brief BaseNodeコードファイル
 */


#include "BaseNode.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
cpp_base::scene::BaseNodeDesc::BaseNodeDesc() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::BaseNodeDesc::~BaseNodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::BaseNodeDesc::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	tml::scene::BaseNodeDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
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
 * @brief SetManager関数
 * @param mgr (manager)
 */
void cpp_base::scene::BaseNodeDesc::SetManager(cpp_base::scene::Manager *mgr)
{
	this->mgr_ = mgr;

	tml::scene::BaseNodeDesc::SetManager(mgr);

	return;
}


/**
 * @brief コンストラクタ
 */
cpp_base::scene::BaseNode::BaseNode() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::BaseNode::~BaseNode()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::scene::BaseNode::Release(void)
{
	tml::scene::BaseNode::Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::BaseNode::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	tml::scene::BaseNode::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
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
