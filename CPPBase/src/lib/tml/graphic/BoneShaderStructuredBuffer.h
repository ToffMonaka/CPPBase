/**
 * @file
 * @brief BoneShaderStructuredBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ShaderStructuredBuffer.h"


namespace tml {
namespace graphic {
/**
 * @brief BoneShaderStructuredBufferDescクラス
 */
class BoneShaderStructuredBufferDesc : public tml::graphic::ShaderStructuredBufferDesc
{
public:

public:
	BoneShaderStructuredBufferDesc();
	virtual ~BoneShaderStructuredBufferDesc();

	virtual void Init(void);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief BoneShaderStructuredBufferクラス
 */
class BoneShaderStructuredBuffer : public tml::graphic::ShaderStructuredBuffer
{
public: BoneShaderStructuredBuffer(const tml::graphic::BoneShaderStructuredBuffer &) = delete;
public: tml::graphic::BoneShaderStructuredBuffer &operator =(const tml::graphic::BoneShaderStructuredBuffer &) = delete;
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
	tml::graphic::BoneShaderStructuredBuffer::ELEMENT *element_ary_;

private:
	void Release(void);

public:
	BoneShaderStructuredBuffer();
	virtual ~BoneShaderStructuredBuffer();

	virtual void Init(void);
	INT Create(const tml::graphic::BoneShaderStructuredBufferDesc &);

	void UpdateBuffer(void);
	tml::graphic::BoneShaderStructuredBuffer::ELEMENT *GetElement(const UINT);
	//void SetElement(const UINT, tml::graphic::Bone *, const bool, const XMMATRIX &);
};
}
}


/**
 * @brief UpdateBuffer関数
 */
inline void tml::graphic::BoneShaderStructuredBuffer::UpdateBuffer(void)
{
	tml::graphic::ShaderStructuredBuffer::UpdateBuffer(this->element_ary_);

	return;
}


/**
 * @brief GetElement関数
 * @param index (index)
 * @return element (element)<br>
 * nullptr=失敗
 */
inline tml::graphic::BoneShaderStructuredBuffer::ELEMENT *tml::graphic::BoneShaderStructuredBuffer::GetElement(const UINT index)
{
	return (tml::graphic::ShaderStructuredBuffer::GetElement(this->element_ary_, index));
}
