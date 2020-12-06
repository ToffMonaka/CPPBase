/**
 * @file
 * @brief MemoryUtil�R�[�h�t�@�C��
 */


#include "MemoryUtil.h"


tml::ThreadFix tml::MemoryUtil::th_fix_;
std::unique_ptr<tml::MemoryUtilEngine> tml::MemoryUtil::engine_;


/**
 * @brief Init�֐�
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
 * @brief Create�֐�
 * @param engine (engine)
 * @return res (result)<br>
 * 0����=���s
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
 * @brief SetBufferIndex�֐�
 *
 * Create�֐��s�v
 *
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param index (index)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
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
 * @brief AddBufferIndex�֐�
 *
 * Create�֐��s�v
 *
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param add_index (add_index)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
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
 * @brief ReadBufferCHAR�֐�
 *
 * Create�֐��s�v
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 * @return val (value)
 */
CHAR tml::MemoryUtil::ReadBufferCHAR(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
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
 * @brief ReadBufferUCHAR�֐�
 *
 * Create�֐��s�v
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 * @return val (value)
 */
UCHAR tml::MemoryUtil::ReadBufferUCHAR(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
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
 * @brief ReadBufferSHORT_B�֐�
 *
 * Create�֐��s�v
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 * @return val (value)
 */
SHORT tml::MemoryUtil::ReadBufferSHORT_B(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
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
 * @brief ReadBufferSHORT_L�֐�
 *
 * Create�֐��s�v
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 * @return val (value)
 */
SHORT tml::MemoryUtil::ReadBufferSHORT_L(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
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
 * @brief ReadBufferUSHORT_B�֐�
 *
 * Create�֐��s�v
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 * @return val (value)
 */
USHORT tml::MemoryUtil::ReadBufferUSHORT_B(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
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
 * @brief ReadBufferUSHORT_L�֐�
 *
 * Create�֐��s�v
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 * @return val (value)
 */
USHORT tml::MemoryUtil::ReadBufferUSHORT_L(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
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
 * @brief ReadBufferINT_B�֐�
 *
 * Create�֐��s�v
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 * @return val (value)
 */
INT tml::MemoryUtil::ReadBufferINT_B(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
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
 * @brief ReadBufferINT_L�֐�
 *
 * Create�֐��s�v
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 * @return val (value)
 */
INT tml::MemoryUtil::ReadBufferINT_L(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
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
 * @brief ReadBufferUINT_B�֐�
 *
 * Create�֐��s�v
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 * @return val (value)
 */
UINT tml::MemoryUtil::ReadBufferUINT_B(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
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
 * @brief ReadBufferUINT_L�֐�
 *
 * Create�֐��s�v
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 * @return val (value)
 */
UINT tml::MemoryUtil::ReadBufferUINT_L(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
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
 * @brief ReadBufferLONGLONG_B�֐�
 *
 * Create�֐��s�v
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 * @return val (value)
 */
LONGLONG tml::MemoryUtil::ReadBufferLONGLONG_B(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
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
 * @brief ReadBufferLONGLONG_L�֐�
 *
 * Create�֐��s�v
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 * @return val (value)
 */
LONGLONG tml::MemoryUtil::ReadBufferLONGLONG_L(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
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
 * @brief ReadBufferULONGLONG_B�֐�
 *
 * Create�֐��s�v
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 * @return val (value)
 */
ULONGLONG tml::MemoryUtil::ReadBufferULONGLONG_B(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
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
 * @brief ReadBufferULONGLONG_L�֐�
 *
 * Create�֐��s�v
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 * @return val (value)
 */
ULONGLONG tml::MemoryUtil::ReadBufferULONGLONG_L(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
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
 * @brief ReadBufferFLOAT_B�֐�
 *
 * Create�֐��s�v
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 * @return val (value)
 */
FLOAT tml::MemoryUtil::ReadBufferFLOAT_B(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	FLOAT val = 0.0f;
	UINT tmp_val = tml::MemoryUtil::ReadBufferUINT_B(buf, buf_size, buf_index, dst_res);

	if (tml::CheckResult(dst_res)) {
		return (val);
	}

	tml::MemoryUtil::Copy(&val, reinterpret_cast<FLOAT *>(&tmp_val), 1U);

	if (std::isnan(val)) {
		val = 0.0f;
	}

	return (val);
}


/**
 * @brief ReadBufferFLOAT_L�֐�
 *
 * Create�֐��s�v
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 * @return val (value)
 */
FLOAT tml::MemoryUtil::ReadBufferFLOAT_L(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	FLOAT val = 0.0f;
	UINT tmp_val = tml::MemoryUtil::ReadBufferUINT_L(buf, buf_size, buf_index, dst_res);

	if (tml::CheckResult(dst_res)) {
		return (val);
	}

	tml::MemoryUtil::Copy(&val, reinterpret_cast<FLOAT *>(&tmp_val), 1U);

	if (std::isnan(val)) {
		val = 0.0f;
	}

	return (val);
}


/**
 * @brief ReadBufferDOUBLE_B�֐�
 *
 * Create�֐��s�v
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 * @return val (value)
 */
DOUBLE tml::MemoryUtil::ReadBufferDOUBLE_B(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	DOUBLE val = 0.0;
	ULONGLONG tmp_val = tml::MemoryUtil::ReadBufferULONGLONG_B(buf, buf_size, buf_index, dst_res);

	if (tml::CheckResult(dst_res)) {
		return (val);
	}

	tml::MemoryUtil::Copy(&val, reinterpret_cast<DOUBLE *>(&tmp_val), 1U);

	if (std::isnan(val)) {
		val = 0.0;
	}

	return (val);
}


/**
 * @brief ReadBufferDOUBLE_L�֐�
 *
 * Create�֐��s�v
 *
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 * @return val (value)
 */
DOUBLE tml::MemoryUtil::ReadBufferDOUBLE_L(const BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
{
	DOUBLE val = 0.0;
	ULONGLONG tmp_val = tml::MemoryUtil::ReadBufferULONGLONG_L(buf, buf_size, buf_index, dst_res);

	if (tml::CheckResult(dst_res)) {
		return (val);
	}

	tml::MemoryUtil::Copy(&val, reinterpret_cast<DOUBLE *>(&tmp_val), 1U);

	if (std::isnan(val)) {
		val = 0.0;
	}

	return (val);
}


/**
 * @brief ReadBufferArray�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_ary (dst_array)
 * @param dst_ary_size (dst_array_size)
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param read_size (read_size)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
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

	tml::MemoryUtil::Copy(dst_ary, &buf[buf_index], read_size);
	buf_index += read_size;

	return (dst_ary);
}


/**
 * @brief ReadBufferString_B�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 * @return dst_str (dst_string)
 */
CHAR *tml::MemoryUtil::ReadBufferString_B(CHAR *dst_str, const size_t dst_str_size, BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
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

	size_t str_size = static_cast<size_t>(tml::MemoryUtil::ReadBufferUSHORT_B(buf, buf_size, buf_index, dst_res)) & 0xFFFF;

	if (((buf_index + str_size) > buf_size)
	|| ((str_size + sizeof(CHAR)) > dst_str_size)) {
		tml::SetResult(dst_res, -1);

		return (dst_str);
	}

	tml::MemoryUtil::Copy(reinterpret_cast<BYTE *>(dst_str), &buf[buf_index], str_size);
	buf_index += str_size;

	dst_str[str_size] = 0;

	return (dst_str);
}


/**
 * @brief ReadBufferString_L�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 * @return dst_str (dst_string)
 */
CHAR *tml::MemoryUtil::ReadBufferString_L(CHAR *dst_str, const size_t dst_str_size, BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
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

	size_t str_size = static_cast<size_t>(tml::MemoryUtil::ReadBufferUSHORT_L(buf, buf_size, buf_index, dst_res)) & 0xFFFF;

	if (((buf_index + str_size) > buf_size)
	|| ((str_size + sizeof(CHAR)) > dst_str_size)) {
		tml::SetResult(dst_res, -1);

		return (dst_str);
	}

	tml::MemoryUtil::Copy(reinterpret_cast<BYTE *>(dst_str), &buf[buf_index], str_size);
	buf_index += str_size;

	dst_str[str_size] = 0;

	return (dst_str);
}


/**
 * @brief ReadBufferString_B�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 * @return dst_str (dst_string)
 */
WCHAR *tml::MemoryUtil::ReadBufferString_B(WCHAR *dst_str, const size_t dst_str_size, BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
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

	size_t str_size = static_cast<size_t>(tml::MemoryUtil::ReadBufferUSHORT_B(buf, buf_size, buf_index, dst_res)) & 0xFFFF;

	if (((buf_index + str_size) > buf_size)
	|| ((str_size + sizeof(WCHAR)) > dst_str_size)) {
		tml::SetResult(dst_res, -1);

		return (dst_str);
	}

	tml::MemoryUtil::Copy(reinterpret_cast<BYTE *>(dst_str), &buf[buf_index], str_size);
	buf_index += str_size;

	dst_str[str_size >> 1] = 0;

	return (dst_str);
}


/**
 * @brief ReadBufferString_L�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param buf_index (buffer_index)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 * @return dst_str (dst_string)
 */
WCHAR *tml::MemoryUtil::ReadBufferString_L(WCHAR *dst_str, const size_t dst_str_size, BYTE *buf, const size_t buf_size, size_t &buf_index, INT *dst_res)
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

	size_t str_size = static_cast<size_t>(tml::MemoryUtil::ReadBufferUSHORT_L(buf, buf_size, buf_index, dst_res)) & 0xFFFF;

	if (((buf_index + str_size) > buf_size)
	|| ((str_size + sizeof(WCHAR)) > dst_str_size)) {
		tml::SetResult(dst_res, -1);

		return (dst_str);
	}

	tml::MemoryUtil::Copy(reinterpret_cast<BYTE *>(dst_str), &buf[buf_index], str_size);
	buf_index += str_size;

	dst_str[str_size >> 1] = 0;

	return (dst_str);
}


/**
 * @brief WriteBufferCHAR�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 */
void tml::MemoryUtil::WriteBufferCHAR(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const CHAR val, INT *dst_res)
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
 * @brief WriteBufferUCHAR�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 */
void tml::MemoryUtil::WriteBufferUCHAR(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const UCHAR val, INT *dst_res)
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
 * @brief WriteBufferSHORT_B�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 */
void tml::MemoryUtil::WriteBufferSHORT_B(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const SHORT val, INT *dst_res)
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
 * @brief WriteBufferSHORT_L�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 */
void tml::MemoryUtil::WriteBufferSHORT_L(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const SHORT val, INT *dst_res)
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
 * @brief WriteBufferUSHORT_B�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 */
void tml::MemoryUtil::WriteBufferUSHORT_B(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const USHORT val, INT *dst_res)
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
 * @brief WriteBufferUSHORT_L�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 */
void tml::MemoryUtil::WriteBufferUSHORT_L(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const USHORT val, INT *dst_res)
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
 * @brief WriteBufferINT_B�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 */
void tml::MemoryUtil::WriteBufferINT_B(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const INT val, INT *dst_res)
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
 * @brief WriteBufferINT_L�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 */
void tml::MemoryUtil::WriteBufferINT_L(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const INT val, INT *dst_res)
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
 * @brief WriteBufferUINT_B�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 */
void tml::MemoryUtil::WriteBufferUINT_B(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const UINT val, INT *dst_res)
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
 * @brief WriteBufferUINT_L�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 */
void tml::MemoryUtil::WriteBufferUINT_L(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const UINT val, INT *dst_res)
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
 * @brief WriteBufferLONGLONG_B�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 */
void tml::MemoryUtil::WriteBufferLONGLONG_B(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const LONGLONG val, INT *dst_res)
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
 * @brief WriteBufferLONGLONG_L�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 */
void tml::MemoryUtil::WriteBufferLONGLONG_L(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const LONGLONG val, INT *dst_res)
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
 * @brief WriteBufferULONGLONG_B�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 */
void tml::MemoryUtil::WriteBufferULONGLONG_B(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const ULONGLONG val, INT *dst_res)
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
 * @brief WriteBufferULONGLONG_L�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 */
void tml::MemoryUtil::WriteBufferULONGLONG_L(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const ULONGLONG val, INT *dst_res)
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
 * @brief WriteBufferFLOAT_B�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 */
void tml::MemoryUtil::WriteBufferFLOAT_B(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const FLOAT val, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	UINT tmp_val = 0U;

	tml::MemoryUtil::Copy(&tmp_val, reinterpret_cast<const UINT *>(&val), 1U);

	tml::MemoryUtil::WriteBufferUINT_B(dst_buf, dst_buf_size, dst_buf_index, tmp_val, dst_res);

	return;
}


/**
 * @brief WriteBufferFLOAT_L�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 */
void tml::MemoryUtil::WriteBufferFLOAT_L(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const FLOAT val, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	UINT tmp_val = 0U;

	tml::MemoryUtil::Copy(&tmp_val, reinterpret_cast<const UINT *>(&val), 1U);

	tml::MemoryUtil::WriteBufferUINT_L(dst_buf, dst_buf_size, dst_buf_index, tmp_val, dst_res);

	return;
}


/**
 * @brief WriteBufferDOUBLE_B�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 */
void tml::MemoryUtil::WriteBufferDOUBLE_B(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const DOUBLE val, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	ULONGLONG tmp_val = 0ULL;

	tml::MemoryUtil::Copy(&tmp_val, reinterpret_cast<const ULONGLONG *>(&val), 1U);

	tml::MemoryUtil::WriteBufferULONGLONG_B(dst_buf, dst_buf_size, dst_buf_index, tmp_val, dst_res);

	return;
}


/**
 * @brief WriteBufferDOUBLE_L�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param val (value)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 */
void tml::MemoryUtil::WriteBufferDOUBLE_L(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const DOUBLE val, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	ULONGLONG tmp_val = 0ULL;

	tml::MemoryUtil::Copy(&tmp_val, reinterpret_cast<const ULONGLONG *>(&val), 1U);

	tml::MemoryUtil::WriteBufferULONGLONG_L(dst_buf, dst_buf_size, dst_buf_index, tmp_val, dst_res);

	return;
}


/**
 * @brief WriteBufferArray�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param ary (array)
 * @param ary_size (array_size)
 * @param write_size (write_size)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
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

	tml::MemoryUtil::Copy(&dst_buf[dst_buf_index], ary, write_size);
	dst_buf_index += write_size;

	return;
}


/**
 * @brief WriteBufferString_B�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param str (string)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 */
void tml::MemoryUtil::WriteBufferString_B(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const CHAR *str, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	size_t str_size = strlen(str);

	tml::MemoryUtil::WriteBufferUSHORT_B(dst_buf, dst_buf_size, dst_buf_index, static_cast<USHORT>(str_size), dst_res);
	tml::MemoryUtil::WriteBufferArray(dst_buf, dst_buf_size, dst_buf_index, reinterpret_cast<const BYTE *>(str), str_size, str_size, dst_res);

	return;
}


/**
 * @brief WriteBufferString_L�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param str (string)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 */
void tml::MemoryUtil::WriteBufferString_L(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const CHAR *str, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	size_t str_size = strlen(str);

	tml::MemoryUtil::WriteBufferUSHORT_L(dst_buf, dst_buf_size, dst_buf_index, static_cast<USHORT>(str_size), dst_res);
	tml::MemoryUtil::WriteBufferArray(dst_buf, dst_buf_size, dst_buf_index, reinterpret_cast<const BYTE *>(str), str_size, str_size, dst_res);

	return;
}


/**
 * @brief WriteBufferString_B�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param str (string)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 */
void tml::MemoryUtil::WriteBufferString_B(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const WCHAR *str, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	size_t str_size = wcslen(str) << 1;

	tml::MemoryUtil::WriteBufferUSHORT_B(dst_buf, dst_buf_size, dst_buf_index, static_cast<USHORT>(str_size), dst_res);
	tml::MemoryUtil::WriteBufferArray(dst_buf, dst_buf_size, dst_buf_index, reinterpret_cast<const BYTE *>(str), str_size, str_size, dst_res);

	return;
}


/**
 * @brief WriteBufferString_L�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_buf (dst_buffer)
 * @param dst_buf_size (dst_buffer_size)
 * @param dst_buf_index (dst_buffer_index)
 * @param str (string)
 * @param dst_res (dst_result)<br>
 * NULLP=�w�薳��,0����=���s
 */
void tml::MemoryUtil::WriteBufferString_L(BYTE *dst_buf, const size_t dst_buf_size, size_t &dst_buf_index, const WCHAR *str, INT *dst_res)
{
	if (tml::CheckResult(dst_res)) {
		return;
	}

	size_t str_size = wcslen(str) << 1;

	tml::MemoryUtil::WriteBufferUSHORT_L(dst_buf, dst_buf_size, dst_buf_index, static_cast<USHORT>(str_size), dst_res);
	tml::MemoryUtil::WriteBufferArray(dst_buf, dst_buf_size, dst_buf_index, reinterpret_cast<const BYTE *>(str), str_size, str_size, dst_res);

	return;
}
