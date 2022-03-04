/**
 * @file
 * @brief ManagerResource�R�[�h�t�@�C��
 */


#include "TestManagerResource.h"
#include "TestManager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::test::ManagerResourceDesc::ManagerResourceDesc() :
	mgr_(nullptr),
	deferred_create_flag(false)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::test::ManagerResourceDesc::~ManagerResourceDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::test::ManagerResourceDesc::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;
	this->resource_name.clear();
	this->deferred_create_flag = false;

	return;
}


/**
 * @brief Read�֐�
 * @param conf_file_read_desc (config_file_read_desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::test::ManagerResourceDesc::Read(const tml::INIFileReadDesc &conf_file_read_desc)
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
 * @brief ReadValue�֐�
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::test::ManagerResourceDesc::ReadValue(const tml::INIFile &conf_file)
{
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Resource Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"RES");

		if (val_name_cont != nullptr) {
			val = conf_file.data.GetValue((*val_name_cont), L"NAME");

			if (val != nullptr) {
				this->resource_name = (*val);
			}
		}
	}

	return (0);
}


/**
 * @brief SetManager�֐�
 * @param mgr (manager)
 */
void tml::test::ManagerResourceDesc::SetManager(tml::test::Manager *mgr)
{
	this->mgr_ = mgr;

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::test::ManagerResource::ManagerResource() :
	mgr_(nullptr),
	res_index_(0U),
	deferred_create_flg_(false),
	deferred_created_flg_(false),
	deferred_create_desc_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::test::ManagerResource::~ManagerResource()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::test::ManagerResource::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::test::ManagerResource::Create(const tml::test::ManagerResourceDesc &desc)
{
	if ((desc.GetManager() == nullptr)
	|| (this->res_index_ == 0U)) {
		return (-1);
	}

	this->mgr_ = desc.GetManager();

	return (0);
}


/**
 * @brief InitDeferred�֐�
 */
void tml::test::ManagerResource::InitDeferred(void)
{
	this->ReleaseDeferred();

	return;
}


/**
 * @brief CreateDeferred�֐�
 * @return result (result)<br>
 * 0����=���s,1=�쐬�ς�
 */
INT tml::test::ManagerResource::CreateDeferred(void)
{
	if (!this->deferred_create_flg_) {
		return (-1);
	}

	if (this->deferred_created_flg_) {
		return (1);
	}

	if (this->OnCreateDeferred() < 0) {
		this->InitDeferred();

		this->deferred_created_flg_ = false;
		this->deferred_create_desc_unique_p_.reset();
		this->deferred_create_desc_ = nullptr;

		return (-1);
	}

	this->deferred_created_flg_ = true;
	this->deferred_create_desc_unique_p_.reset();
	this->deferred_create_desc_ = nullptr;

	return (0);
}


/**
 * @brief OnCreateDeferred�֐�
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::test::ManagerResource::OnCreateDeferred(void)
{
	return (0);
}
