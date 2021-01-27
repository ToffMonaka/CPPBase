/**
 * @file
 * @brief FogShaderStructuredBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief FogShaderStructuredBufferDescクラス
 */
class FogShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

public:
	FogShaderStructuredBufferDesc();
	virtual ~FogShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief FogShaderStructuredBufferクラス
 */
class FogShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: FogShaderStructuredBuffer(const tml::graphic::FogShaderStructuredBuffer &) = delete;
public: tml::graphic::FogShaderStructuredBuffer &operator =(const tml::graphic::FogShaderStructuredBuffer &) = delete;
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
	tml::graphic::FogShaderStructuredBuffer::ELEMENT *element_ary_;

private:
	void Release(void);

public:
	FogShaderStructuredBuffer();
	virtual ~FogShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::FogShaderStructuredBufferDesc &);

	void UpdateBuffer(void);
	tml::graphic::FogShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	//void SetElement(const UINT, tml::graphic::Fog *, const bool, const XMMATRIX &);
};
}
}


/**
 * @brief UpdateBuffer関数
 */
inline void tml::graphic::FogShaderStructuredBuffer::UpdateBuffer(void)
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
inline tml::graphic::FogShaderStructuredBuffer::ELEMENT *tml::graphic::FogShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement(this->element_ary_, index));
}
