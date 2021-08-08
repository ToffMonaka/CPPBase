/**
 * @file
 * @brief Fileコードファイル
 */


#include "File.h"


/**
 * @brief コンストラクタ
 */
tml::FileReadDescData::FileReadDescData()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::FileReadDescData::~FileReadDescData()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::FileReadDescData::Init(void)
{
	this->Release();

	this->file_path.clear();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::FileWriteDescData::FileWriteDescData()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::FileWriteDescData::~FileWriteDescData()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::FileWriteDescData::Init(void)
{
	this->Release();

	this->file_path.clear();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::File::File()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::File::~File()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::File::Init(void)
{
	this->Release();

	return;
}
