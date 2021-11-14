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
	Transform3D(const tml::XMFLOAT3EX &);
	Transform3D(const tml::XMFLOAT3EX &, const tml::XMFLOAT4EX &);
	Transform3D(const tml::Transform3D &);
	tml::Transform3D &operator =(const tml::Transform3D &);
	Transform3D(tml::Transform3D &&) noexcept;
	tml::Transform3D &operator =(tml::Transform3D &&) noexcept;
	virtual ~Transform3D();

	virtual void Init(void);
	virtual void Init(const tml::XMFLOAT3EX &);
	virtual void Init(const tml::XMFLOAT3EX &, const tml::XMFLOAT4EX &);
};
}


/**
 * @brief Release関数
 */
inline void tml::Transform3D::Release(void)
{
	return;
}
