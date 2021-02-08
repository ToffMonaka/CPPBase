/**
 * @file
 * @brief ModelShaderConstantBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ShaderConstantBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief ModelShaderConstantBufferDescクラス
 */
class ModelShaderConstantBufferDesc : public tml::graphic::ShaderConstantBufferDesc
{
public:

protected:
	void Release(void);

public:
	ModelShaderConstantBufferDesc();
	virtual ~ModelShaderConstantBufferDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::ModelShaderConstantBufferDesc::Release(void)
{
	tml::graphic::ShaderConstantBufferDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief ModelShaderConstantBufferクラス
 */
class ModelShaderConstantBuffer : public tml::graphic::ShaderConstantBuffer
{
public: ModelShaderConstantBuffer(const tml::graphic::ModelShaderConstantBuffer &) = delete;
public: tml::graphic::ModelShaderConstantBuffer &operator =(const tml::graphic::ModelShaderConstantBuffer &) = delete;
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
	tml::graphic::ModelShaderConstantBuffer::ELEMENT *element_;

protected:
	void Release(void);

public:
	ModelShaderConstantBuffer();
	virtual ~ModelShaderConstantBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::ModelShaderConstantBufferDesc &);

	void UpdateBuffer(void);
	tml::graphic::ModelShaderConstantBuffer::ELEMENT *GetElement(void);
	//void SetElement(const UINT);
};
}
}


/**
 * @brief UpdateBuffer関数
 */
inline void tml::graphic::ModelShaderConstantBuffer::UpdateBuffer(void)
{
	tml::graphic::ShaderConstantBuffer::UpdateBuffer(this->element_);

	return;
}


/**
 * @brief GetElement関数
 * @return element (element)<br>
 * nullptr=失敗
 */
inline tml::graphic::ModelShaderConstantBuffer::ELEMENT *tml::graphic::ModelShaderConstantBuffer::GetElement(void)
{
	return (tml::graphic::ShaderConstantBuffer::GetElement(this->element_));
}
