/**
 * @file
 * @brief GroundModel2DShaderStructuredBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathFLOAT.h"
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

		/**
		 * @brief コンストラクタ
		 */
		ELEMENT_() :
			world_view_projection_matrix(tml::ConstantUtil::XNAMATH::IDENTITY_MATRIX::TYPE),
			color(1.0f)
		{
			return;
		};
	} ELEMENT;

private:
	void Release(void);

public:
	GroundModel2DShaderStructuredBuffer();
	virtual ~GroundModel2DShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::GroundModel2DShaderStructuredBufferDesc &);

	tml::graphic::GroundModel2DShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	tml::graphic::GroundModel2DShaderStructuredBuffer::ELEMENT *GetElementFast(const UINT);
	void SetElement(const UINT, const DirectX::XMMATRIX &, const DirectX::XMMATRIX &, const DirectX::XMMATRIX &, const tml::XMFLOAT4EX &);
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
