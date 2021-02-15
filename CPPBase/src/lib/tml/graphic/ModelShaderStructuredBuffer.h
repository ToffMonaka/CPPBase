/**
 * @file
 * @brief ModelShaderStructuredBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMath.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief ModelShaderStructuredBufferDescクラス
 */
class ModelShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

protected:
	void Release(void);

public:
	ModelShaderStructuredBufferDesc();
	virtual ~ModelShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::ModelShaderStructuredBufferDesc::Release(void)
{
	tml::graphic::ShaderStructuredBufferDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief ModelShaderStructuredBufferクラス
 */
class ModelShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: ModelShaderStructuredBuffer(const tml::graphic::ModelShaderStructuredBuffer &) = delete;
public: tml::graphic::ModelShaderStructuredBuffer &operator =(const tml::graphic::ModelShaderStructuredBuffer &) = delete;
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
	tml::graphic::ModelShaderStructuredBuffer::ELEMENT *element_ary_;

protected:
	void Release(void);

public:
	ModelShaderStructuredBuffer();
	virtual ~ModelShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::ModelShaderStructuredBufferDesc &);

	void UpdateBuffer(void);
	tml::graphic::ModelShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	void SetElement(const UINT, const XMMATRIX &, const XMMATRIX &, const tml::XMFLOAT4EX &);
};
}
}


/**
 * @brief UpdateBuffer関数
 */
inline void tml::graphic::ModelShaderStructuredBuffer::UpdateBuffer(void)
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
inline tml::graphic::ModelShaderStructuredBuffer::ELEMENT *tml::graphic::ModelShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement(this->element_ary_, index));
}
