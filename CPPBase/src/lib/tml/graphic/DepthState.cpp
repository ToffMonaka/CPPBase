/**
 * @file
 * @brief DepthStateコードファイル
 */


#include "DepthState.h"
#include "GraphicManager.h"


/**
 * @brief コンストラクタ
 */
tml::DepthStateDesc::DepthStateDesc() :
	depth_state_desc(CD3D11_DEFAULT())
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::DepthStateDesc::~DepthStateDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::DepthStateDesc::Init(void)
{
	this->depth_state_desc = CD3D11_DEPTH_STENCIL_DESC(CD3D11_DEFAULT());

	tml::GraphicResourceDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::DepthState::DepthState() :
	ds_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::DepthState::~DepthState()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::DepthState::Release(void)
{
	if (this->ds_ != nullptr) {
		this->ds_->Release();

		this->ds_ = nullptr;
	}

	tml::GraphicResource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::DepthState::Init(void)
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
INT tml::DepthState::Create(tml::DepthStateDesc &desc)
{
	this->Init();

	if (tml::GraphicResource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	if (FAILED(this->GetManager()->GetDevice()->CreateDepthStencilState(&desc.depth_state_desc, &this->ds_))) {
		this->Init();

		return (-1);
	}

	return (0);
}
