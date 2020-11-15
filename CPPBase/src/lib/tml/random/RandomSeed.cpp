/**
 * @file
 * @brief RandomSeed�R�[�h�t�@�C��
 */


#include "RandomSeed.h"
#include <array>


/**
 * @brief �R���X�g���N�^
 */
tml::RandomSeed::RandomSeed()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::RandomSeed::~RandomSeed()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::RandomSeed::Release(void)
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::RandomSeed::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief Create�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::RandomSeed::Create(void)
{
	this->Release();

	std::random_device device;
	std::array<std::random_device::result_type, 10U> device_val_ary;

	std::generate(device_val_ary.begin(), device_val_ary.end(), std::ref(device));

	std::seed_seq seed_seq(device_val_ary.begin(), device_val_ary.end());

	this->seed_.seed(seed_seq);

	return (0);
}
