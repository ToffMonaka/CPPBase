/**
 * @file
 * @brief ConfigShaderConstantBufferコードファイル
 */


#include "ConfigShaderConstantBuffer.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::ConfigShaderConstantBufferDesc::ConfigShaderConstantBufferDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ConfigShaderConstantBufferDesc::~ConfigShaderConstantBufferDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ConfigShaderConstantBufferDesc::Init(void)
{
	this->Release();

	tml::graphic::ShaderConstantBufferDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::ConfigShaderConstantBuffer::ConfigShaderConstantBuffer() :
	desc_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ConfigShaderConstantBuffer::~ConfigShaderConstantBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ConfigShaderConstantBuffer::Init(void)
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
INT tml::graphic::ConfigShaderConstantBuffer::OnCreate(void)
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
INT tml::graphic::ConfigShaderConstantBuffer::OnCreateDeferred(void)
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
void tml::graphic::ConfigShaderConstantBuffer::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::graphic::ConfigShaderConstantBufferDesc *>(desc);

	tml::graphic::ShaderConstantBuffer::OnSetDesc(this->desc_);

	return;
}
