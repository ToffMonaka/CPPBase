/**
 * @file
 * @brief TextFileコードファイル
 */


#include "TextFile.h"


/**
 * @brief コンストラクタ
 */
tml::TextFile::TextFile()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::TextFile::~TextFile()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::TextFile::Release(void)
{
	tml::File::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::TextFile::Init(void)
{
	this->Release();

	tml::File::Init();

	return;
}


/**
 * @brief Read関数
 */
void tml::TextFile::Read(void)
{
	return;
}


/**
 * @brief Write関数
 */
void tml::TextFile::Write(void)
{
	return;
}
