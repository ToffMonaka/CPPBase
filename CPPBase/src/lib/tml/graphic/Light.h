/**
 * @file
 * @brief Light�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "GraphicResource.h"


namespace tml {
/**
 * @brief LightDesc�N���X
 */
class LightDesc : public tml::GraphicResourceDesc
{
public:

public:
	LightDesc();
	virtual ~LightDesc();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief Light�N���X
 */
class Light : public tml::GraphicResource
{
public: Light(const tml::Light &) = delete;
public: tml::Light &operator =(const tml::Light &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

private:
	void Release(void);

public:
	Light();
	virtual ~Light();

	virtual void Init(void);
	INT Create(const tml::LightDesc &);
};
}
