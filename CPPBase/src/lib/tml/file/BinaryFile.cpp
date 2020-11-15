/**
 * @file
 * @brief BinaryFileコードファイル
 */


#include "BinaryFile.h"


/**
 * @brief コンストラクタ
 */
tml::BinaryFile::BinaryFile()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::BinaryFile::~BinaryFile()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::BinaryFile::Release(void)
{
	tml::File::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::BinaryFile::Init(void)
{
	this->Release();

	tml::File::Init();

	return;
}


/**
 * @brief Read関数
 */
void tml::BinaryFile::Read(void)
{
	return;
}


/**
 * @brief Write関数
 */
void tml::BinaryFile::Write(void)
{
	return;
}
