/**
 * @file
 * @brief Transform2Dヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "XNAMathVectorFLOAT.h"
#include "XNAMathMatrixFLOAT.h"


namespace tml {
/**
 * @brief Transform2Dクラス
 */
class Transform2D
{
public:
	tml::XMFLOAT2EX position;
	FLOAT angle;
	tml::XMFLOAT2EX scale;

private:
	void Release(void);

public:
	Transform2D();
	virtual ~Transform2D();

	virtual void Init(void);
};
}


/**
 * @brief Release関数
 */
inline void tml::Transform2D::Release(void)
{
	return;
}
