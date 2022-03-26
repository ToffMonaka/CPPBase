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
 * @brief Release�֐�
 */
inline void tml::graphic::ConfigShaderConstantBufferDesc::Release(void)
{
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
 * @brief Release�֐�
 */
inline void tml::graphic::ConfigShaderConstantBuffer::Release(void)
{
	return;
}


/**
 * @brief GetDesc�֐�
 * @return desc (desc)
 */
inline const tml::graphic::ConfigShaderConstantBufferDesc *tml::graphic::ConfigShaderConstantBuffer::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief GetElement�֐�
 * @return element (element)<br>
 * nullptr=���s
 */
inline tml::graphic::ConfigShaderConstantBuffer::ELEMENT *tml::graphic::ConfigShaderConstantBuffer::GetElement(void)
{
	return (tml::graphic::ShaderConstantBuffer::GetElement<tml::graphic::ConfigShaderConstantBuffer::ELEMENT>());
}
