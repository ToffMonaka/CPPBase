/**
 * @file
 * @brief FileUtilコードファイル
 */


#include "FileUtil.h"


std::unique_ptr<tml::FileUtilEngine> tml::FileUtil::engine_;
BYTE *tml::FileUtil::read_buf_ = nullptr;
size_t tml::FileUtil::read_buf_size_ = 0U;
BYTE *tml::FileUtil::write_buf_ = nullptr;
size_t tml::FileUtil::write_buf_size_ = 0U;
tml::MutexThreadLock tml::FileUtil::file_th_lock_;
tml::MutexThreadLock tml::FileUtil::dir_th_lock_;


/**
 * @brief Init関数
 */
void tml::FileUtil::Init(void)
{
	if (!tml::FileUtil::CheckFixedThread()) {
		return;
	}

	if (tml::FileUtil::read_buf_ != nullptr) {
		delete [] tml::FileUtil::read_buf_;

		tml::FileUtil::read_buf_ = nullptr;
	}

	tml::FileUtil::read_buf_size_ = 0U;

	if (tml::FileUtil::write_buf_ != nullptr) {
		delete [] tml::FileUtil::write_buf_;

		tml::FileUtil::write_buf_ = nullptr;
	}
	
	tml::FileUtil::write_buf_size_ = 0U;

	tml::FileUtil::engine_.reset();

	return;
}


/**
 * @brief Create関数
 * @param engine (engine)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::FileUtil::Create(std::unique_ptr<tml::FileUtilEngine> &engine)
{
	if (!tml::FileUtil::CheckFixedThread()) {
		tml::FileUtil::Init();

		return (-1);
	}

	tml::FileUtil::Init();

	tml::FileUtil::engine_ = std::move(engine);

	tml::FileUtil::read_buf_size_ = 2048U;
	tml::FileUtil::read_buf_ = new BYTE[tml::FileUtil::read_buf_size_];

	tml::FileUtil::write_buf_size_ = 2048U;
	tml::FileUtil::write_buf_ = new BYTE[tml::FileUtil::write_buf_size_];

	return (0);
}


/**
 * @brief GetReadBuffer関数
 *
 * Create関数不要
 *
 * @param dst_read_buf (dst_read_buffer)
 * @param dst_read_buf_size (dst_read_buffer_size)
 * @return dst_read_buf (dst_read_buffer)
 */
BYTE *&tml::FileUtil::GetReadBuffer(BYTE *&dst_read_buf, size_t &dst_read_buf_size)
{
	if (tml::FileUtil::read_buf_ == nullptr) {
		tml::FileUtil::read_buf_size_ = 2048U;
		tml::FileUtil::read_buf_ = new BYTE[tml::FileUtil::read_buf_size_];
	}

	dst_read_buf = tml::FileUtil::read_buf_;
	dst_read_buf_size = tml::FileUtil::read_buf_size_;

	return (dst_read_buf);
}


/**
 * @brief GetWriteBuffer関数
 *
 * Create関数不要
 *
 * @param dst_write_buf (dst_write_buffer)
 * @param dst_write_buf_size (dst_write_buffer_size)
 * @return dst_write_buf (dst_write_buffer)
 */
BYTE *&tml::FileUtil::GetWriteBuffer(BYTE *&dst_write_buf, size_t &dst_write_buf_size)
{
	if (tml::FileUtil::write_buf_ == nullptr) {
		tml::FileUtil::write_buf_size_ = 2048U;
		tml::FileUtil::write_buf_ = new BYTE[tml::FileUtil::write_buf_size_];
	}

	dst_write_buf = tml::FileUtil::write_buf_;
	dst_write_buf_size = tml::FileUtil::write_buf_size_;

	return (dst_write_buf);
}
