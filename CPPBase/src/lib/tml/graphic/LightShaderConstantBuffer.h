/**
 * @file
 * @brief LightShaderConstantBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ShaderConstantBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief LightShaderConstantBufferDescクラス
 */
class LightShaderConstantBufferDesc : public tml::graphic::ShaderConstantBufferDesc
{
public:

public:
	LightShaderConstantBufferDesc();
	virtual ~LightShaderConstantBufferDesc();

	virtual void Init(void);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief LightShaderConstantBufferクラス
 */
class LightShaderConstantBuffer : public tml::graphic::ShaderConstantBuffer
{
public: LightShaderConstantBuffer(const tml::graphic::LightShaderConstantBuffer &) = delete;
public: tml::graphic::LightShaderConstantBuffer &operator =(const tml::graphic::LightShaderConstantBuffer &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	/**
	 * @brief ELEMENT構造体
	 */
	typedef struct ELEMENT_
	{
		UINT dummy1;
		UINT dummy2;
		UINT dummy3;
		UINT dummy4;

		/**
		 * @brief コンストラクタ
		 */
		ELEMENT_() :
			dummy1(0U),
			dummy2(0U),
			dummy3(0U),
			dummy4(0U)
		{
			return;
		}
	} ELEMENT;

private:
	tml::graphic::LightShaderConstantBuffer::ELEMENT *element_;

private:
	void Release(void);

public:
	LightShaderConstantBuffer();
	virtual ~LightShaderConstantBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::LightShaderConstantBufferDesc &);

	void UpdateBuffer(void);
	tml::graphic::LightShaderConstantBuffer::ELEMENT *GetElement(void);
	//void SetElement(const UINT);
};
}
}


/**
 * @brief UpdateBuffer関数
 */
inline void tml::graphic::LightShaderConstantBuffer::UpdateBuffer(void)
{
	tml::graphic::ShaderConstantBuffer::UpdateBuffer(this->element_);

	return;
}


/**
 * @brief GetElement関数
 * @return element (element)<br>
 * nullptr=失敗
 */
inline tml::graphic::LightShaderConstantBuffer::ELEMENT *tml::graphic::LightShaderConstantBuffer::GetElement(void)
{
	return (tml::graphic::ShaderConstantBuffer::GetElement(this->element_));
}
