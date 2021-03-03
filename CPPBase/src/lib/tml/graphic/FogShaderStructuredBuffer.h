/**
 * @file
 * @brief FogShaderStructuredBuffer�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ShaderStructuredBuffer.h"
#include "Fog.h"


namespace tml {
namespace graphic {
/**
 * @brief FogShaderStructuredBufferDesc�N���X
 */
class FogShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

protected:
	void Release(void);

public:
	FogShaderStructuredBufferDesc();
	virtual ~FogShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::FogShaderStructuredBufferDesc::Release(void)
{
	tml::graphic::ShaderStructuredBufferDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief FogShaderStructuredBuffer�N���X
 */
class FogShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: FogShaderStructuredBuffer(const tml::graphic::FogShaderStructuredBuffer &) = delete;
public: tml::graphic::FogShaderStructuredBuffer &operator =(const tml::graphic::FogShaderStructuredBuffer &) = delete;
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

protected:
	void Release(void);

public:
	FogShaderStructuredBuffer();
	virtual ~FogShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::FogShaderStructuredBufferDesc &);

	tml::graphic::FogShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	tml::graphic::FogShaderStructuredBuffer::ELEMENT *GetElementArray(void);
	void SetElement(const UINT, const tml::graphic::Fog *);
	void SetElement(const UINT, const UINT, const tml::graphic::Fog *const *);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::FogShaderStructuredBuffer::Release(void)
{
	tml::graphic::ShaderStructuredBuffer::Release();

	return;
}


/**
 * @brief GetElement�֐�
 * @param index (index)
 * @return element (element)<br>
 * nullptr=���s
 */
inline tml::graphic::FogShaderStructuredBuffer::ELEMENT *tml::graphic::FogShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement<tml::graphic::FogShaderStructuredBuffer::ELEMENT>(index));
}


/**
 * @brief GetElementArray�֐�
 * @return element_ary (element_array)
 */
inline tml::graphic::FogShaderStructuredBuffer::ELEMENT *tml::graphic::FogShaderStructuredBuffer::GetElementArray(void)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElementArray<tml::graphic::FogShaderStructuredBuffer::ELEMENT>());
}
