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
	Transform2D(const tml::XMFLOAT2EX &);
	Transform2D(const tml::XMFLOAT2EX &, const FLOAT);
	Transform2D(const tml::Transform2D &);
	tml::Transform2D &operator =(const tml::Transform2D &);
	Transform2D(tml::Transform2D &&) noexcept;
	tml::Transform2D &operator =(tml::Transform2D &&) noexcept;
	virtual ~Transform2D();

	virtual void Init(void);
	virtual void Init(const tml::XMFLOAT2EX &);
	virtual void Init(const tml::XMFLOAT2EX &, const FLOAT);
};
}


/**
 * @brief Release関数
 */
inline void tml::Transform2D::Release(void)
{
	return;
}
