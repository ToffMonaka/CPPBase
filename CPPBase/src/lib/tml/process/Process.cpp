/**
 * @file
 * @brief Process�R�[�h�t�@�C��
 */


#include "Process.h"
#include "ProcessUtil.h"


/**
 * @brief �R���X�g���N�^
 */
tml::Process::Process()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::Process::~Process()
{
	return;
}


/**
 * @brief Release�֐�
 */
void tml::Process::Release(void)
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::Process::Init(void)
{
	this->th_id_ = std::thread::id();

	return;
}


/**
 * @brief Create�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::Process::Create(void)
{
	this->th_id_ = std::this_thread::get_id();

	return (0);
}
