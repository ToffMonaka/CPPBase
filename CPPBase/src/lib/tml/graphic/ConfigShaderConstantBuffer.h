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

protected:
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
	tml::graphic::ShaderConstantBufferDesc::Release();

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
	tml::graphic::ConfigShaderConstantBuffer::ELEMENT *element_;

protected:
	void Release(void);

public:
	ConfigShaderConstantBuffer();
	virtual ~ConfigShaderConstantBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::ConfigShaderConstantBufferDesc &);

	tml::graphic::ConfigShaderConstantBuffer::ELEMENT *GetElement(void);
	void UploadCPUBuffer(void);
	void DownloadCPUBuffer(void);
};
}
}


/**
 * @brief GetElement関数
 * @return element (element)<br>
 * nullptr=失敗
 */
inline tml::graphic::ConfigShaderConstantBuffer::ELEMENT *tml::graphic::ConfigShaderConstantBuffer::GetElement(void)
{
	return (tml::graphic::ShaderConstantBuffer::GetElement(this->element_));
}


/**
 * @brief UploadCPUBuffer関数
 */
inline void tml::graphic::ConfigShaderConstantBuffer::UploadCPUBuffer(void)
{
	tml::graphic::ShaderConstantBuffer::UploadCPUBuffer(reinterpret_cast<BYTE *>(this->element_));

	return;
}


/**
 * @brief DownloadCPUBuffer関数
 */
inline void tml::graphic::ConfigShaderConstantBuffer::DownloadCPUBuffer(void)
{
	tml::graphic::ShaderConstantBuffer::DownloadCPUBuffer(reinterpret_cast<BYTE *>(this->element_));

	return;
}
