/**
 * @file
 * @brief RandomUtilEngine�w�b�_�[�t�@�C��
 */
#pragma once


#include "../ConstantUtil.h"
#include "RandomSeed.h"
#include "../thread/SpinThreadLock.h"


namespace tml {
/**
 * @brief RandomUtilEngine�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class RandomUtilEngine
{
public: RandomUtilEngine(const RandomUtilEngine &) = delete;
public: RandomUtilEngine &operator =(const RandomUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::RandomSeed seed_;
	tml::SpinThreadLock seed_th_lock_;

protected:
	void Release(void);
	INT Create(void);

public:
	RandomUtilEngine();
	virtual ~RandomUtilEngine();

	virtual void Init(void);

	INT GetINT(void);
	INT GetINT(const INT, const INT);
	UINT GetUINT(void);
	UINT GetUINT(const UINT, const UINT);
	LONGLONG GetLONGLONG(void);
	LONGLONG GetLONGLONG(const LONGLONG, const LONGLONG);
	ULONGLONG GetULONGLONG(void);
	ULONGLONG GetULONGLONG(const ULONGLONG, const ULONGLONG);
	FLOAT GetFLOAT(void);
	FLOAT GetFLOAT(const FLOAT, const FLOAT);
	DOUBLE GetDOUBLE(void);
	DOUBLE GetDOUBLE(const DOUBLE, const DOUBLE);
};
}


/**
 * @brief GetINT�֐�
 * @return val (value)
 */
inline INT tml::RandomUtilEngine::GetINT(void)
{tml::ThreadLockBlock th_lock_block(this->seed_th_lock_);
	return (this->seed_.GetINT());
}


/**
 * @brief GetINT�֐�
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline INT tml::RandomUtilEngine::GetINT(const INT min_val, const INT max_val)
{tml::ThreadLockBlock th_lock_block(this->seed_th_lock_);
	return (this->seed_.GetINT(min_val, max_val));
}


/**
 * @brief GetUINT�֐�
 * @return val (value)
 */
inline UINT tml::RandomUtilEngine::GetUINT(void)
{tml::ThreadLockBlock th_lock_block(this->seed_th_lock_);
	return (this->seed_.GetUINT());
}


/**
 * @brief GetUINT�֐�
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline UINT tml::RandomUtilEngine::GetUINT(const UINT min_val, const UINT max_val)
{tml::ThreadLockBlock th_lock_block(this->seed_th_lock_);
	return (this->seed_.GetUINT(min_val, max_val));
}


/**
 * @brief GetLONGLONG�֐�
 * @return val (value)
 */
inline LONGLONG tml::RandomUtilEngine::GetLONGLONG(void)
{tml::ThreadLockBlock th_lock_block(this->seed_th_lock_);
	return (this->seed_.GetLONGLONG());
}


/**
 * @brief GetLONGLONG�֐�
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline LONGLONG tml::RandomUtilEngine::GetLONGLONG(const LONGLONG min_val, const LONGLONG max_val)
{tml::ThreadLockBlock th_lock_block(this->seed_th_lock_);
	return (this->seed_.GetLONGLONG(min_val, max_val));
}


/**
 * @brief GetULONGLONG�֐�
 * @return val (value)
 */
inline ULONGLONG tml::RandomUtilEngine::GetULONGLONG(void)
{tml::ThreadLockBlock th_lock_block(this->seed_th_lock_);
	return (this->seed_.GetULONGLONG());
}


/**
 * @brief GetULONGLONG�֐�
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline ULONGLONG tml::RandomUtilEngine::GetULONGLONG(const ULONGLONG min_val, const ULONGLONG max_val)
{tml::ThreadLockBlock th_lock_block(this->seed_th_lock_);
	return (this->seed_.GetULONGLONG(min_val, max_val));
}


/**
 * @brief GetFLOAT�֐�
 * @return val (value)
 */
inline FLOAT tml::RandomUtilEngine::GetFLOAT(void)
{tml::ThreadLockBlock th_lock_block(this->seed_th_lock_);
	return (this->seed_.GetFLOAT());
}


/**
 * @brief GetFLOAT�֐�
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline FLOAT tml::RandomUtilEngine::GetFLOAT(const FLOAT min_val, const FLOAT max_val)
{tml::ThreadLockBlock th_lock_block(this->seed_th_lock_);
	return (this->seed_.GetFLOAT(min_val, max_val));
}


/**
 * @brief GetDOUBLE�֐�
 * @return val (value)
 */
inline DOUBLE tml::RandomUtilEngine::GetDOUBLE(void)
{tml::ThreadLockBlock th_lock_block(this->seed_th_lock_);
	return (this->seed_.GetDOUBLE());
}


/**
 * @brief GetDOUBLE�֐�
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline DOUBLE tml::RandomUtilEngine::GetDOUBLE(const DOUBLE min_val, const DOUBLE max_val)
{tml::ThreadLockBlock th_lock_block(this->seed_th_lock_);
	return (this->seed_.GetDOUBLE(min_val, max_val));
}
