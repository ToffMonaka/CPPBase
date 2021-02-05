/**
 * @file
 * @brief LightShaderStructuredBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ShaderStructuredBuffer.h"
#include "Light.h"


namespace tml {
namespace graphic {
/**
 * @brief LightShaderStructuredBufferDescクラス
 */
class LightShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

public:
	LightShaderStructuredBufferDesc();
	virtual ~LightShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief LightShaderStructuredBufferクラス
 */
class LightShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: LightShaderStructuredBuffer(const tml::graphic::LightShaderStructuredBuffer &) = delete;
public: tml::graphic::LightShaderStructuredBuffer &operator =(const tml::graphic::LightShaderStructuredBuffer &) = delete;
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
	tml::graphic::LightShaderStructuredBuffer::ELEMENT *element_ary_;

private:
	void Release(void);

public:
	LightShaderStructuredBuffer();
	virtual ~LightShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::LightShaderStructuredBufferDesc &);

	void UpdateBuffer(void);
	tml::graphic::LightShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	void SetElement(const UINT, const tml::graphic::Light *);
	void SetElement(const UINT, const UINT, const tml::graphic::Light *const *);
};
}
}


/**
 * @brief UpdateBuffer関数
 */
inline void tml::graphic::LightShaderStructuredBuffer::UpdateBuffer(void)
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
inline tml::graphic::LightShaderStructuredBuffer::ELEMENT *tml::graphic::LightShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement(this->element_ary_, index));
}
