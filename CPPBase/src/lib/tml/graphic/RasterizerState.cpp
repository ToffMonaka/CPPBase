/**
 * @file
 * @brief RasterizerStateコードファイル
 */


#include "RasterizerState.h"
#include "GraphicManager.h"


/**
 * @brief コンストラクタ
 */
tml::RasterizerStateDesc::RasterizerStateDesc() :
	desc(CD3D11_DEFAULT())
{
	this->desc.CullMode = D3D11_CULL_NONE;

	return;
}


/**
 * @brief デストラクタ
 */
tml::RasterizerStateDesc::~RasterizerStateDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::RasterizerStateDesc::Init(void)
{
	this->desc = CD3D11_RASTERIZER_DESC(CD3D11_DEFAULT());
	this->desc.CullMode = D3D11_CULL_NONE;

	tml::GraphicResourceDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::RasterizerState::RasterizerState() :
	rs_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::RasterizerState::~RasterizerState()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::RasterizerState::Release(void)
{
	if (this->rs_ != nullptr) {
		this->rs_->Release();

		this->rs_ = nullptr;
	}

	tml::GraphicResource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::RasterizerState::Init(void)
{
	this->Release();

	tml::GraphicResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::RasterizerState::Create(const tml::RasterizerStateDesc &desc)
{
	this->Init();

	if (tml::GraphicResource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	if (FAILED(this->GetManager()->GetDevice()->CreateRasterizerState(&desc.desc, &this->rs_))) {
		this->Init();

		return (-1);
	}

	return (0);
}
