/**
 * @file
 * @brief MemoryUtilコードファイル
 */


#include "MemoryUtil.h"


std::unique_ptr<tml::MemoryUtilEngine> tml::MemoryUtil::engine_;


/**
 * @brief Init関数
 */
void tml::MemoryUtil::Init(void)
{
	if (!tml::MemoryUtil::CheckFixedThread()) {
		return;
	}

	tml::MemoryUtil::engine_.reset();

	return;
}


/**
 * @brief Create関数
 * @param engine (engine)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::MemoryUtil::Create(std::unique_ptr<tml::MemoryUtilEngine> &engine)
{
	if (!tml::MemoryUtil::CheckFixedThread()) {
		tml::MemoryUtil::Init();

		return (-1);
	}

	tml::MemoryUtil::Init();

	tml::MemoryUtil::engine_ = std::move(engine);

	return (0);
}


/**
 * @brief SetBufferIndex関数
 *
 * Create関数不要
 *
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param index (index)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 */
void tml::MemoryUtil::SetBufferIndex(const size_t buf_size, size_t &buf_index, const size_t index, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	if (index > buf_size) {
		tml::SetResult(dst_res, -1);

		return;
	}

	buf_index = index;

	return;
}


/**
 * @brief AddBufferIndex関数
 *
 * Create関数不要
 *
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param add_index (add_index)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 */
void tml::MemoryUtil::AddBufferIndex(const size_t buf_size, size_t &buf_index, const INT add_index, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	LONGLONG tmp_index = static_cast<LONGLONG>(buf_index) + add_index;

	if ((tmp_index < 0LL)
	|| (tmp_index > static_cast<LONGLONG>(buf_size))) {
		tml::SetResult(dst_res, -1);

		return;
	}

	buf_index = static_cast<size_t>(tmp_index);

	return;
}


/**
 * @brief ReadBufferChar関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 * @return val (value)
 */
CHAR tml::MemoryUtil::ReadBufferChar(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	CHAR val = 0;

	if (tml::CheckResult(dst_res)) {
		return (val);
	}

	if ((buf == nullptr)
	|| ((buf_index + sizeof(CHAR)) > buf_size)) {
		tml::SetResult(dst_res, -1);

		return (val);
	}

	val = buf[buf_index++];

	return (val);
}


/**
 * @brief ReadBufferUChar関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 * @return val (value)
 */
UCHAR tml::MemoryUtil::ReadBufferUChar(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	UCHAR val = 0;

	if (tml::CheckResult(dst_res)) {
		return (val);
	}

	if ((buf == nullptr)
	|| ((buf_index + sizeof(UCHAR)) > buf_size)) {
		tml::SetResult(dst_res, -1);

		return (val);
	}

	val = buf[buf_index++];

	return (val);
}


/**
 * @brief ReadBufferShortB関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 * @return val (value)
 */
SHORT tml::MemoryUtil::ReadBufferShortB(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	SHORT val = 0;

	if (tml::CheckResult(dst_res)) {
		return (val);
	}

	if ((buf == nullptr)
	|| ((buf_index + sizeof(SHORT)) > buf_size)) {
		tml::SetResult(dst_res, -1);

		return (val);
	}

	val |= (static_cast<SHORT>(buf[buf_index++]) & 0xFF) << 8;
	val |= (static_cast<SHORT>(buf[buf_index++]) & 0xFF) << 0;

	return (val);
}


/**
 * @brief ReadBufferShortL関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 * @return val (value)
 */
SHORT tml::MemoryUtil::ReadBufferShortL(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	SHORT val = 0;

	if (tml::CheckResult(dst_res)) {
		return (val);
	}

	if ((buf == nullptr)
	|| ((buf_index + sizeof(SHORT)) > buf_size)) {
		tml::SetResult(dst_res, -1);

		return (val);
	}

	val |= (static_cast<SHORT>(buf[buf_index++]) & 0xFF) << 0;
	val |= (static_cast<SHORT>(buf[buf_index++]) & 0xFF) << 8;

	return (val);
}


/**
 * @brief ReadBufferUShortB関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 * @return val (value)
 */
USHORT tml::MemoryUtil::ReadBufferUShortB(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	USHORT val = 0;

	if (tml::CheckResult(dst_res)) {
		return (val);
	}

	if ((buf == nullptr)
	|| ((buf_index + sizeof(USHORT)) > buf_size)) {
		tml::SetResult(dst_res, -1);

		return (val);
	}

	val |= (static_cast<USHORT>(buf[buf_index++]) & 0xFF) << 8;
	val |= (static_cast<USHORT>(buf[buf_index++]) & 0xFF) << 0;

	return (val);
}


/**
 * @brief ReadBufferUShortL関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 * @return val (value)
 */
USHORT tml::MemoryUtil::ReadBufferUShortL(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	USHORT val = 0;

	if (tml::CheckResult(dst_res)) {
		return (val);
	}

	if ((buf == nullptr)
	|| ((buf_index + sizeof(USHORT)) > buf_size)) {
		tml::SetResult(dst_res, -1);

		return (val);
	}

	val |= (static_cast<USHORT>(buf[buf_index++]) & 0xFF) << 0;
	val |= (static_cast<USHORT>(buf[buf_index++]) & 0xFF) << 8;

	return (val);
}


/**
 * @brief ReadBufferIntB関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 * @return val (value)
 */
INT tml::MemoryUtil::ReadBufferIntB(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	INT val = 0;

	if (tml::CheckResult(dst_res)) {
		return (val);
	}

	if ((buf == nullptr)
	|| ((buf_index + sizeof(INT)) > buf_size)) {
		tml::SetResult(dst_res, -1);

		return (val);
	}

	val |= (static_cast<INT>(buf[buf_index++]) & 0xFF) << 24;
	val |= (static_cast<INT>(buf[buf_index++]) & 0xFF) << 16;
	val |= (static_cast<INT>(buf[buf_index++]) & 0xFF) <<  8;
	val |= (static_cast<INT>(buf[buf_index++]) & 0xFF) <<  0;

	return (val);
}


/**
 * @brief ReadBufferIntL関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 * @return val (value)
 */
INT tml::MemoryUtil::ReadBufferIntL(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	INT val = 0;

	if (tml::CheckResult(dst_res)) {
		return (val);
	}

	if ((buf == nullptr)
	|| ((buf_index + sizeof(INT)) > buf_size)) {
		tml::SetResult(dst_res, -1);

		return (val);
	}

	val |= (static_cast<INT>(buf[buf_index++]) & 0xFF) <<  0;
	val |= (static_cast<INT>(buf[buf_index++]) & 0xFF) <<  8;
	val |= (static_cast<INT>(buf[buf_index++]) & 0xFF) << 16;
	val |= (static_cast<INT>(buf[buf_index++]) & 0xFF) << 24;

	return (val);
}


/**
 * @brief ReadBufferUIntB関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 * @return val (value)
 */
UINT tml::MemoryUtil::ReadBufferUIntB(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	UINT val = 0U;

	if (tml::CheckResult(dst_res)) {
		return (val);
	}

	if ((buf == nullptr)
	|| ((buf_index + sizeof(UINT)) > buf_size)) {
		tml::SetResult(dst_res, -1);

		return (val);
	}

	val |= (static_cast<UINT>(buf[buf_index++]) & 0xFF) << 24;
	val |= (static_cast<UINT>(buf[buf_index++]) & 0xFF) << 16;
	val |= (static_cast<UINT>(buf[buf_index++]) & 0xFF) <<  8;
	val |= (static_cast<UINT>(buf[buf_index++]) & 0xFF) <<  0;

	return (val);
}


/**
 * @brief ReadBufferUIntL関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 * @return val (value)
 */
UINT tml::MemoryUtil::ReadBufferUIntL(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	UINT val = 0U;

	if (tml::CheckResult(dst_res)) {
		return (val);
	}

	if ((buf == nullptr)
	|| ((buf_index + sizeof(UINT)) > buf_size)) {
		tml::SetResult(dst_res, -1);

		return (val);
	}

	val |= (static_cast<UINT>(buf[buf_index++]) & 0xFF) <<  0;
	val |= (static_cast<UINT>(buf[buf_index++]) & 0xFF) <<  8;
	val |= (static_cast<UINT>(buf[buf_index++]) & 0xFF) << 16;
	val |= (static_cast<UINT>(buf[buf_index++]) & 0xFF) << 24;

	return (val);
}


/**
 * @brief ReadBufferLongLongB関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 * @return val (value)
 */
LONGLONG tml::MemoryUtil::ReadBufferLongLongB(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	LONGLONG val = 0LL;

	if (tml::CheckResult(dst_res)) {
		return (val);
	}

	if ((buf == nullptr)
	|| ((buf_index + sizeof(LONGLONG)) > buf_size)) {
		tml::SetResult(dst_res, -1);

		return (val);
	}

	val |= (static_cast<LONGLONG>(buf[buf_index++]) & 0xFF) << 56;
	val |= (static_cast<LONGLONG>(buf[buf_index++]) & 0xFF) << 48;
	val |= (static_cast<LONGLONG>(buf[buf_index++]) & 0xFF) << 40;
	val |= (static_cast<LONGLONG>(buf[buf_index++]) & 0xFF) << 32;
	val |= (static_cast<LONGLONG>(buf[buf_index++]) & 0xFF) << 24;
	val |= (static_cast<LONGLONG>(buf[buf_index++]) & 0xFF) << 16;
	val |= (static_cast<LONGLONG>(buf[buf_index++]) & 0xFF) <<  8;
	val |= (static_cast<LONGLONG>(buf[buf_index++]) & 0xFF) <<  0;

	return (val);
}


/**
 * @brief ReadBufferLongLongL関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 * @return val (value)
 */
LONGLONG tml::MemoryUtil::ReadBufferLongLongL(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	LONGLONG val = 0LL;

	if (tml::CheckResult(dst_res)) {
		return (val);
	}

	if ((buf == nullptr)
	|| ((buf_index + sizeof(LONGLONG)) > buf_size)) {
		tml::SetResult(dst_res, -1);

		return (val);
	}

	val |= (static_cast<LONGLONG>(buf[buf_index++]) & 0xFF) <<  0;
	val |= (static_cast<LONGLONG>(buf[buf_index++]) & 0xFF) <<  8;
	val |= (static_cast<LONGLONG>(buf[buf_index++]) & 0xFF) << 16;
	val |= (static_cast<LONGLONG>(buf[buf_index++]) & 0xFF) << 24;
	val |= (static_cast<LONGLONG>(buf[buf_index++]) & 0xFF) << 32;
	val |= (static_cast<LONGLONG>(buf[buf_index++]) & 0xFF) << 40;
	val |= (static_cast<LONGLONG>(buf[buf_index++]) & 0xFF) << 48;
	val |= (static_cast<LONGLONG>(buf[buf_index++]) & 0xFF) << 56;

	return (val);
}


/**
 * @brief ReadBufferULongLongB関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 * @return val (value)
 */
ULONGLONG tml::MemoryUtil::ReadBufferULongLongB(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	ULONGLONG val = 0ULL;

	if (tml::CheckResult(dst_res)) {
		return (val);
	}

	if ((buf == nullptr)
	|| ((buf_index + sizeof(ULONGLONG)) > buf_size)) {
		tml::SetResult(dst_res, -1);

		return (val);
	}

	val |= (static_cast<ULONGLONG>(buf[buf_index++]) & 0xFF) << 56;
	val |= (static_cast<ULONGLONG>(buf[buf_index++]) & 0xFF) << 48;
	val |= (static_cast<ULONGLONG>(buf[buf_index++]) & 0xFF) << 40;
	val |= (static_cast<ULONGLONG>(buf[buf_index++]) & 0xFF) << 32;
	val |= (static_cast<ULONGLONG>(buf[buf_index++]) & 0xFF) << 24;
	val |= (static_cast<ULONGLONG>(buf[buf_index++]) & 0xFF) << 16;
	val |= (static_cast<ULONGLONG>(buf[buf_index++]) & 0xFF) <<  8;
	val |= (static_cast<ULONGLONG>(buf[buf_index++]) & 0xFF) <<  0;

	return (val);
}


/**
 * @brief ReadBufferULongLongL関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 * @return val (value)
 */
ULONGLONG tml::MemoryUtil::ReadBufferULongLongL(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	ULONGLONG val = 0ULL;

	if (tml::CheckResult(dst_res)) {
		return (val);
	}

	if ((buf == nullptr)
	|| ((buf_index + sizeof(ULONGLONG)) > buf_size)) {
		tml::SetResult(dst_res, -1);

		return (val);
	}

	val |= (static_cast<ULONGLONG>(buf[buf_index++]) & 0xFF) <<  0;
	val |= (static_cast<ULONGLONG>(buf[buf_index++]) & 0xFF) <<  8;
	val |= (static_cast<ULONGLONG>(buf[buf_index++]) & 0xFF) << 16;
	val |= (static_cast<ULONGLONG>(buf[buf_index++]) & 0xFF) << 24;
	val |= (static_cast<ULONGLONG>(buf[buf_index++]) & 0xFF) << 32;
	val |= (static_cast<ULONGLONG>(buf[buf_index++]) & 0xFF) << 40;
	val |= (static_cast<ULONGLONG>(buf[buf_index++]) & 0xFF) << 48;
	val |= (static_cast<ULONGLONG>(buf[buf_index++]) & 0xFF) << 56;

	return (val);
}


/**
 * @brief ReadBufferFloatB関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 * @return val (value)
 */
FLOAT tml::MemoryUtil::ReadBufferFloatB(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	FLOAT val = 0.0f;
	UINT tmp_val = tml::MemoryUtil::ReadBufferUIntB(buf, buf_size, buf_index, dst_res);

	if (tml::CheckResult(dst_res)) {
		return (val);
	}

	tml::Copy(&val, reinterpret_cast<FLOAT *>(&tmp_val), 1U);

	if (std::isnan(val)) {
		val = 0.0f;
	}

	return (val);
}


/**
 * @brief ReadBufferFloatL関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 * @return val (value)
 */
FLOAT tml::MemoryUtil::ReadBufferFloatL(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	FLOAT val = 0.0f;
	UINT tmp_val = tml::MemoryUtil::ReadBufferUIntL(buf, buf_size, buf_index, dst_res);

	if (tml::CheckResult(dst_res)) {
		return (val);
	}

	tml::Copy(&val, reinterpret_cast<FLOAT *>(&tmp_val), 1U);

	if (std::isnan(val)) {
		val = 0.0f;
	}

	return (val);
}


/**
 * @brief ReadBufferDoubleB関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 * @return val (value)
 */
DOUBLE tml::MemoryUtil::ReadBufferDoubleB(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	DOUBLE val = 0.0;
	ULONGLONG tmp_val = tml::MemoryUtil::ReadBufferULongLongB(buf, buf_size, buf_index, dst_res);

	if (tml::CheckResult(dst_res)) {
		return (val);
	}

	tml::Copy(&val, reinterpret_cast<DOUBLE *>(&tmp_val), 1U);

	if (std::isnan(val)) {
		val = 0.0;
	}

	return (val);
}


/**
 * @brief ReadBufferDoubleL関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 * @return val (value)
 */
DOUBLE tml::MemoryUtil::ReadBufferDoubleL(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	DOUBLE val = 0.0;
	ULONGLONG tmp_val = tml::MemoryUtil::ReadBufferULongLongL(buf, buf_size, buf_index, dst_res);

	if (tml::CheckResult(dst_res)) {
		return (val);
	}

	tml::Copy(&val, reinterpret_cast<DOUBLE *>(&tmp_val), 1U);

	if (std::isnan(val)) {
		val = 0.0;
	}

	return (val);
}


/**
 * @brief ReadBufferArray関数
 *
 * Create関数不要
 *
 * @param dst_ary (dst_array)
 * @param dst_ary_size (dst_array_size)
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param read_size (read_size)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 * @return dst_ary (dst_array)
 */
BYTE *tml::MemoryUtil::ReadBufferArray(BYTE *dst_ary, const size_t dst_ary_size, const BYTE *buf, const size_t buf_size, size_t &buf_index, const size_t read_size, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return (dst_ary);
	}

	if ((buf == nullptr)
	|| ((buf_index + read_size) > buf_size)
	|| (buf == dst_ary)
	|| (read_size > dst_ary_size)) {
		tml::SetResult(dst_res, -1);

		return (dst_ary);
	}

	tml::Copy(dst_ary, &buf[buf_index], read_size);
	buf_index += read_size;

	return (dst_ary);
}


/**
 * @brief ReadBufferStringB関数
 *
 * Create関数不要
 *
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 * @return dst_str (dst_string)
 */
CHAR *tml::MemoryUtil::ReadBufferStringB(CHAR *dst_str, const size_t dst_str_size, BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		if ((dst_str != nullptr)
		&& (dst_str_size >= sizeof(CHAR))) {
			dst_str[0] = 0;
		}

		return (dst_str);
	}

	if ((dst_str == nullptr)
	|| (dst_str_size < sizeof(CHAR))) {
		tml::SetResult(dst_res, -1);

		return (dst_str);
	}

	dst_str[0] = 0;

	size_t str_size = static_cast<size_t>(tml::MemoryUtil::ReadBufferUShortB(buf, buf_size, buf_index, dst_res)) & 0xFFFF;

	if (((buf_index + str_size) > buf_size)
	|| ((str_size + sizeof(CHAR)) > dst_str_size)) {
		tml::SetResult(dst_res, -1);

		return (dst_str);
	}

	tml::Copy(reinterpret_cast<BYTE *>(dst_str), &buf[buf_index], str_size);
	buf_index += str_size;

	dst_str[str_size] = 0;

	return (dst_str);
}


/**
 * @brief ReadBufferStringL関数
 *
 * Create関数不要
 *
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 * @return dst_str (dst_string)
 */
CHAR *tml::MemoryUtil::ReadBufferStringL(CHAR *dst_str, const size_t dst_str_size, BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		if ((dst_str != nullptr)
		&& (dst_str_size >= sizeof(CHAR))) {
			dst_str[0] = 0;
		}

		return (dst_str);
	}

	if ((dst_str == nullptr)
	|| (dst_str_size < sizeof(CHAR))) {
		tml::SetResult(dst_res, -1);

		return (dst_str);
	}

	dst_str[0] = 0;

	size_t str_size = static_cast<size_t>(tml::MemoryUtil::ReadBufferUShortL(buf, buf_size, buf_index, dst_res)) & 0xFFFF;

	if (((buf_index + str_size) > buf_size)
	|| ((str_size + sizeof(CHAR)) > dst_str_size)) {
		tml::SetResult(dst_res, -1);

		return (dst_str);
	}

	tml::Copy(reinterpret_cast<BYTE *>(dst_str), &buf[buf_index], str_size);
	buf_index += str_size;

	dst_str[str_size] = 0;

	return (dst_str);
}


/**
 * @brief ReadBufferStringB関数
 *
 * Create関数不要
 *
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 * @return dst_str (dst_string)
 */
WCHAR *tml::MemoryUtil::ReadBufferStringB(WCHAR *dst_str, const size_t dst_str_size, BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		if ((dst_str != nullptr)
		&& (dst_str_size >= sizeof(WCHAR))) {
			dst_str[0] = 0;
		}

		return (dst_str);
	}

	if ((dst_str == nullptr)
	|| (dst_str_size < sizeof(WCHAR))) {
		tml::SetResult(dst_res, -1);

		return (dst_str);
	}

	dst_str[0] = 0;

	size_t str_size = static_cast<size_t>(tml::MemoryUtil::ReadBufferUShortB(buf, buf_size, buf_index, dst_res)) & 0xFFFF;

	if (((buf_index + str_size) > buf_size)
	|| ((str_size + sizeof(WCHAR)) > dst_str_size)) {
		tml::SetResult(dst_res, -1);

		return (dst_str);
	}

	tml::Copy(reinterpret_cast<BYTE *>(dst_str), &buf[buf_index], str_size);
	buf_index += str_size;

	dst_str[str_size >> 1] = 0;

	return (dst_str);
}


/**
 * @brief ReadBufferStringL関数
 *
 * Create関数不要
 *
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 * @return dst_str (dst_string)
 */
WCHAR *tml::MemoryUtil::ReadBufferStringL(WCHAR *dst_str, const size_t dst_str_size, BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		if ((dst_str != nullptr)
		&& (dst_str_size >= sizeof(WCHAR))) {
			dst_str[0] = 0;
		}

		return (dst_str);
	}

	if ((dst_str == nullptr)
	|| (dst_str_size < sizeof(WCHAR))) {
		tml::SetResult(dst_res, -1);

		return (dst_str);
	}

	dst_str[0] = 0;

	size_t str_size = static_cast<size_t>(tml::MemoryUtil::ReadBufferUShortL(buf, buf_size, buf_index, dst_res)) & 0xFFFF;

	if (((buf_index + str_size) > buf_size)
	|| ((str_size + sizeof(WCHAR)) > dst_str_size)) {
		tml::SetResult(dst_res, -1);

		return (dst_str);
	}

	tml::Copy(reinterpret_cast<BYTE *>(dst_str), &buf[buf_index], str_size);
	buf_index += str_size;

	dst_str[str_size >> 1] = 0;

	return (dst_str);
}


/**
 * @brief WriteBufferChar関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteBufferChar(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const CHAR val, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + sizeof(CHAR)) > dst_buf_size)) {
		tml::SetResult(dst_res, -1);

		return;
	}

	dst_buf[dst_buf_index++] = val;

	return;
}


/**
 * @brief WriteBufferUChar関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteBufferUChar(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const UCHAR val, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + sizeof(UCHAR)) > dst_buf_size)) {
		tml::SetResult(dst_res, -1);

		return;
	}

	dst_buf[dst_buf_index++] = val;

	return;
}


/**
 * @brief WriteBufferShortB関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteBufferShortB(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const SHORT val, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + sizeof(SHORT)) > dst_buf_size)) {
		tml::SetResult(dst_res, -1);

		return;
	}

	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 8) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 0) & 0xFF);

	return;
}


/**
 * @brief WriteBufferShortL関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteBufferShortL(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const SHORT val, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + sizeof(SHORT)) > dst_buf_size)) {
		tml::SetResult(dst_res, -1);

		return;
	}

	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 0) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 8) & 0xFF);

	return;
}


/**
 * @brief WriteBufferUShortB関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteBufferUShortB(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const USHORT val, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + sizeof(USHORT)) > dst_buf_size)) {
		tml::SetResult(dst_res, -1);

		return;
	}

	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 8) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 0) & 0xFF);

	return;
}


/**
 * @brief WriteBufferUShortL関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteBufferUShortL(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const USHORT val, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + sizeof(USHORT)) > dst_buf_size)) {
		tml::SetResult(dst_res, -1);

		return;
	}

	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 0) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 8) & 0xFF);

	return;
}


/**
 * @brief WriteBufferIntB関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteBufferIntB(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const INT val, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + sizeof(INT)) > dst_buf_size)) {
		tml::SetResult(dst_res, -1);

		return;
	}

	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 24) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 16) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >>  8) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >>  0) & 0xFF);

	return;
}


/**
 * @brief WriteBufferIntL関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteBufferIntL(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const INT val, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + sizeof(INT)) > dst_buf_size)) {
		tml::SetResult(dst_res, -1);

		return;
	}

	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >>  0) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >>  8) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 16) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 24) & 0xFF);

	return;
}


/**
 * @brief WriteBufferUIntB関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteBufferUIntB(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const UINT val, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + sizeof(UINT)) > dst_buf_size)) {
		tml::SetResult(dst_res, -1);

		return;
	}

	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 24) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 16) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >>  8) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >>  0) & 0xFF);

	return;
}


/**
 * @brief WriteBufferUIntL関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteBufferUIntL(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const UINT val, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + sizeof(UINT)) > dst_buf_size)) {
		tml::SetResult(dst_res, -1);

		return;
	}

	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >>  0) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >>  8) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 16) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 24) & 0xFF);

	return;
}


/**
 * @brief WriteBufferLongLongB関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteBufferLongLongB(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const LONGLONG val, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + sizeof(LONGLONG)) > dst_buf_size)) {
		tml::SetResult(dst_res, -1);

		return;
	}

	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 56) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 48) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 40) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 32) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 24) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 16) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >>  8) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >>  0) & 0xFF);

	return;
}


/**
 * @brief WriteBufferLongLongL関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteBufferLongLongL(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const LONGLONG val, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + sizeof(LONGLONG)) > dst_buf_size)) {
		tml::SetResult(dst_res, -1);

		return;
	}

	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >>  0) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >>  8) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 16) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 24) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 32) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 40) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 48) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 56) & 0xFF);

	return;
}


/**
 * @brief WriteBufferULongLongB関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteBufferULongLongB(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const ULONGLONG val, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + sizeof(ULONGLONG)) > dst_buf_size)) {
		tml::SetResult(dst_res, -1);

		return;
	}

	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 56) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 48) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 40) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 32) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 24) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 16) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >>  8) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >>  0) & 0xFF);

	return;
}


/**
 * @brief WriteBufferULongLongL関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteBufferULongLongL(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const ULONGLONG val, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + sizeof(ULONGLONG)) > dst_buf_size)) {
		tml::SetResult(dst_res, -1);

		return;
	}

	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >>  0) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >>  8) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 16) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 24) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 32) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 40) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 48) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 56) & 0xFF);

	return;
}


/**
 * @brief WriteBufferFloatB関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteBufferFloatB(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const FLOAT val, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	UINT tmp_val = 0U;

	tml::Copy(&tmp_val, reinterpret_cast<const UINT *>(&val), 1U);

	tml::MemoryUtil::WriteBufferUIntB(dst_buf, dst_buf_size, dst_buf_index, tmp_val, dst_res);

	return;
}


/**
 * @brief WriteBufferFloatL関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteBufferFloatL(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const FLOAT val, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	UINT tmp_val = 0U;

	tml::Copy(&tmp_val, reinterpret_cast<const UINT *>(&val), 1U);

	tml::MemoryUtil::WriteBufferUIntL(dst_buf, dst_buf_size, dst_buf_index, tmp_val, dst_res);

	return;
}


/**
 * @brief WriteBufferDoubleB関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteBufferDoubleB(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const DOUBLE val, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	ULONGLONG tmp_val = 0ULL;

	tml::Copy(&tmp_val, reinterpret_cast<const ULONGLONG *>(&val), 1U);

	tml::MemoryUtil::WriteBufferULongLongB(dst_buf, dst_buf_size, dst_buf_index, tmp_val, dst_res);

	return;
}


/**
 * @brief WriteBufferDoubleL関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteBufferDoubleL(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const DOUBLE val, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	ULONGLONG tmp_val = 0ULL;

	tml::Copy(&tmp_val, reinterpret_cast<const ULONGLONG *>(&val), 1U);

	tml::MemoryUtil::WriteBufferULongLongL(dst_buf, dst_buf_size, dst_buf_index, tmp_val, dst_res);

	return;
}


/**
 * @brief WriteBufferArray関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param ary (array)
 * @param ary_size (array_size)
 * @param write_size (write_size)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteBufferArray(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const BYTE *ary, const size_t ary_size, const size_t write_size, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + write_size) > dst_buf_size)
	|| (dst_buf == ary)
	|| (write_size > ary_size)) {
		tml::SetResult(dst_res, -1);

		return;
	}

	tml::Copy(&dst_buf[dst_buf_index], ary, write_size);
	dst_buf_index += write_size;

	return;
}


/**
 * @brief WriteBufferStringB関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param str (string)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteBufferStringB(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const CHAR *str, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	size_t str_size = strlen(str);

	tml::MemoryUtil::WriteBufferUShortB(dst_buf, dst_buf_size, dst_buf_index, static_cast<USHORT>(str_size), dst_res);
	tml::MemoryUtil::WriteBufferArray(dst_buf, dst_buf_size, dst_buf_index, reinterpret_cast<const BYTE *>(str), str_size, str_size, dst_res);

	return;
}


/**
 * @brief WriteBufferStringL関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param str (string)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteBufferStringL(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const CHAR *str, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	size_t str_size = strlen(str);

	tml::MemoryUtil::WriteBufferUShortL(dst_buf, dst_buf_size, dst_buf_index, static_cast<USHORT>(str_size), dst_res);
	tml::MemoryUtil::WriteBufferArray(dst_buf, dst_buf_size, dst_buf_index, reinterpret_cast<const BYTE *>(str), str_size, str_size, dst_res);

	return;
}


/**
 * @brief WriteBufferStringB関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param str (string)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteBufferStringB(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const WCHAR *str, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	size_t str_size = wcslen(str) << 1;

	tml::MemoryUtil::WriteBufferUShortB(dst_buf, dst_buf_size, dst_buf_index, static_cast<USHORT>(str_size), dst_res);
	tml::MemoryUtil::WriteBufferArray(dst_buf, dst_buf_size, dst_buf_index, reinterpret_cast<const BYTE *>(str), str_size, str_size, dst_res);

	return;
}


/**
 * @brief WriteBufferStringL関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param str (string)
 * @param dst_res (dst_result)<br>
 * nullptr=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteBufferStringL(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const WCHAR *str, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	size_t str_size = wcslen(str) << 1;

	tml::MemoryUtil::WriteBufferUShortL(dst_buf, dst_buf_size, dst_buf_index, static_cast<USHORT>(str_size), dst_res);
	tml::MemoryUtil::WriteBufferArray(dst_buf, dst_buf_size, dst_buf_index, reinterpret_cast<const BYTE *>(str), str_size, str_size, dst_res);

	return;
}
