/**
 * @file
 * @brief Light2DShaderStructuredBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathVector.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief Light2DShaderStructuredBufferDescクラス
 */
class Light2DShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

private:
	void Release(void);

public:
	Light2DShaderStructuredBufferDesc();
	virtual ~Light2DShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Light2DShaderStructuredBufferDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Light2DShaderStructuredBufferクラス
 */
class Light2DShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: Light2DShaderStructuredBuffer(const tml::graphic::Light2DShaderStructuredBuffer &) = delete;
public: tml::graphic::Light2DShaderStructuredBuffer &operator =(const tml::graphic::Light2DShaderStructuredBuffer &) = delete;
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
	const tml::graphic::Light2DShaderStructuredBufferDesc *desc_;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);

public:
	Light2DShaderStructuredBuffer();
	virtual ~Light2DShaderStructuredBuffer();

	virtual void Init(void);

	const tml::graphic::Light2DShaderStructuredBufferDesc *GetDesc(void) const;
	tml::graphic::Light2DShaderStructuredBuffer::ELEMENT *GetElementArray(void);
	tml::graphic::Light2DShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	tml::graphic::Light2DShaderStructuredBuffer::ELEMENT *GetElementFast(const UINT);
	void SetElement(const UINT, const tml::graphic::Light2D *);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Light2DShaderStructuredBuffer::Release(void)
{
	return;
}


/**
 * @brief GetDesc関数
 * @return desc (desc)
 */
inline const tml::graphic::Light2DShaderStructuredBufferDesc *tml::graphic::Light2DShaderStructuredBuffer::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief GetElementArray関数
 * @return element_ary (element_array)
 */
inline tml::graphic::Light2DShaderStructuredBuffer::ELEMENT *tml::graphic::Light2DShaderStructuredBuffer::GetElementArray(void)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementArray<tml::graphic::Light2DShaderStructuredBuffer::ELEMENT>());
}


/**
 * @brief GetElement関数
 * @param index (index)
 * @return element (element)<br>
 * nullptr=失敗
 */
inline tml::graphic::Light2DShaderStructuredBuffer::ELEMENT *tml::graphic::Light2DShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement<tml::graphic::Light2DShaderStructuredBuffer::ELEMENT>(index));
}


/**
 * @brief GetElementFast関数
 * @param index (index)
 * @return element (element)<br>
 * nullptr=失敗
 */
inline tml::graphic::Light2DShaderStructuredBuffer::ELEMENT *tml::graphic::Light2DShaderStructuredBuffer::GetElementFast(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementFast<tml::graphic::Light2DShaderStructuredBuffer::ELEMENT>(index));
}
