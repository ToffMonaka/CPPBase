/**
 * @file
 * @brief ConfigShaderConstantBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ShaderConstantBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief ConfigShaderConstantBufferDescクラス
 */
class ConfigShaderConstantBufferDesc : public tml::graphic::ShaderConstantBufferDesc
{
public:

private:
	void Release(void);

public:
	ConfigShaderConstantBufferDesc();
	virtual ~ConfigShaderConstantBufferDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::ConfigShaderConstantBufferDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief ConfigShaderConstantBufferクラス
 */
class ConfigShaderConstantBuffer : public tml::graphic::ShaderConstantBuffer
{
public: ConfigShaderConstantBuffer(const tml::graphic::ConfigShaderConstantBuffer &) = delete;
public: tml::graphic::ConfigShaderConstantBuffer &operator =(const tml::graphic::ConfigShaderConstantBuffer &) = delete;
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
	const tml::graphic::ConfigShaderConstantBufferDesc *desc_;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);

public:
	ConfigShaderConstantBuffer();
	virtual ~ConfigShaderConstantBuffer();

	virtual void Init(void);

	const tml::graphic::ConfigShaderConstantBufferDesc *GetDesc(void) const;
	tml::graphic::ConfigShaderConstantBuffer::ELEMENT *GetElement(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::ConfigShaderConstantBuffer::Release(void)
{
	return;
}


/**
 * @brief GetDesc関数
 * @return desc (desc)
 */
inline const tml::graphic::ConfigShaderConstantBufferDesc *tml::graphic::ConfigShaderConstantBuffer::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief GetElement関数
 * @return element (element)<br>
 * nullptr=失敗
 */
inline tml::graphic::ConfigShaderConstantBuffer::ELEMENT *tml::graphic::ConfigShaderConstantBuffer::GetElement(void)
{
	return (tml::graphic::ShaderConstantBuffer::GetElement<tml::graphic::ConfigShaderConstantBuffer::ELEMENT>());
}
