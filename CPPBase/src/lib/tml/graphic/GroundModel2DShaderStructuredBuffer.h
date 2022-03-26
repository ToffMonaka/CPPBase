/**
 * @file
 * @brief GroundModel2DShaderStructuredBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathVector.h"
#include "../math/XNAMathMatrix.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief GroundModel2DShaderStructuredBufferDescクラス
 */
class GroundModel2DShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

private:
	void Release(void);

public:
	GroundModel2DShaderStructuredBufferDesc();
	virtual ~GroundModel2DShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::GroundModel2DShaderStructuredBufferDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief GroundModel2DShaderStructuredBufferクラス
 */
class GroundModel2DShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: GroundModel2DShaderStructuredBuffer(const tml::graphic::GroundModel2DShaderStructuredBuffer &) = delete;
public: tml::graphic::GroundModel2DShaderStructuredBuffer &operator =(const tml::graphic::GroundModel2DShaderStructuredBuffer &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	/**
	 * @brief ELEMENT構造体
	 */
	typedef struct ELEMENT_
	{
		tml::XMFLOAT4X4EX world_view_projection_matrix;
		tml::XMFLOAT4EX color;
		tml::XMUINT2EX tileset_tile_count;
		UINT dummy1;
		UINT dummy2;

		/**
		 * @brief コンストラクタ
		 */
		ELEMENT_() :
			world_view_projection_matrix(tml::ConstantUtil::XNAMATH::IDENTITY_MATRIX::TYPE),
			color(1.0f),
			tileset_tile_count(0U),
			dummy1(0U),
			dummy2(0U)
		{
			return;
		};
	} ELEMENT;

private:
	const tml::graphic::GroundModel2DShaderStructuredBufferDesc *desc_;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);

public:
	GroundModel2DShaderStructuredBuffer();
	virtual ~GroundModel2DShaderStructuredBuffer();

	virtual void Init(void);

	const tml::graphic::GroundModel2DShaderStructuredBufferDesc *GetDesc(void) const;
	tml::graphic::GroundModel2DShaderStructuredBuffer::ELEMENT *GetElementArray(void);
	tml::graphic::GroundModel2DShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	tml::graphic::GroundModel2DShaderStructuredBuffer::ELEMENT *GetElementFast(const UINT);
	void SetElement(const UINT, const DirectX::XMMATRIX &, const DirectX::XMMATRIX &, const DirectX::XMMATRIX &, const tml::XMFLOAT4EX &, const tml::XMUINT2EX &);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::GroundModel2DShaderStructuredBuffer::Release(void)
{
	return;
}


/**
 * @brief GetDesc関数
 * @return desc (desc)
 */
inline const tml::graphic::GroundModel2DShaderStructuredBufferDesc *tml::graphic::GroundModel2DShaderStructuredBuffer::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief GetElementArray関数
 * @return element_ary (element_array)
 */
inline tml::graphic::GroundModel2DShaderStructuredBuffer::ELEMENT *tml::graphic::GroundModel2DShaderStructuredBuffer::GetElementArray(void)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementArray<tml::graphic::GroundModel2DShaderStructuredBuffer::ELEMENT>());
}


/**
 * @brief GetElement関数
 * @param index (index)
 * @return element (element)<br>
 * nullptr=失敗
 */
inline tml::graphic::GroundModel2DShaderStructuredBuffer::ELEMENT *tml::graphic::GroundModel2DShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement<tml::graphic::GroundModel2DShaderStructuredBuffer::ELEMENT>(index));
}


/**
 * @brief GetElementFast関数
 * @param index (index)
 * @return element (element)<br>
 * nullptr=失敗
 */
inline tml::graphic::GroundModel2DShaderStructuredBuffer::ELEMENT *tml::graphic::GroundModel2DShaderStructuredBuffer::GetElementFast(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementFast<tml::graphic::GroundModel2DShaderStructuredBuffer::ELEMENT>(index));
}
