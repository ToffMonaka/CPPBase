/**
 * @file
 * @brief SpriteModelShaderStructuredBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMath.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief SpriteModelShaderStructuredBufferDescクラス
 */
class SpriteModelShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

protected:
	void Release(void);

public:
	SpriteModelShaderStructuredBufferDesc();
	virtual ~SpriteModelShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::SpriteModelShaderStructuredBufferDesc::Release(void)
{
	tml::graphic::ShaderStructuredBufferDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief SpriteModelShaderStructuredBufferクラス
 */
class SpriteModelShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: SpriteModelShaderStructuredBuffer(const tml::graphic::SpriteModelShaderStructuredBuffer &) = delete;
public: tml::graphic::SpriteModelShaderStructuredBuffer &operator =(const tml::graphic::SpriteModelShaderStructuredBuffer &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	/**
	 * @brief ELEMENT構造体
	 */
	typedef struct ELEMENT_
	{
		tml::XMFLOAT4X4EX world_projection_matrix;
		tml::XMFLOAT4EX color;

		/**
		 * @brief コンストラクタ
		 */
		ELEMENT_() :
			world_projection_matrix(tml::ConstantUtil::XNAMATH::IDENTITY_MATRIX::TYPE),
			color(1.0f)
		{
			return;
		};
	} ELEMENT;

private:
	tml::graphic::SpriteModelShaderStructuredBuffer::ELEMENT *element_ary_;

protected:
	void Release(void);

public:
	SpriteModelShaderStructuredBuffer();
	virtual ~SpriteModelShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::SpriteModelShaderStructuredBufferDesc &);

	void UpdateBuffer(void);
	tml::graphic::SpriteModelShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	void SetElement(const UINT, const XMMATRIX &, const XMMATRIX &, const tml::XMFLOAT4EX &);
};
}
}


/**
 * @brief UpdateBuffer関数
 */
inline void tml::graphic::SpriteModelShaderStructuredBuffer::UpdateBuffer(void)
{
	tml::graphic::ShaderStructuredBuffer::UpdateBuffer(this->element_ary_);

	return;
}


/**
 * @brief GetElement関数
 * @param index (index)
 * @return element (element)<br>
 * nullptr=失敗
 */
inline tml::graphic::SpriteModelShaderStructuredBuffer::ELEMENT *tml::graphic::SpriteModelShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement(this->element_ary_, index));
}
