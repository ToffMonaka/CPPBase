/**
 * @file
 * @brief RandomUtilEngineヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include <random>
#include "../thread/SpinThreadLock.h"


namespace tml {
/**
 * @brief RandomUtilEngineクラス
 *
 * インターフェースパターン
 */
class RandomUtilEngine
{
public: RandomUtilEngine(const RandomUtilEngine &) = delete;
public: RandomUtilEngine &operator =(const RandomUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	std::mt19937 gen_;
	tml::SpinThreadLock gen_th_lock_;

protected:
	void Release(void);
	INT Create(void);

public:
	RandomUtilEngine();
	virtual ~RandomUtilEngine();

	virtual void Init(void);

	CHAR GetCHAR(void);
	CHAR GetCHAR(const CHAR, const CHAR);
	SHORT GetSHORT(void);
	SHORT GetSHORT(const SHORT, const SHORT);
	INT GetINT(void);
	INT GetINT(const INT, const INT);
	LONGLONG GetLONGLONG(void);
	LONGLONG GetLONGLONG(const LONGLONG, const LONGLONG);
	FLOAT GetFLOAT(void);
	FLOAT GetFLOAT(const FLOAT, const FLOAT);
	DOUBLE GetDOUBLE(void);
	DOUBLE GetDOUBLE(const DOUBLE, const DOUBLE);
};
}
