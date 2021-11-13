/**
 * @file
 * @brief Fog2DShaderStructuredBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathVector.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief Fog2DShaderStructuredBufferDescクラス
 */
class Fog2DShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

private:
	void Release(void);

public:
	Fog2DShaderStructuredBufferDesc();
	virtual ~Fog2DShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Fog2DShaderStructuredBufferDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Fog2DShaderStructuredBufferクラス
 */
class Fog2DShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: Fog2DShaderStructuredBuffer(const tml::graphic::Fog2DShaderStructuredBuffer &) = delete;
public: tml::graphic::Fog2DShaderStructuredBuffer &operator =(const tml::graphic::Fog2DShaderStructuredBuffer &) = delete;
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
		};
	} ELEMENT;

private:
	void Release(void);

public:
	Fog2DShaderStructuredBuffer();
	virtual ~Fog2DShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::Fog2DShaderStructuredBufferDesc &);

	tml::graphic::Fog2DShaderStructuredBuffer::ELEMENT *GetElementArray(void);
	tml::graphic::Fog2DShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	tml::graphic::Fog2DShaderStructuredBuffer::ELEMENT *GetElementFast(const UINT);
	void SetElement(const UINT, const tml::graphic::Fog2D *);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Fog2DShaderStructuredBuffer::Release(void)
{
	return;
}


/**
 * @brief GetElementArray関数
 * @return element_ary (element_array)
 */
inline tml::graphic::Fog2DShaderStructuredBuffer::ELEMENT *tml::graphic::Fog2DShaderStructuredBuffer::GetElementArray(void)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementArray<tml::graphic::Fog2DShaderStructuredBuffer::ELEMENT>());
}


/**
 * @brief GetElement関数
 * @param index (index)
 * @return element (element)<br>
 * nullptr=失敗
 */
inline tml::graphic::Fog2DShaderStructuredBuffer::ELEMENT *tml::graphic::Fog2DShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement<tml::graphic::Fog2DShaderStructuredBuffer::ELEMENT>(index));
}


/**
 * @brief GetElementFast関数
 * @param index (index)
 * @return element (element)<br>
 * nullptr=失敗
 */
inline tml::graphic::Fog2DShaderStructuredBuffer::ELEMENT *tml::graphic::Fog2DShaderStructuredBuffer::GetElementFast(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementFast<tml::graphic::Fog2DShaderStructuredBuffer::ELEMENT>(index));
}
