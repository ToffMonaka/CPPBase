/**
 * @file
 * @brief FrameRateヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"


namespace tml {
/**
 * @brief FrameRateクラス
 */
class FrameRate
{
public: FrameRate(const FrameRate &) = delete;
public: FrameRate &operator =(const FrameRate &) = delete;

private:
	UINT limit_;
	UINT cnt_;
	DOUBLE fps_;
	std::chrono::steady_clock::time_point one_start_time_;
	tml::TIME_REAL one_elapsed_time_;
	std::chrono::steady_clock::time_point work_one_start_time_;
	tml::TIME_REAL work_one_elapsed_time_;
	tml::TIME_REAL total_elapsed_time_;
	tml::TIME_REAL one_time_;
	tml::TIME_REAL sleep_time_;
	tml::TIME_REAL average_sleep_time_;
	tml::TIME_REAL wait_time_;
	tml::TIME_REAL over_time_;
	bool started_flg_;

public:
	FrameRate();
	virtual ~FrameRate();

	void Init(void);

	INT Start(const UINT);
	void Stop(void);
	void Update(void);
	UINT GetLimit(void) const;
	UINT GetCount(void) const;
	DOUBLE GetFPS(void) const;
};
}


/**
 * @brief GetLimit関数
 * @return limit (limit)
 */
inline UINT tml::FrameRate::GetLimit(void) const
{
	return (this->limit_);
}


/**
 * @brief GetCount関数
 * @return cnt (count)
 */
inline UINT tml::FrameRate::GetCount(void) const
{
	return (this->cnt_);
}


/**
 * @brief GetFPS関数
 * @return fps (fps)
 */
inline DOUBLE tml::FrameRate::GetFPS(void) const
{
	return (this->fps_);
}
