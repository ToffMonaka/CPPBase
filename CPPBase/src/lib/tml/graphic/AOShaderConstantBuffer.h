/**
 * @file
 * @brief AOShaderConstantBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ShaderConstantBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief AOShaderConstantBufferDescクラス
 */
class AOShaderConstantBufferDesc : public tml::graphic::ShaderConstantBufferDesc
{
public:

public:
	AOShaderConstantBufferDesc();
	virtual ~AOShaderConstantBufferDesc();

	virtual void Init(void);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief AOShaderConstantBufferクラス
 */
class AOShaderConstantBuffer : public tml::graphic::ShaderConstantBuffer
{
public: AOShaderConstantBuffer(const tml::graphic::AOShaderConstantBuffer &) = delete;
public: tml::graphic::AOShaderConstantBuffer &operator =(const tml::graphic::AOShaderConstantBuffer &) = delete;
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
	tml::graphic::AOShaderConstantBuffer::ELEMENT *element_;

private:
	void Release(void);

public:
	AOShaderConstantBuffer();
	virtual ~AOShaderConstantBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::AOShaderConstantBufferDesc &);

	void UpdateBuffer(void);
	tml::graphic::AOShaderConstantBuffer::ELEMENT *GetElement(void);
	//void SetElement(const UINT);
};
}
}


/**
 * @brief UpdateBuffer関数
 */
inline void tml::graphic::AOShaderConstantBuffer::UpdateBuffer(void)
{
	tml::graphic::ShaderConstantBuffer::UpdateBuffer(this->element_);

	return;
}


/**
 * @brief GetElement関数
 * @return element (element)<br>
 * nullptr=失敗
 */
inline tml::graphic::AOShaderConstantBuffer::ELEMENT *tml::graphic::AOShaderConstantBuffer::GetElement(void)
{
	return (tml::graphic::ShaderConstantBuffer::GetElement(this->element_));
}
