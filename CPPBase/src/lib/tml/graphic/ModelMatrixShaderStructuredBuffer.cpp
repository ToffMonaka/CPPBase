/**
 * @file
 * @brief ModelMatrixShaderStructuredBuffer�R�[�h�t�@�C��
 */


#include "ModelMatrixShaderStructuredBuffer.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::ModelMatrixShaderStructuredBufferDesc::ModelMatrixShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::ModelMatrixShaderStructuredBufferDesc::~ModelMatrixShaderStructuredBufferDesc()
{
	return;
}


/**
 * @brief �������֐�
 */
void tml::graphic::ModelMatrixShaderStructuredBufferDesc::Init(void)
{
	tml::graphic::ShaderStructuredBufferDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::ModelMatrixShaderStructuredBuffer::ModelMatrixShaderStructuredBuffer() :
	element_ary_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::ModelMatrixShaderStructuredBuffer::~ModelMatrixShaderStructuredBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::graphic::ModelMatrixShaderStructuredBuffer::Release(void)
{
	tml::MemoryUtil::Release(&this->element_ary_);

	tml::graphic::ShaderStructuredBuffer::Release();

	return;
}


/**
 * @brief �������֐�
 */
void tml::graphic::ModelMatrixShaderStructuredBuffer::Init(void)
{
	this->Release();

	tml::graphic::ShaderStructuredBuffer::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::ModelMatrixShaderStructuredBuffer::Create(const tml::graphic::ModelMatrixShaderStructuredBufferDesc &desc)
{
	this->Init();

	if (tml::graphic::ShaderStructuredBuffer::Create(desc, sizeof(tml::graphic::ModelMatrixShaderStructuredBuffer::ELEMENT)) < 0) {
		this->Init();

		return (-1);
	}

	this->element_ary_ = tml::MemoryUtil::Get<tml::graphic::ModelMatrixShaderStructuredBuffer::ELEMENT>(desc.element_limit);

	return (0);
}


/**
 * @brief �v�f�Z�b�g�֐�
 * @param index �c�C���f�b�N�X
 * @param light �c���C�g
 * @param draw_shadow_flg �c�`��V���h�E�t���O(false=�`��V���h�E����,true=�`��V���h�E�L��)
 * @param v_mat �c�r���[�s��
 */
/*
void tml::graphic::ModelMatrixShaderStructuredBuffer::SetElement(const UINT index, tml::graphic::ModelMatrix *light, const bool draw_shadow_flg, const XMMATRIX &v_mat)
{
	auto element = this->GetElement(index);

	if (element == NULLP) { //�v�f�����̎�
		return;
	}

	element->type = static_cast<UINT>(light->GetType());
	element->flg = light->GetFlag();
	XMStoreFloat3(&element->v_pos, XMVector3Transform(XMLoadFloat3(&light->GetPosition().Get().GetPosition()), v_mat));
	XMStoreFloat3(&element->v_dir_vec, XMVector3TransformNormal(XMLoadFloat3(&light->GetPosition().Get().GetZAxisVector()), v_mat));
	element->col = light->GetColor();
	element->mul_val = light->GetMulValue();
	element->add_val = light->GetAddValue();
	element->exponent = light->GetExponent();
	element->cut_val = light->GetCutValue();
	element->soft_val = light->GetSoftValue();
	element->atten_val = light->GetAttenuateValue();
	element->rng = light->GetRange();
	element->inv_rng = (light->GetRange() > 0.0f) ? 1.0f / light->GetRange() : 0.0f;
	element->rng_exponent = light->GetRangeExponent();
	element->draw_shadow_flg = draw_shadow_flg;

	return;
}
*/
