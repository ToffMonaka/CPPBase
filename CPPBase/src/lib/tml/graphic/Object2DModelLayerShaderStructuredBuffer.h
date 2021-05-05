/**
 * @file
 * @brief Object2DModelLayerShaderStructuredBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathFLOAT.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief Object2DModelLayerShaderStructuredBufferDescクラス
 */
class Object2DModelLayerShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

protected:
	void Release(void);

public:
	Object2DModelLayerShaderStructuredBufferDesc();
	virtual ~Object2DModelLayerShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Object2DModelLayerShaderStructuredBufferDesc::Release(void)
{
	tml::graphic::ShaderStructuredBufferDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Object2DModelLayerShaderStructuredBufferクラス
 */
class Object2DModelLayerShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: Object2DModelLayerShaderStructuredBuffer(const tml::graphic::Object2DModelLayerShaderStructuredBuffer &) = delete;
public: tml::graphic::Object2DModelLayerShaderStructuredBuffer &operator =(const tml::graphic::Object2DModelLayerShaderStructuredBuffer &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	/**
	 * @brief ELEMENT構造体
	 */
	typedef struct ELEMENT_
	{
		UINT diffuse_texture_flag;
		UINT dummy1;
		UINT dummy2;
		UINT dummy3;

		/**
		 * @brief コンストラクタ
		 */
		ELEMENT_() :
			diffuse_texture_flag(0U),
			dummy1(0U),
			dummy2(0U),
			dummy3(0U)
		{
			return;
		};
	} ELEMENT;

protected:
	void Release(void);

public:
	Object2DModelLayerShaderStructuredBuffer();
	virtual ~Object2DModelLayerShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::Object2DModelLayerShaderStructuredBufferDesc &);

	tml::graphic::Object2DModelLayerShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	tml::graphic::Object2DModelLayerShaderStructuredBuffer::ELEMENT *GetElementFast(const UINT);
	void SetElement(const UINT, const bool);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Object2DModelLayerShaderStructuredBuffer::Release(void)
{
	tml::graphic::ShaderStructuredBuffer::Release();

	return;
}


/**
 * @brief GetElement関数
 * @param index (index)
 * @return element (element)<br>
 * nullptr=失敗
 */
inline tml::graphic::Object2DModelLayerShaderStructuredBuffer::ELEMENT *tml::graphic::Object2DModelLayerShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement<tml::graphic::Object2DModelLayerShaderStructuredBuffer::ELEMENT>(index));
}


/**
 * @brief GetElementFast関数
 * @param index (index)
 * @return element (element)<br>
 * nullptr=失敗
 */
inline tml::graphic::Object2DModelLayerShaderStructuredBuffer::ELEMENT *tml::graphic::Object2DModelLayerShaderStructuredBuffer::GetElementFast(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementFast<tml::graphic::Object2DModelLayerShaderStructuredBuffer::ELEMENT>(index));
}
