/**
 * @file
 * @brief ShadowShaderConstantBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ShaderConstantBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief ShadowShaderConstantBufferDescクラス
 */
class ShadowShaderConstantBufferDesc : public tml::graphic::ShaderConstantBufferDesc
{
public:

public:
	ShadowShaderConstantBufferDesc();
	virtual ~ShadowShaderConstantBufferDesc();

	virtual void Init(void);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief ShadowShaderConstantBufferクラス
 */
class ShadowShaderConstantBuffer : public tml::graphic::ShaderConstantBuffer
{
public: ShadowShaderConstantBuffer(const tml::graphic::ShadowShaderConstantBuffer &) = delete;
public: tml::graphic::ShadowShaderConstantBuffer &operator =(const tml::graphic::ShadowShaderConstantBuffer &) = delete;
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
	tml::graphic::ShadowShaderConstantBuffer::ELEMENT *element_;

private:
	void Release(void);

public:
	ShadowShaderConstantBuffer();
	virtual ~ShadowShaderConstantBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::ShadowShaderConstantBufferDesc &);

	void UpdateBuffer(void);
	tml::graphic::ShadowShaderConstantBuffer::ELEMENT *GetElement(void);
	//void SetElement(const UINT);
};
}
}


/**
 * @brief UpdateBuffer関数
 */
inline void tml::graphic::ShadowShaderConstantBuffer::UpdateBuffer(void)
{
	tml::graphic::ShaderConstantBuffer::UpdateBuffer(this->element_);

	return;
}


/**
 * @brief GetElement関数
 * @return element (element)<br>
 * nullptr=失敗
 */
inline tml::graphic::ShadowShaderConstantBuffer::ELEMENT *tml::graphic::ShadowShaderConstantBuffer::GetElement(void)
{
	return (tml::graphic::ShaderConstantBuffer::GetElement(this->element_));
}
