/**
 * @file
 * @brief Bufferコードファイル
 */


#include "Buffer.h"


/**
 * @brief コンストラクタ
 */
tml::Buffer::Buffer() :
	p_(nullptr),
	capacity_(0U),
	size_(0U),
	len_(0U),
	read_index_(0U),
	read_result_(0),
	write_index_(0U),
	write_result_(0)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::Buffer::~Buffer()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::Buffer::Init(void)
{
	this->Release();

	this->p_ = nullptr;
	this->capacity_ = 0U;
	this->size_ = 0U;
	this->len_ = 0U;
	this->read_index_ = 0U;
	this->read_result_ = 0;
	this->write_index_ = 0U;
	this->write_result_ = 0;

	return;
}
