/**
 * @file
 * @brief Material�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "GraphicResource.h"


namespace tml {
/**
 * @brief MaterialDesc�N���X
 */
class MaterialDesc : public tml::GraphicResourceDesc
{
public:

public:
	MaterialDesc();
	virtual ~MaterialDesc();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief Material�N���X
 */
class Material : public tml::GraphicResource
{
public: Material(const tml::Material &) = delete;
public: tml::Material &operator =(const tml::Material &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

private:
	void Release(void);

public:
	Material();
	virtual ~Material();

	virtual void Init(void);
	INT Create(const tml::MaterialDesc &);
};
}
