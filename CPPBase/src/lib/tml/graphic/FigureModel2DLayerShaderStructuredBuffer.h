/**
 * @file
 * @brief FigureModel2DLayerShaderStructuredBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathVector.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
class FigureModel2DLayer;
}
}


namespace tml {
namespace graphic {
/**
 * @brief FigureModel2DLayerShaderStructuredBufferDescクラス
 */
class FigureModel2DLayerShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

private:
	void Release(void);

public:
	FigureModel2DLayerShaderStructuredBufferDesc();
	virtual ~FigureModel2DLayerShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::FigureModel2DLayerShaderStructuredBufferDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief FigureModel2DLayerShaderStructuredBufferクラス
 */
class FigureModel2DLayerShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: FigureModel2DLayerShaderStructuredBuffer(const tml::graphic::FigureModel2DLayerShaderStructuredBuffer &) = delete;
public: tml::graphic::FigureModel2DLayerShaderStructuredBuffer &operator =(const tml::graphic::FigureModel2DLayerShaderStructuredBuffer &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	/**
	 * @brief ELEMENT構造体
	 */
	typedef struct ELEMENT_
	{
		UINT texture_flag;
		UINT dummy1;
		UINT dummy2;
		UINT dummy3;
		tml::XMUINT2EX diffuse_texture_rect_position;
		tml::XMUINT2EX diffuse_texture_rect_size;

		/**
		 * @brief コンストラクタ
		 */
		ELEMENT_() :
			texture_flag(0U),
			dummy1(0U),
			dummy2(0U),
			dummy3(0U),
			diffuse_texture_rect_position(0U),
			diffuse_texture_rect_size(0U)
		{
			return;
		};
	} ELEMENT;

private:
	const tml::graphic::FigureModel2DLayerShaderStructuredBufferDesc *desc_;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);

public:
	FigureModel2DLayerShaderStructuredBuffer();
	virtual ~FigureModel2DLayerShaderStructuredBuffer();

	virtual void Init(void);

	const tml::graphic::FigureModel2DLayerShaderStructuredBufferDesc *GetDesc(void) const;
	tml::graphic::FigureModel2DLayerShaderStructuredBuffer::ELEMENT *GetElementArray(void);
	tml::graphic::FigureModel2DLayerShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	tml::graphic::FigureModel2DLayerShaderStructuredBuffer::ELEMENT *GetElementFast(const UINT);
	void SetElement(const UINT, const tml::graphic::Texture *);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::FigureModel2DLayerShaderStructuredBuffer::Release(void)
{
	return;
}


/**
 * @brief GetDesc関数
 * @return desc (desc)
 */
inline const tml::graphic::FigureModel2DLayerShaderStructuredBufferDesc *tml::graphic::FigureModel2DLayerShaderStructuredBuffer::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief GetElementArray関数
 * @return element_ary (element_array)
 */
inline tml::graphic::FigureModel2DLayerShaderStructuredBuffer::ELEMENT *tml::graphic::FigureModel2DLayerShaderStructuredBuffer::GetElementArray(void)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementArray<tml::graphic::FigureModel2DLayerShaderStructuredBuffer::ELEMENT>());
}


/**
 * @brief GetElement関数
 * @param index (index)
 * @return element (element)<br>
 * nullptr=失敗
 */
inline tml::graphic::FigureModel2DLayerShaderStructuredBuffer::ELEMENT *tml::graphic::FigureModel2DLayerShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement<tml::graphic::FigureModel2DLayerShaderStructuredBuffer::ELEMENT>(index));
}


/**
 * @brief GetElementFast関数
 * @param index (index)
 * @return element (element)<br>
 * nullptr=失敗
 */
inline tml::graphic::FigureModel2DLayerShaderStructuredBuffer::ELEMENT *tml::graphic::FigureModel2DLayerShaderStructuredBuffer::GetElementFast(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementFast<tml::graphic::FigureModel2DLayerShaderStructuredBuffer::ELEMENT>(index));
}
