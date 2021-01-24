/**
 * @file
 * @brief FogShaderConstantBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ShaderConstantBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief FogShaderConstantBufferDescクラス
 */
class FogShaderConstantBufferDesc : public tml::graphic::ShaderConstantBufferDesc
{
public:

public:
	FogShaderConstantBufferDesc();
	virtual ~FogShaderConstantBufferDesc();

	virtual void Init(void);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief FogShaderConstantBufferクラス
 */
class FogShaderConstantBuffer : public tml::graphic::ShaderConstantBuffer
{
public: FogShaderConstantBuffer(const tml::graphic::FogShaderConstantBuffer &) = delete;
public: tml::graphic::FogShaderConstantBuffer &operator =(const tml::graphic::FogShaderConstantBuffer &) = delete;
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
		}
	} ELEMENT;

private:
	tml::graphic::FogShaderConstantBuffer::ELEMENT *element_;

private:
	void Release(void);

public:
	FogShaderConstantBuffer();
	virtual ~FogShaderConstantBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::FogShaderConstantBufferDesc &);

	void UpdateBuffer(void);
	tml::graphic::FogShaderConstantBuffer::ELEMENT *GetElement(void);
	//void SetElement(const UINT);
};
}
}


/**
 * @brief UpdateBuffer関数
 */
inline void tml::graphic::FogShaderConstantBuffer::UpdateBuffer(void)
{
	tml::graphic::ShaderConstantBuffer::UpdateBuffer(this->element_);

	return;
}


/**
 * @brief GetElement関数
 * @return element (element)<br>
 * nullptr=失敗
 */
inline tml::graphic::FogShaderConstantBuffer::ELEMENT *tml::graphic::FogShaderConstantBuffer::GetElement(void)
{
	return (tml::graphic::ShaderConstantBuffer::GetElement(this->element_));
}
