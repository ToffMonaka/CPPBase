/**
 * @file
 * @brief Light3DShaderStructuredBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathVector.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief Light3DShaderStructuredBufferDescクラス
 */
class Light3DShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

private:
	void Release(void);

public:
	Light3DShaderStructuredBufferDesc();
	virtual ~Light3DShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Light3DShaderStructuredBufferDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Light3DShaderStructuredBufferクラス
 */
class Light3DShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: Light3DShaderStructuredBuffer(const tml::graphic::Light3DShaderStructuredBuffer &) = delete;
public: tml::graphic::Light3DShaderStructuredBuffer &operator =(const tml::graphic::Light3DShaderStructuredBuffer &) = delete;
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
	Light3DShaderStructuredBuffer();
	virtual ~Light3DShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::Light3DShaderStructuredBufferDesc &);

	tml::graphic::Light3DShaderStructuredBuffer::ELEMENT *GetElementArray(void);
	tml::graphic::Light3DShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	tml::graphic::Light3DShaderStructuredBuffer::ELEMENT *GetElementFast(const UINT);
	void SetElement(const UINT, const tml::graphic::Light3D *);
	void SetElement(const UINT, const UINT, const tml::graphic::Light3D *const *);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Light3DShaderStructuredBuffer::Release(void)
{
	return;
}


/**
 * @brief GetElementArray関数
 * @return element_ary (element_array)
 */
inline tml::graphic::Light3DShaderStructuredBuffer::ELEMENT *tml::graphic::Light3DShaderStructuredBuffer::GetElementArray(void)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementArray<tml::graphic::Light3DShaderStructuredBuffer::ELEMENT>());
}


/**
 * @brief GetElement関数
 * @param index (index)
 * @return element (element)<br>
 * nullptr=失敗
 */
inline tml::graphic::Light3DShaderStructuredBuffer::ELEMENT *tml::graphic::Light3DShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement<tml::graphic::Light3DShaderStructuredBuffer::ELEMENT>(index));
}


/**
 * @brief GetElementFast関数
 * @param index (index)
 * @return element (element)<br>
 * nullptr=失敗
 */
inline tml::graphic::Light3DShaderStructuredBuffer::ELEMENT *tml::graphic::Light3DShaderStructuredBuffer::GetElementFast(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementFast<tml::graphic::Light3DShaderStructuredBuffer::ELEMENT>(index));
}
