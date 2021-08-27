/**
 * @file
 * @brief ManagerResourceFactory�R�[�h�t�@�C��
 */


#include "ManagerResourceFactory.h"


/**
 * @brief �R���X�g���N�^
 */
tml::ManagerResourceFactory::ManagerResourceFactory()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::ManagerResourceFactory::~ManagerResourceFactory()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::ManagerResourceFactory::Init(void)
{
	this->Release();

	this->func_cont_.clear();

	return;
}


/**
 * @brief AddFunction�֐�
 * @param class_name (class_name)
 * @param func (function)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::ManagerResourceFactory::AddFunction(const WCHAR *class_name, std::function<tml::shared_ptr<tml::ManagerResource>(const tml::INIFileReadDesc &, INT *)> func)
{
	if ((class_name == nullptr)
	|| (class_name[0] == 0)) {
		return (-1);
	}

	this->func_cont_[class_name] = func;

	return (0);
}


/**
 * @brief RemoveFunction�֐�
 * @param class_name (class_name)
 */
void tml::ManagerResourceFactory::RemoveFunction(const WCHAR *class_name)
{
	if ((class_name == nullptr)
	|| (class_name[0] == 0)) {
		return;
	}

	this->func_cont_.erase(class_name);

	return;
}
