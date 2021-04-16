#if 0
/**
 * @file
 * @brief Event�R�[�h�t�@�C��
 */


#include "Event.h"


/**
 * @brief �R���X�g���N�^
 */
tml::input::Event::Event() :
	event_type_(tml::ConstantUtil::INPUT::EVENT_TYPE::NONE),
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::input::Event::~Event()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::input::Event::Init(void)
{
	this->event_type_ = tml::ConstantUtil::INPUT::EVENT_TYPE::NONE;
	this->mgr_ = nullptr;

	return;
}


/**
 * @brief Create�֐�
 * @param event_type (event_type)
 * @param mgr (manager)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::input::Event::Create(const tml::ConstantUtil::INPUT::EVENT_TYPE event_type, tml::input::Manager *mgr)
{
	if ((event_type == tml::ConstantUtil::INPUT::EVENT_TYPE::NONE)
	|| (mgr == nullptr)) {
		return (-1);
	}

	this->event_type_ = event_type;
	this->mgr_ = mgr;

	return (0);
}
#endif
