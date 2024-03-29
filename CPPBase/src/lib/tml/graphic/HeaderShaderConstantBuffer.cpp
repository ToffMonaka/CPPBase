/**
 * @file
 * @brief HeaderShaderConstantBufferコードファイル
 */


#include "HeaderShaderConstantBuffer.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::HeaderShaderConstantBufferDesc::HeaderShaderConstantBufferDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::HeaderShaderConstantBufferDesc::~HeaderShaderConstantBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::HeaderShaderConstantBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderConstantBufferDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::HeaderShaderConstantBuffer::HeaderShaderConstantBuffer() :
	desc_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::HeaderShaderConstantBuffer::~HeaderShaderConstantBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::HeaderShaderConstantBuffer::Init(void)
{
	this->Release();

	tml::graphic::ShaderConstantBuffer::Init();

	return;
}


/**
 * @brief OnCreate関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::HeaderShaderConstantBuffer::OnCreate(void)
{
	if (tml::graphic::ShaderConstantBuffer::OnCreate() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnCreateDeferred関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::HeaderShaderConstantBuffer::OnCreateDeferred(void)
{
	if (tml::graphic::ShaderConstantBuffer::OnCreateDeferred() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnSetDesc関数
 * @param desc (desc)
 */
void tml::graphic::HeaderShaderConstantBuffer::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::graphic::HeaderShaderConstantBufferDesc *>(desc);

	tml::graphic::ShaderConstantBuffer::OnSetDesc(this->desc_);

	return;
}


/**
 * @brief SetElement関数
 * @param camera_cnt (camera_count)
 * @param light_cnt (light_count)
 * @param fog_cnt (fog_count)
 * @param model_cnt (model_count)
 */
void tml::graphic::HeaderShaderConstantBuffer::SetElement(const UINT camera_cnt, const UINT light_cnt, const UINT fog_cnt, const UINT model_cnt)
{
	auto element = this->GetElement();

	element->camera_count = camera_cnt;
	element->light_count = light_cnt;
	element->fog_count = fog_cnt;
	element->model_count = model_cnt;

	return;
}
