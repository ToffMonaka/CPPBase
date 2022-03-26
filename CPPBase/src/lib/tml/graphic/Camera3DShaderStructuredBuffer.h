/**
 * @file
 * @brief Camera3DShaderStructuredBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathVector.h"
#include "../math/XNAMathMatrix.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief Camera3DShaderStructuredBufferDescクラス
 */
class Camera3DShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

private:
	void Release(void);

public:
	Camera3DShaderStructuredBufferDesc();
	virtual ~Camera3DShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Camera3DShaderStructuredBufferDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Camera3DShaderStructuredBufferクラス
 */
class Camera3DShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: Camera3DShaderStructuredBuffer(const tml::graphic::Camera3DShaderStructuredBuffer &) = delete;
public: tml::graphic::Camera3DShaderStructuredBuffer &operator =(const tml::graphic::Camera3DShaderStructuredBuffer &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	/**
	 * @brief ELEMENT構造体
	 */
	typedef struct ELEMENT_
	{
		tml::XMFLOAT4X4EX view_matrix;
		tml::XMFLOAT4X4EX inverse_view_matrix;
		tml::XMFLOAT4X4EX projection_matrix;

		/**
		 * @brief コンストラクタ
		 */
		ELEMENT_() :
			view_matrix(tml::ConstantUtil::XNAMATH::IDENTITY_MATRIX::TYPE),
			inverse_view_matrix(tml::ConstantUtil::XNAMATH::IDENTITY_MATRIX::TYPE),
			projection_matrix(tml::ConstantUtil::XNAMATH::IDENTITY_MATRIX::TYPE)
		{
			return;
		};
	} ELEMENT;

private:
	const tml::graphic::Camera3DShaderStructuredBufferDesc *desc_;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);

public:
	Camera3DShaderStructuredBuffer();
	virtual ~Camera3DShaderStructuredBuffer();

	virtual void Init(void);

	const tml::graphic::Camera3DShaderStructuredBufferDesc *GetDesc(void) const;
	tml::graphic::Camera3DShaderStructuredBuffer::ELEMENT *GetElementArray(void);
	tml::graphic::Camera3DShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	tml::graphic::Camera3DShaderStructuredBuffer::ELEMENT *GetElementFast(const UINT);
	void SetElement(const UINT, const DirectX::XMMATRIX &, const DirectX::XMMATRIX &, const DirectX::XMMATRIX &);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Camera3DShaderStructuredBuffer::Release(void)
{
	return;
}


/**
 * @brief GetDesc関数
 * @return desc (desc)
 */
inline const tml::graphic::Camera3DShaderStructuredBufferDesc *tml::graphic::Camera3DShaderStructuredBuffer::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief GetElementArray関数
 * @return element_ary (element_array)
 */
inline tml::graphic::Camera3DShaderStructuredBuffer::ELEMENT *tml::graphic::Camera3DShaderStructuredBuffer::GetElementArray(void)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementArray<tml::graphic::Camera3DShaderStructuredBuffer::ELEMENT>());
}


/**
 * @brief GetElement関数
 * @param index (index)
 * @return element (element)<br>
 * nullptr=失敗
 */
inline tml::graphic::Camera3DShaderStructuredBuffer::ELEMENT *tml::graphic::Camera3DShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement<tml::graphic::Camera3DShaderStructuredBuffer::ELEMENT>(index));
}


/**
 * @brief GetElementFast関数
 * @param index (index)
 * @return element (element)<br>
 * nullptr=失敗
 */
inline tml::graphic::Camera3DShaderStructuredBuffer::ELEMENT *tml::graphic::Camera3DShaderStructuredBuffer::GetElementFast(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementFast<tml::graphic::Camera3DShaderStructuredBuffer::ELEMENT>(index));
}
