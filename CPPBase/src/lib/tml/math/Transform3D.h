/**
 * @file
 * @brief Transform3D�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "XNAMathVectorFLOAT.h"
#include "XNAMathMatrixFLOAT.h"


namespace tml {
/**
 * @brief Transform3D�N���X
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
 * @brief Release�֐�
 */
inline void tml::Transform3D::Release(void)
{
	return;
}
