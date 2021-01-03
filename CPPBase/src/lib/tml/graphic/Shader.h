/**
 * @file
 * @brief Shaderヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "GraphicResource.h"


namespace tml {
/**
 * @brief ShaderDescクラス
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
 * @brief Shaderクラス
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
