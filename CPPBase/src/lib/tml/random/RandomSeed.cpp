/**
 * @file
 * @brief RandomSeedコードファイル
 */


#include "RandomSeed.h"


/**
 * @brief コンストラクタ
 */
tml::RandomSeed::RandomSeed()
{
	this->seed_val_cont_.resize(10U);

	std::random_device device;

	std::generate(this->seed_val_cont_.begin(), this->seed_val_cont_.end(), std::ref(device));

	std::seed_seq seed_seq(this->seed_val_cont_.begin(), this->seed_val_cont_.end());

	this->seed_.seed(seed_seq);

	return;
}


/**
 * @brief デストラクタ
 */
tml::RandomSeed::~RandomSeed()
{
	return;
}
