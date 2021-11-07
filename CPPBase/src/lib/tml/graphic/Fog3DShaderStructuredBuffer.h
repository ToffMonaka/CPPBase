/**
 * @file
 * @brief Fog3DShaderStructuredBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathVector.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief Fog3DShaderStructuredBufferDescクラス
 */
class Fog3DShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

private:
	void Release(void);

public:
	Fog3DShaderStructuredBufferDesc();
	virtual ~Fog3DShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Fog3DShaderStructuredBufferDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Fog3DShaderStructuredBufferクラス
 */
class Fog3DShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: Fog3DShaderStructuredBuffer(const tml::graphic::Fog3DShaderStructuredBuffer &) = delete;
public: tml::graphic::Fog3DShaderStructuredBuffer &operator =(const tml::graphic::Fog3DShaderStructuredBuffer &) = delete;
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
	Fog3DShaderStructuredBuffer();
	virtual ~Fog3DShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::Fog3DShaderStructuredBufferDesc &);

	tml::graphic::Fog3DShaderStructuredBuffer::ELEMENT *GetElementArray(void);
	tml::graphic::Fog3DShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	tml::graphic::Fog3DShaderStructuredBuffer::ELEMENT *GetElementFast(const UINT);
	void SetElement(const UINT, const tml::graphic::Fog3D *);
	void SetElement(const UINT, const UINT, const tml::graphic::Fog3D *const *);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Fog3DShaderStructuredBuffer::Release(void)
{
	return;
}


/**
 * @brief GetElementArray関数
 * @return element_ary (element_array)
 */
inline tml::graphic::Fog3DShaderStructuredBuffer::ELEMENT *tml::graphic::Fog3DShaderStructuredBuffer::GetElementArray(void)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementArray<tml::graphic::Fog3DShaderStructuredBuffer::ELEMENT>());
}


/**
 * @brief GetElement関数
 * @param index (index)
 * @return element (element)<br>
 * nullptr=失敗
 */
inline tml::graphic::Fog3DShaderStructuredBuffer::ELEMENT *tml::graphic::Fog3DShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement<tml::graphic::Fog3DShaderStructuredBuffer::ELEMENT>(index));
}


/**
 * @brief GetElementFast関数
 * @param index (index)
 * @return element (element)<br>
 * nullptr=失敗
 */
inline tml::graphic::Fog3DShaderStructuredBuffer::ELEMENT *tml::graphic::Fog3DShaderStructuredBuffer::GetElementFast(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementFast<tml::graphic::Fog3DShaderStructuredBuffer::ELEMENT>(index));
}
