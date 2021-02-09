/**
 * @file
 * @brief HeaderShaderConstantBuffer�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ShaderConstantBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief HeaderShaderConstantBufferDesc�N���X
 */
class HeaderShaderConstantBufferDesc : public tml::graphic::ShaderConstantBufferDesc
{
public:

protected:
	void Release(void);

public:
	HeaderShaderConstantBufferDesc();
	virtual ~HeaderShaderConstantBufferDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::HeaderShaderConstantBufferDesc::Release(void)
{
	tml::graphic::ShaderConstantBufferDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief HeaderShaderConstantBuffer�N���X
 */
class HeaderShaderConstantBuffer : public tml::graphic::ShaderConstantBuffer
{
public: HeaderShaderConstantBuffer(const tml::graphic::HeaderShaderConstantBuffer &) = delete;
public: tml::graphic::HeaderShaderConstantBuffer &operator =(const tml::graphic::HeaderShaderConstantBuffer &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	/**
	 * @brief ELEMENT�\����
	 */
	typedef struct ELEMENT_
	{
		UINT camera_count;
		UINT light_count;
		UINT fog_count;
		UINT model_count;

		/**
		 * @brief �R���X�g���N�^
		 */
		ELEMENT_() :
			camera_count(0U),
			light_count(0U),
			fog_count(0U),
			model_count(0U)
		{
			return;
		};
	} ELEMENT;

private:
	tml::graphic::HeaderShaderConstantBuffer::ELEMENT *element_;

protected:
	void Release(void);

public:
	HeaderShaderConstantBuffer();
	virtual ~HeaderShaderConstantBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::HeaderShaderConstantBufferDesc &);

	void UpdateBuffer(void);
	tml::graphic::HeaderShaderConstantBuffer::ELEMENT *GetElement(void);
	void SetElement(const UINT, const UINT, const UINT, const UINT);
};
}
}


/**
 * @brief UpdateBuffer�֐�
 */
inline void tml::graphic::HeaderShaderConstantBuffer::UpdateBuffer(void)
{
	tml::graphic::ShaderConstantBuffer::UpdateBuffer(this->element_);

	return;
}


/**
 * @brief GetElement�֐�
 * @return element (element)<br>
 * nullptr=���s
 */
inline tml::graphic::HeaderShaderConstantBuffer::ELEMENT *tml::graphic::HeaderShaderConstantBuffer::GetElement(void)
{
	return (tml::graphic::ShaderConstantBuffer::GetElement(this->element_));
}
