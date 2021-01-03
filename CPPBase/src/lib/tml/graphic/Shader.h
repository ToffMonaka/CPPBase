/**
 * @file
 * @brief Shader�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "GraphicResource.h"


namespace tml {
/**
 * @brief ShaderDesc�N���X
 */
class ShaderDesc : public tml::GraphicResourceDesc
{
public:

public:
	ShaderDesc();
	virtual ~ShaderDesc();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief Shader�N���X
 */
class Shader : public tml::GraphicResource
{
public: Shader(const tml::Shader &) = delete;
public: tml::Shader &operator =(const tml::Shader &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

private:
	void Release(void);

public:
	Shader();
	virtual ~Shader();

	virtual void Init(void);
	INT Create(const tml::ShaderDesc &);
};
}
