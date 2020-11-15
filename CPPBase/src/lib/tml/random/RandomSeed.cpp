/**
 * @file
 * @brief RandomSeedコードファイル
 */


#include "RandomSeed.h"
#include <array>


/**
 * @brief コンストラクタ
 */
tml::RandomSeed::RandomSeed()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::RandomSeed::~RandomSeed()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::RandomSeed::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::RandomSeed::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief Create関数
 * @return res (result)<br>
 * 0未満=失敗
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
