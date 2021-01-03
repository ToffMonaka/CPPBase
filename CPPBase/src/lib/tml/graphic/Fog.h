/**
 * @file
 * @brief Fog�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "GraphicResource.h"


namespace tml {
/**
 * @brief FogDesc�N���X
 */
class FogDesc : public tml::GraphicResourceDesc
{
public:

public:
	FogDesc();
	virtual ~FogDesc();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief Fog�N���X
 */
class Fog : public tml::GraphicResource
{
public: Fog(const tml::Fog &) = delete;
public: tml::Fog &operator =(const tml::Fog &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

private:
	void Release(void);

public:
	Fog();
	virtual ~Fog();

	virtual void Init(void);
	INT Create(const tml::FogDesc &);
};
}
