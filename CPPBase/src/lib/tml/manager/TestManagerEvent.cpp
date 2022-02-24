/**
 * @file
 * @brief ManagerEventコードファイル
 */


#include "TestManagerEvent.h"
#include "TestManager.h"


/**
 * @brief コンストラクタ
 */
tml::test::ManagerEventDesc::ManagerEventDesc() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::test::ManagerEventDesc::~ManagerEventDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::test::ManagerEventDesc::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;
	this->event_name.clear();

	return;
}


/**
 * @brief Read関数
 * @param conf_file_read_desc (config_file_read_desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::test::ManagerEventDesc::Read(const tml::INIFileReadDesc &conf_file_read_desc)
{
	auto conf_file_read_desc_dat = conf_file_read_desc.GetDataByParent();

	if (conf_file_read_desc_dat->IsEmpty()) {
		return (0);
	}

	tml::INIFile conf_file;

	conf_file.read_desc.parent_data = conf_file_read_desc_dat;

	if (conf_file.Read() < 0) {
		return (-1);
	}

	if (conf_file.data.value_container.empty()) {
		return (0);
	}

	return (this->ReadValue(conf_file));
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::test::ManagerEventDesc::ReadValue(const tml::INIFile &conf_file)
{
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Resource Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"EVENT");

		if (val_name_cont != nullptr) {
			val = conf_file.data.GetValue((*val_name_cont), L"NAME");

			if (val != nullptr) {
				this->event_name = (*val);
			}
		}
	}

	return (0);
}


/**
 * @brief SetManager関数
 * @param mgr (manager)
 */
void tml::test::ManagerEventDesc::SetManager(tml::test::Manager *mgr)
{
	this->mgr_ = mgr;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::test::ManagerEvent::ManagerEvent() :
	mgr_(nullptr),
	event_index_(0U)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::test::ManagerEvent::~ManagerEvent()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::test::ManagerEvent::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::test::ManagerEvent::Create(const tml::test::ManagerEventDesc &desc)
{
	if ((desc.GetManager() == nullptr)
	|| (this->event_index_ == 0U)) {
		return (-1);
	}

	this->mgr_ = desc.GetManager();

	return (0);
}
