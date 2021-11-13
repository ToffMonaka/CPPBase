/**
 * @file
 * @brief Transform3Dヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "XNAMathVectorFLOAT.h"
#include "XNAMathMatrixFLOAT.h"


namespace tml {
/**
 * @brief Transform3Dクラス
 */
class Transform3D
{
public:
	tml::XMFLOAT3EX position;
	tml::XMFLOAT4EX quaternion;
	tml::XMFLOAT3EX scale;

private:
	void Release(void);

public:
	Transform3D();
	virtual ~Transform3D();

	virtual void Init(void);
};
}


/**
 * @brief Release関数
 */
inline void tml::Transform3D::Release(void)
{
	return;
}
