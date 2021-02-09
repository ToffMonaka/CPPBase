/**
 * @file
 * @brief ConfigShaderConstantBuffer�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ShaderConstantBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief ConfigShaderConstantBufferDesc�N���X
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
 * @brief Release�֐�
 */
inline void tml::graphic::ConfigShaderConstantBufferDesc::Release(void)
{
	tml::graphic::ShaderConstantBufferDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief ConfigShaderConstantBuffer�N���X
 */
class ConfigShaderConstantBuffer : public tml::graphic::ShaderConstantBuffer
{
public: ConfigShaderConstantBuffer(const tml::graphic::ConfigShaderConstantBuffer &) = delete;
public: tml::graphic::ConfigShaderConstantBuffer &operator =(const tml::graphic::ConfigShaderConstantBuffer &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	/**
	 * @brief ELEMENT�\����
	 */
	typedef struct ELEMENT_
	{
		UINT dummy1;
		UINT dummy2;
		UINT dummy3;
		UINT dummy4;

		/**
		 * @brief �R���X�g���N�^
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

	void UpdateBuffer(void);
	tml::graphic::ConfigShaderConstantBuffer::ELEMENT *GetElement(void);
};
}
}


/**
 * @brief UpdateBuffer�֐�
 */
inline void tml::graphic::ConfigShaderConstantBuffer::UpdateBuffer(void)
{
	tml::graphic::ShaderConstantBuffer::UpdateBuffer(this->element_);

	return;
}


/**
 * @brief GetElement�֐�
 * @return element (element)<br>
 * nullptr=���s
 */
inline tml::graphic::ConfigShaderConstantBuffer::ELEMENT *tml::graphic::ConfigShaderConstantBuffer::GetElement(void)
{
	return (tml::graphic::ShaderConstantBuffer::GetElement(this->element_));
}
