/**
 * @file
 * @brief FrameRate�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"


namespace tml {
/**
 * @brief FrameRate�N���X
 */
class FrameRate
{
private:
	UINT limit_;
	UINT cnt_;
	DOUBLE fps_;
	std::chrono::steady_clock::time_point start_time_;
	std::chrono::steady_clock::time_point work_start_time_;
	tml::TIME_REAL elapsed_time_;
	tml::TIME_REAL work_elapsed_time_;
	tml::TIME_REAL total_elapsed_time_;
	tml::TIME_REAL one_time_;
	tml::TIME_REAL sleep_time_;
	tml::TIME_REAL average_sleep_time_;
	tml::TIME_REAL wait_time_;
	tml::TIME_REAL over_time_;
	bool started_flg_;

protected:
	void Release(void);

public:
	FrameRate();
	FrameRate(const tml::FrameRate &);
	tml::FrameRate &operator =(const tml::FrameRate &);
	FrameRate(tml::FrameRate &&) noexcept;
	tml::FrameRate &operator =(tml::FrameRate &&) noexcept;
	virtual ~FrameRate();

	virtual void Init(void);

	INT Start(const UINT);
	void Stop(void);
	void Update(void);
	UINT GetLimit(void) const;
	UINT GetCount(void) const;
	DOUBLE GetFPS(void) const;
	const tml::TIME_REAL &GetElapsedTime(void) const;
};
}


/**
 * @brief Release�֐�
 */
inline void tml::FrameRate::Release(void)
{
	return;
}


/**
 * @brief GetLimit�֐�
 * @return limit (limit)
 */
inline UINT tml::FrameRate::GetLimit(void) const
{
	return (this->limit_);
}


/**
 * @brief GetCount�֐�
 * @return cnt (count)
 */
inline UINT tml::FrameRate::GetCount(void) const
{
	return (this->cnt_);
}


/**
 * @brief GetFPS�֐�
 * @return fps (fps)
 */
inline DOUBLE tml::FrameRate::GetFPS(void) const
{
	return (this->fps_);
}


/**
 * @brief GetElapsedTime�֐�
 * @return elapsed_time (elapsed_time)
 */
inline const tml::TIME_REAL &tml::FrameRate::GetElapsedTime(void) const
{
	return (this->elapsed_time_);
}
