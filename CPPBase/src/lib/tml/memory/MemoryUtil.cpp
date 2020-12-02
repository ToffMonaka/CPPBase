/**
 * @file
 * @brief MemoryUtilコードファイル
 */


#include "MemoryUtil.h"


tml::ThreadFix tml::MemoryUtil::th_fix_;
std::unique_ptr<tml::MemoryUtilEngine> tml::MemoryUtil::engine_;


/**
 * @brief Init関数
 */
void tml::MemoryUtil::Init(void)
{
	if (!tml::MemoryUtil::th_fix_.Check()) {
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
	if (!tml::MemoryUtil::th_fix_.Check()) {
		tml::MemoryUtil::Init();

		return (-1);
	}

	tml::MemoryUtil::Init();

	tml::MemoryUtil::engine_ = std::move(engine);

	return (0);
}


/**
 * @brief ReadCHAR関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 * @return val (value)
 */
CHAR tml::MemoryUtil::ReadCHAR(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	CHAR val = 0;

	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return (val);
		}
	}

	if ((buf == nullptr)
	|| ((buf_index + sizeof(CHAR)) > buf_size)) {
		tml::SetValue(dst_res, -1);

		return (val);
	}

	val = buf[buf_index++];

	return (val);
}


/**
 * @brief ReadUCHAR関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 * @return val (value)
 */
UCHAR tml::MemoryUtil::ReadUCHAR(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	UCHAR val = 0;

	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return (val);
		}
	}

	if ((buf == nullptr)
	|| ((buf_index + sizeof(UCHAR)) > buf_size)) {
		tml::SetValue(dst_res, -1);

		return (val);
	}

	val = buf[buf_index++];

	return (val);
}


/**
 * @brief ReadSHORT_B関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 * @return val (value)
 */
SHORT tml::MemoryUtil::ReadSHORT_B(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	SHORT val = 0;

	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return (val);
		}
	}

	if ((buf == nullptr)
	|| ((buf_index + sizeof(SHORT)) > buf_size)) {
		tml::SetValue(dst_res, -1);

		return (val);
	}

	val |= (static_cast<SHORT>(buf[buf_index++]) & 0xFF) << 8;
	val |= (static_cast<SHORT>(buf[buf_index++]) & 0xFF) << 0;

	return (val);
}


/**
 * @brief ReadSHORT_L関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 * @return val (value)
 */
SHORT tml::MemoryUtil::ReadSHORT_L(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	SHORT val = 0;

	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return (val);
		}
	}

	if ((buf == nullptr)
	|| ((buf_index + sizeof(SHORT)) > buf_size)) {
		tml::SetValue(dst_res, -1);

		return (val);
	}

	val |= (static_cast<SHORT>(buf[buf_index++]) & 0xFF) << 0;
	val |= (static_cast<SHORT>(buf[buf_index++]) & 0xFF) << 8;

	return (val);
}


/**
 * @brief ReadUSHORT_B関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 * @return val (value)
 */
USHORT tml::MemoryUtil::ReadUSHORT_B(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	USHORT val = 0;

	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return (val);
		}
	}

	if ((buf == nullptr)
	|| ((buf_index + sizeof(USHORT)) > buf_size)) {
		tml::SetValue(dst_res, -1);

		return (val);
	}

	val |= (static_cast<USHORT>(buf[buf_index++]) & 0xFF) << 8;
	val |= (static_cast<USHORT>(buf[buf_index++]) & 0xFF) << 0;

	return (val);
}


/**
 * @brief ReadUSHORT_L関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 * @return val (value)
 */
USHORT tml::MemoryUtil::ReadUSHORT_L(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	USHORT val = 0;

	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return (val);
		}
	}

	if ((buf == nullptr)
	|| ((buf_index + sizeof(USHORT)) > buf_size)) {
		tml::SetValue(dst_res, -1);

		return (val);
	}

	val |= (static_cast<USHORT>(buf[buf_index++]) & 0xFF) << 0;
	val |= (static_cast<USHORT>(buf[buf_index++]) & 0xFF) << 8;

	return (val);
}


/**
 * @brief ReadINT_B関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 * @return val (value)
 */
INT tml::MemoryUtil::ReadINT_B(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	INT val = 0;

	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return (val);
		}
	}

	if ((buf == nullptr)
	|| ((buf_index + sizeof(INT)) > buf_size)) {
		tml::SetValue(dst_res, -1);

		return (val);
	}

	val |= (static_cast<INT>(buf[buf_index++]) & 0xFF) << 24;
	val |= (static_cast<INT>(buf[buf_index++]) & 0xFF) << 16;
	val |= (static_cast<INT>(buf[buf_index++]) & 0xFF) <<  8;
	val |= (static_cast<INT>(buf[buf_index++]) & 0xFF) <<  0;

	return (val);
}


/**
 * @brief ReadINT_L関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 * @return val (value)
 */
INT tml::MemoryUtil::ReadINT_L(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	INT val = 0;

	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return (val);
		}
	}

	if ((buf == nullptr)
	|| ((buf_index + sizeof(INT)) > buf_size)) {
		tml::SetValue(dst_res, -1);

		return (val);
	}

	val |= (static_cast<INT>(buf[buf_index++]) & 0xFF) <<  0;
	val |= (static_cast<INT>(buf[buf_index++]) & 0xFF) <<  8;
	val |= (static_cast<INT>(buf[buf_index++]) & 0xFF) << 16;
	val |= (static_cast<INT>(buf[buf_index++]) & 0xFF) << 24;

	return (val);
}


/**
 * @brief ReadUINT_B関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 * @return val (value)
 */
UINT tml::MemoryUtil::ReadUINT_B(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	UINT val = 0U;

	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return (val);
		}
	}

	if ((buf == nullptr)
	|| ((buf_index + sizeof(UINT)) > buf_size)) {
		tml::SetValue(dst_res, -1);

		return (val);
	}

	val |= (static_cast<UINT>(buf[buf_index++]) & 0xFF) << 24;
	val |= (static_cast<UINT>(buf[buf_index++]) & 0xFF) << 16;
	val |= (static_cast<UINT>(buf[buf_index++]) & 0xFF) <<  8;
	val |= (static_cast<UINT>(buf[buf_index++]) & 0xFF) <<  0;

	return (val);
}


/**
 * @brief ReadUINT_L関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 * @return val (value)
 */
UINT tml::MemoryUtil::ReadUINT_L(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	UINT val = 0U;

	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return (val);
		}
	}

	if ((buf == nullptr)
	|| ((buf_index + sizeof(UINT)) > buf_size)) {
		tml::SetValue(dst_res, -1);

		return (val);
	}

	val |= (static_cast<UINT>(buf[buf_index++]) & 0xFF) <<  0;
	val |= (static_cast<UINT>(buf[buf_index++]) & 0xFF) <<  8;
	val |= (static_cast<UINT>(buf[buf_index++]) & 0xFF) << 16;
	val |= (static_cast<UINT>(buf[buf_index++]) & 0xFF) << 24;

	return (val);
}


/**
 * @brief ReadLONGLONG_B関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 * @return val (value)
 */
LONGLONG tml::MemoryUtil::ReadLONGLONG_B(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	LONGLONG val = 0LL;

	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return (val);
		}
	}

	if ((buf == nullptr)
	|| ((buf_index + sizeof(LONGLONG)) > buf_size)) {
		tml::SetValue(dst_res, -1);

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
 * @brief ReadLONGLONG_L関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 * @return val (value)
 */
LONGLONG tml::MemoryUtil::ReadLONGLONG_L(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	LONGLONG val = 0LL;

	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return (val);
		}
	}

	if ((buf == nullptr)
	|| ((buf_index + sizeof(LONGLONG)) > buf_size)) {
		tml::SetValue(dst_res, -1);

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
 * @brief ReadULONGLONG_B関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 * @return val (value)
 */
ULONGLONG tml::MemoryUtil::ReadULONGLONG_B(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	ULONGLONG val = 0ULL;

	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return (val);
		}
	}

	if ((buf == nullptr)
	|| ((buf_index + sizeof(ULONGLONG)) > buf_size)) {
		tml::SetValue(dst_res, -1);

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
 * @brief ReadULONGLONG_L関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 * @return val (value)
 */
ULONGLONG tml::MemoryUtil::ReadULONGLONG_L(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	ULONGLONG val = 0ULL;

	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return (val);
		}
	}

	if ((buf == nullptr)
	|| ((buf_index + sizeof(ULONGLONG)) > buf_size)) {
		tml::SetValue(dst_res, -1);

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
 * @brief ReadFLOAT_B関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 * @return val (value)
 */
FLOAT tml::MemoryUtil::ReadFLOAT_B(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	FLOAT val = 0.0f;
	UINT tmp_val = tml::MemoryUtil::ReadUINT_B(buf, buf_size, buf_index, dst_res);

	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return (val);
		}
	}

	tml::MemoryUtil::Copy(&val, reinterpret_cast<FLOAT *>(&tmp_val), 1U);

	if (std::isnan(val)) {
		val = 0.0f;
	}

	return (val);
}


/**
 * @brief ReadFLOAT_L関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 * @return val (value)
 */
FLOAT tml::MemoryUtil::ReadFLOAT_L(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	FLOAT val = 0.0f;
	UINT tmp_val = tml::MemoryUtil::ReadUINT_L(buf, buf_size, buf_index, dst_res);

	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return (val);
		}
	}

	tml::MemoryUtil::Copy(&val, reinterpret_cast<FLOAT *>(&tmp_val), 1U);

	if (std::isnan(val)) {
		val = 0.0f;
	}

	return (val);
}


/**
 * @brief ReadDOUBLE_B関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 * @return val (value)
 */
DOUBLE tml::MemoryUtil::ReadDOUBLE_B(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	DOUBLE val = 0.0;
	ULONGLONG tmp_val = tml::MemoryUtil::ReadULONGLONG_B(buf, buf_size, buf_index, dst_res);

	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return (val);
		}
	}

	tml::MemoryUtil::Copy(&val, reinterpret_cast<DOUBLE *>(&tmp_val), 1U);

	if (std::isnan(val)) {
		val = 0.0;
	}

	return (val);
}


/**
 * @brief ReadDOUBLE_L関数
 *
 * Create関数不要
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 * @return val (value)
 */
DOUBLE tml::MemoryUtil::ReadDOUBLE_L(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	DOUBLE val = 0.0;
	ULONGLONG tmp_val = tml::MemoryUtil::ReadULONGLONG_L(buf, buf_size, buf_index, dst_res);

	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return (val);
		}
	}

	tml::MemoryUtil::Copy(&val, reinterpret_cast<DOUBLE *>(&tmp_val), 1U);

	if (std::isnan(val)) {
		val = 0.0;
	}

	return (val);
}


/**
 * @brief ReadArray関数
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
 * NULLP=指定無し,0未満=失敗
 * @return dst_ary (dst_array)
 */
BYTE *tml::MemoryUtil::ReadArray(BYTE *dst_ary, const size_t dst_ary_size, const BYTE *buf, const size_t buf_size, size_t &buf_index, const size_t read_size, INT *dst_res)
{
	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return (dst_ary);
		}
	}

	if ((buf == nullptr)
	|| ((buf_index + read_size) > buf_size)
	|| (read_size > dst_ary_size)) {
		tml::SetValue(dst_res, -1);

		return (dst_ary);
	}

	tml::MemoryUtil::Copy(dst_ary, &buf[buf_index], read_size);
	buf_index += read_size;

	return (dst_ary);
}


/**
 * @brief ReadString_B関数
 *
 * Create関数不要
 *
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 * @return dst_str (dst_string)
 */
CHAR *tml::MemoryUtil::ReadString_B(CHAR *dst_str, const size_t dst_str_size, BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	if ((dst_str == nullptr)
	|| (dst_str_size <= 0U)) {
		tml::SetValue(dst_res, -1);

		return (dst_str);
	}

	dst_str[0] = 0;

	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return (dst_str);
		}
	}

	size_t str_size = static_cast<size_t>(tml::MemoryUtil::ReadUSHORT_B(buf, buf_size, buf_index, dst_res)) & 0xFFFF;

	if (((buf_index + str_size) > buf_size)
	|| ((str_size + sizeof(CHAR)) > dst_str_size)) {
		tml::SetValue(dst_res, -1);

		return (dst_str);
	}

	tml::MemoryUtil::Copy(reinterpret_cast<BYTE *>(dst_str), &buf[buf_index], str_size);
	buf_index += str_size;

	dst_str[str_size] = 0;

	return (dst_str);
}


/**
 * @brief ReadString_L関数
 *
 * Create関数不要
 *
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 * @return dst_str (dst_string)
 */
CHAR *tml::MemoryUtil::ReadString_L(CHAR *dst_str, const size_t dst_str_size, BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	if ((dst_str == nullptr)
	|| (dst_str_size <= 0U)) {
		tml::SetValue(dst_res, -1);

		return (dst_str);
	}

	dst_str[0] = 0;

	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return (dst_str);
		}
	}

	size_t str_size = static_cast<size_t>(tml::MemoryUtil::ReadUSHORT_L(buf, buf_size, buf_index, dst_res)) & 0xFFFF;

	if (((buf_index + str_size) > buf_size)
	|| ((str_size + sizeof(CHAR)) > dst_str_size)) {
		tml::SetValue(dst_res, -1);

		return (dst_str);
	}

	tml::MemoryUtil::Copy(reinterpret_cast<BYTE *>(dst_str), &buf[buf_index], str_size);
	buf_index += str_size;

	dst_str[str_size] = 0;

	return (dst_str);
}


/**
 * @brief ReadString_B関数
 *
 * Create関数不要
 *
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 * @return dst_str (dst_string)
 */
WCHAR *tml::MemoryUtil::ReadString_B(WCHAR *dst_str, const size_t dst_str_size, BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	if ((dst_str == nullptr)
	|| (dst_str_size <= 0U)) {
		tml::SetValue(dst_res, -1);

		return (dst_str);
	}

	dst_str[0] = 0;

	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return (dst_str);
		}
	}

	size_t str_size = static_cast<size_t>(tml::MemoryUtil::ReadUSHORT_B(buf, buf_size, buf_index, dst_res)) & 0xFFFF;

	if (((buf_index + str_size) > buf_size)
	|| ((str_size + sizeof(WCHAR)) > dst_str_size)) {
		tml::SetValue(dst_res, -1);

		return (dst_str);
	}

	tml::MemoryUtil::Copy(reinterpret_cast<BYTE *>(dst_str), &buf[buf_index], str_size);
	buf_index += str_size;

	dst_str[str_size >> 1] = 0;

	return (dst_str);
}


/**
 * @brief ReadString_L関数
 *
 * Create関数不要
 *
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 * @return dst_str (dst_string)
 */
WCHAR *tml::MemoryUtil::ReadString_L(WCHAR *dst_str, const size_t dst_str_size, BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	if ((dst_str == nullptr)
	|| (dst_str_size <= 0U)) {
		tml::SetValue(dst_res, -1);

		return (dst_str);
	}

	dst_str[0] = 0;

	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return (dst_str);
		}
	}

	size_t str_size = static_cast<size_t>(tml::MemoryUtil::ReadUSHORT_L(buf, buf_size, buf_index, dst_res)) & 0xFFFF;

	if (((buf_index + str_size) > buf_size)
	|| ((str_size + sizeof(WCHAR)) > dst_str_size)) {
		tml::SetValue(dst_res, -1);

		return (dst_str);
	}

	tml::MemoryUtil::Copy(reinterpret_cast<BYTE *>(dst_str), &buf[buf_index], str_size);
	buf_index += str_size;

	dst_str[str_size >> 1] = 0;

	return (dst_str);
}


/**
 * @brief WriteCHAR関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteCHAR(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const CHAR val, INT *dst_res)
{
	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return;
		}
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + sizeof(CHAR)) > dst_buf_size)) {
		tml::SetValue(dst_res, -1);

		return;
	}

	dst_buf[dst_buf_index++] = val;

	return;
}


/**
 * @brief WriteUCHAR関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteUCHAR(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const UCHAR val, INT *dst_res)
{
	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return;
		}
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + sizeof(UCHAR)) > dst_buf_size)) {
		tml::SetValue(dst_res, -1);

		return;
	}

	dst_buf[dst_buf_index++] = val;

	return;
}


/**
 * @brief WriteSHORT_B関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteSHORT_B(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const SHORT val, INT *dst_res)
{
	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return;
		}
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + sizeof(SHORT)) > dst_buf_size)) {
		tml::SetValue(dst_res, -1);

		return;
	}

	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 8) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 0) & 0xFF);

	return;
}


/**
 * @brief WriteSHORT_L関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteSHORT_L(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const SHORT val, INT *dst_res)
{
	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return;
		}
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + sizeof(SHORT)) > dst_buf_size)) {
		tml::SetValue(dst_res, -1);

		return;
	}

	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 0) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 8) & 0xFF);

	return;
}


/**
 * @brief WriteUSHORT_B関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteUSHORT_B(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const USHORT val, INT *dst_res)
{
	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return;
		}
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + sizeof(USHORT)) > dst_buf_size)) {
		tml::SetValue(dst_res, -1);

		return;
	}

	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 8) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 0) & 0xFF);

	return;
}


/**
 * @brief WriteUSHORT_L関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteUSHORT_L(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const USHORT val, INT *dst_res)
{
	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return;
		}
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + sizeof(USHORT)) > dst_buf_size)) {
		tml::SetValue(dst_res, -1);

		return;
	}

	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 0) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 8) & 0xFF);

	return;
}


/**
 * @brief WriteINT_B関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteINT_B(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const INT val, INT *dst_res)
{
	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return;
		}
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + sizeof(INT)) > dst_buf_size)) {
		tml::SetValue(dst_res, -1);

		return;
	}

	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 24) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 16) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >>  8) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >>  0) & 0xFF);

	return;
}


/**
 * @brief WriteINT_L関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteINT_L(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const INT val, INT *dst_res)
{
	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return;
		}
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + sizeof(INT)) > dst_buf_size)) {
		tml::SetValue(dst_res, -1);

		return;
	}

	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >>  0) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >>  8) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 16) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 24) & 0xFF);

	return;
}


/**
 * @brief WriteUINT_B関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteUINT_B(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const UINT val, INT *dst_res)
{
	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return;
		}
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + sizeof(UINT)) > dst_buf_size)) {
		tml::SetValue(dst_res, -1);

		return;
	}

	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 24) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 16) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >>  8) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >>  0) & 0xFF);

	return;
}


/**
 * @brief WriteUINT_L関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteUINT_L(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const UINT val, INT *dst_res)
{
	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return;
		}
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + sizeof(UINT)) > dst_buf_size)) {
		tml::SetValue(dst_res, -1);

		return;
	}

	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >>  0) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >>  8) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 16) & 0xFF);
	dst_buf[dst_buf_index++] = static_cast<BYTE>((val >> 24) & 0xFF);

	return;
}


/**
 * @brief WriteLONGLONG_B関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteLONGLONG_B(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const LONGLONG val, INT *dst_res)
{
	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return;
		}
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + sizeof(LONGLONG)) > dst_buf_size)) {
		tml::SetValue(dst_res, -1);

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
 * @brief WriteLONGLONG_L関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteLONGLONG_L(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const LONGLONG val, INT *dst_res)
{
	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return;
		}
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + sizeof(LONGLONG)) > dst_buf_size)) {
		tml::SetValue(dst_res, -1);

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
 * @brief WriteULONGLONG_B関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteULONGLONG_B(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const ULONGLONG val, INT *dst_res)
{
	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return;
		}
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + sizeof(ULONGLONG)) > dst_buf_size)) {
		tml::SetValue(dst_res, -1);

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
 * @brief WriteULONGLONG_L関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteULONGLONG_L(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const ULONGLONG val, INT *dst_res)
{
	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return;
		}
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + sizeof(ULONGLONG)) > dst_buf_size)) {
		tml::SetValue(dst_res, -1);

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
 * @brief WriteFLOAT_B関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteFLOAT_B(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const FLOAT val, INT *dst_res)
{
	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return;
		}
	}

	UINT tmp_val = 0U;

	tml::MemoryUtil::Copy(&tmp_val, reinterpret_cast<const UINT *>(&val), 1U);

	tml::MemoryUtil::WriteUINT_B(dst_buf, dst_buf_size, dst_buf_index, tmp_val, dst_res);

	return;
}


/**
 * @brief WriteFLOAT_L関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteFLOAT_L(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const FLOAT val, INT *dst_res)
{
	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return;
		}
	}

	UINT tmp_val = 0U;

	tml::MemoryUtil::Copy(&tmp_val, reinterpret_cast<const UINT *>(&val), 1U);

	tml::MemoryUtil::WriteUINT_L(dst_buf, dst_buf_size, dst_buf_index, tmp_val, dst_res);

	return;
}


/**
 * @brief WriteDOUBLE_B関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteDOUBLE_B(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const DOUBLE val, INT *dst_res)
{
	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return;
		}
	}

	ULONGLONG tmp_val = 0ULL;

	tml::MemoryUtil::Copy(&tmp_val, reinterpret_cast<const ULONGLONG *>(&val), 1U);

	tml::MemoryUtil::WriteULONGLONG_B(dst_buf, dst_buf_size, dst_buf_index, tmp_val, dst_res);

	return;
}


/**
 * @brief WriteDOUBLE_L関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteDOUBLE_L(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const DOUBLE val, INT *dst_res)
{
	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return;
		}
	}

	ULONGLONG tmp_val = 0ULL;

	tml::MemoryUtil::Copy(&tmp_val, reinterpret_cast<const ULONGLONG *>(&val), 1U);

	tml::MemoryUtil::WriteULONGLONG_L(dst_buf, dst_buf_size, dst_buf_index, tmp_val, dst_res);

	return;
}


/**
 * @brief WriteArray関数
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
 * NULLP=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteArray(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const BYTE *ary, const size_t ary_size, const size_t write_size, INT *dst_res)
{
	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return;
		}
	}

	if ((dst_buf == nullptr)
	|| ((dst_buf_index + write_size) > dst_buf_size)
	|| (write_size > ary_size)) {
		tml::SetValue(dst_res, -1);

		return;
	}

	tml::MemoryUtil::Copy(&dst_buf[dst_buf_index], ary, write_size);
	dst_buf_index += write_size;

	return;
}


/**
 * @brief WriteString_B関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param str (string)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteString_B(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const CHAR *str, INT *dst_res)
{
	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return;
		}
	}

	size_t str_size = strlen(str);

	tml::MemoryUtil::WriteUSHORT_B(dst_buf, dst_buf_size, dst_buf_index, static_cast<USHORT>(str_size), dst_res);
	tml::MemoryUtil::WriteArray(dst_buf, dst_buf_size, dst_buf_index, reinterpret_cast<const BYTE *>(str), str_size, str_size, dst_res);

	return;
}


/**
 * @brief WriteString_L関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param str (string)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteString_L(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const CHAR *str, INT *dst_res)
{
	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return;
		}
	}

	size_t str_size = strlen(str);

	tml::MemoryUtil::WriteUSHORT_L(dst_buf, dst_buf_size, dst_buf_index, static_cast<USHORT>(str_size), dst_res);
	tml::MemoryUtil::WriteArray(dst_buf, dst_buf_size, dst_buf_index, reinterpret_cast<const BYTE *>(str), str_size, str_size, dst_res);

	return;
}


/**
 * @brief WriteString_B関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param str (string)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteString_B(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const WCHAR *str, INT *dst_res)
{
	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return;
		}
	}

	size_t str_size = wcslen(str) << 1;

	tml::MemoryUtil::WriteUSHORT_B(dst_buf, dst_buf_size, dst_buf_index, static_cast<USHORT>(str_size), dst_res);
	tml::MemoryUtil::WriteArray(dst_buf, dst_buf_size, dst_buf_index, reinterpret_cast<const BYTE *>(str), str_size, str_size, dst_res);

	return;
}


/**
 * @brief WriteString_L関数
 *
 * Create関数不要
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param str (string)
 * @param dst_res (dst_result)<br>
 * NULLP=指定無し,0未満=失敗
 */
void tml::MemoryUtil::WriteString_L(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const WCHAR *str, INT *dst_res)
{
	if (dst_res != nullptr) {
		if ((*dst_res) < 0) {
			return;
		}
	}

	size_t str_size = wcslen(str) << 1;

	tml::MemoryUtil::WriteUSHORT_L(dst_buf, dst_buf_size, dst_buf_index, static_cast<USHORT>(str_size), dst_res);
	tml::MemoryUtil::WriteArray(dst_buf, dst_buf_size, dst_buf_index, reinterpret_cast<const BYTE *>(str), str_size, str_size, dst_res);

	return;
}
