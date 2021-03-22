/**
 * @file
 * @brief SpriteModelLayerShaderStructuredBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathFLOAT.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief SpriteModelLayerShaderStructuredBufferDescクラス
 */
class SpriteModelLayerShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

protected:
	void Release(void);

public:
	SpriteModelLayerShaderStructuredBufferDesc();
	virtual ~SpriteModelLayerShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::SpriteModelLayerShaderStructuredBufferDesc::Release(void)
{
	tml::graphic::ShaderStructuredBufferDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief SpriteModelLayerShaderStructuredBufferクラス
 */
class SpriteModelLayerShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: SpriteModelLayerShaderStructuredBuffer(const tml::graphic::SpriteModelLayerShaderStructuredBuffer &) = delete;
public: tml::graphic::SpriteModelLayerShaderStructuredBuffer &operator =(const tml::graphic::SpriteModelLayerShaderStructuredBuffer &) = delete;
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
	SpriteModelLayerShaderStructuredBuffer();
	virtual ~SpriteModelLayerShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::SpriteModelLayerShaderStructuredBufferDesc &);

	tml::graphic::SpriteModelLayerShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	tml::graphic::SpriteModelLayerShaderStructuredBuffer::ELEMENT *GetElementFast(const UINT);
	void SetElement(const UINT, const bool);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::SpriteModelLayerShaderStructuredBuffer::Release(void)
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
inline tml::graphic::SpriteModelLayerShaderStructuredBuffer::ELEMENT *tml::graphic::SpriteModelLayerShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement<tml::graphic::SpriteModelLayerShaderStructuredBuffer::ELEMENT>(index));
}


/**
 * @brief GetElementFast関数
 * @param index (index)
 * @return element (element)<br>
 * nullptr=失敗
 */
inline tml::graphic::SpriteModelLayerShaderStructuredBuffer::ELEMENT *tml::graphic::SpriteModelLayerShaderStructuredBuffer::GetElementFast(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementFast<tml::graphic::SpriteModelLayerShaderStructuredBuffer::ELEMENT>(index));
}
