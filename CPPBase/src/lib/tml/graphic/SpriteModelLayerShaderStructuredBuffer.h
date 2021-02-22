/**
 * @file
 * @brief SpriteModelLayerShaderStructuredBuffer�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMath.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief SpriteModelLayerShaderStructuredBufferDesc�N���X
 */
class SpriteModelLayerShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

protected:
	void Release(void);

public:
	SpriteModelLayerShaderStructuredBufferDesc();
	virtual ~SpriteModelLayerShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::SpriteModelLayerShaderStructuredBufferDesc::Release(void)
{
	tml::graphic::ShaderStructuredBufferDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief SpriteModelLayerShaderStructuredBuffer�N���X
 */
class SpriteModelLayerShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: SpriteModelLayerShaderStructuredBuffer(const tml::graphic::SpriteModelLayerShaderStructuredBuffer &) = delete;
public: tml::graphic::SpriteModelLayerShaderStructuredBuffer &operator =(const tml::graphic::SpriteModelLayerShaderStructuredBuffer &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	/**
	 * @brief ELEMENT�\����
	 */
	typedef struct ELEMENT_
	{
		UINT diffuse_texture_flag;
		UINT dummy1;
		UINT dummy2;
		UINT dummy3;

		/**
		 * @brief �R���X�g���N�^
		 */
		ELEMENT_() :
			diffuse_texture_flag(0U),
			dummy1(0U),
			dummy2(0U),
			dummy3(0U)
		{
			return;
		};
	} ELEMENT;

private:
	tml::graphic::SpriteModelLayerShaderStructuredBuffer::ELEMENT *element_ary_;

protected:
	void Release(void);

public:
	SpriteModelLayerShaderStructuredBuffer();
	virtual ~SpriteModelLayerShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::SpriteModelLayerShaderStructuredBufferDesc &);

	tml::graphic::SpriteModelLayerShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	void SetElement(const UINT, const bool);
	void UploadCPUBuffer(void);
	void DownloadCPUBuffer(void);
};
}
}


/**
 * @brief GetElement�֐�
 * @param index (index)
 * @return element (element)<br>
 * nullptr=���s
 */
inline tml::graphic::SpriteModelLayerShaderStructuredBuffer::ELEMENT *tml::graphic::SpriteModelLayerShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement(this->element_ary_, index));
}


/**
 * @brief UploadCPUBuffer�֐�
 */
inline void tml::graphic::SpriteModelLayerShaderStructuredBuffer::UploadCPUBuffer(void)
{
	tml::graphic::ShaderStructuredBuffer::UploadCPUBuffer(reinterpret_cast<BYTE *>(this->element_ary_));

	return;
}


/**
 * @brief DownloadCPUBuffer�֐�
 */
inline void tml::graphic::SpriteModelLayerShaderStructuredBuffer::DownloadCPUBuffer(void)
{
	tml::graphic::ShaderStructuredBuffer::DownloadCPUBuffer(reinterpret_cast<BYTE *>(this->element_ary_));

	return;
}
