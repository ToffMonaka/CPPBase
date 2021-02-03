/**
 * @file
 * @brief ConfigShaderConstantBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ShaderConstantBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief ConfigShaderConstantBufferDescクラス
 */
class ConfigShaderConstantBufferDesc : public tml::graphic::ShaderConstantBufferDesc
{
public:

public:
	ConfigShaderConstantBufferDesc();
	virtual ~ConfigShaderConstantBufferDesc();

	virtual void Init(void);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief ConfigShaderConstantBufferクラス
 */
class ConfigShaderConstantBuffer : public tml::graphic::ShaderConstantBuffer
{
public: ConfigShaderConstantBuffer(const tml::graphic::ConfigShaderConstantBuffer &) = delete;
public: tml::graphic::ConfigShaderConstantBuffer &operator =(const tml::graphic::ConfigShaderConstantBuffer &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	/**
	 * @brief ELEMENT構造体
	 */
	typedef struct ELEMENT_
	{
		UINT light_count;
		UINT fog_count;
		UINT dummy1;
		UINT dummy2;

		/**
		 * @brief コンストラクタ
		 */
		ELEMENT_() :
			light_count(0U),
			fog_count(0U),
			dummy1(0U),
			dummy2(0U)
		{
			return;
		};
	} ELEMENT;

private:
	tml::graphic::ConfigShaderConstantBuffer::ELEMENT *element_;

private:
	void Release(void);

public:
	ConfigShaderConstantBuffer();
	virtual ~ConfigShaderConstantBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::ConfigShaderConstantBufferDesc &);

	void UpdateBuffer(void);
	tml::graphic::ConfigShaderConstantBuffer::ELEMENT *GetElement(void);
	void SetElement(const UINT, const UINT);
};
}
}


/**
 * @brief UpdateBuffer関数
 */
inline void tml::graphic::ConfigShaderConstantBuffer::UpdateBuffer(void)
{
	tml::graphic::ShaderConstantBuffer::UpdateBuffer(this->element_);

	return;
}


/**
 * @brief GetElement関数
 * @return element (element)<br>
 * nullptr=失敗
 */
inline tml::graphic::ConfigShaderConstantBuffer::ELEMENT *tml::graphic::ConfigShaderConstantBuffer::GetElement(void)
{
	return (tml::graphic::ShaderConstantBuffer::GetElement(this->element_));
}
