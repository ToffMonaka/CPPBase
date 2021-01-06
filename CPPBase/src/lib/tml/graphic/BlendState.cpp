/**
 * @file
 * @brief BlendStateコードファイル
 */


#include "BlendState.h"
#include "GraphicManager.h"


/**
 * @brief コンストラクタ
 */
tml::BlendStateDesc::BlendStateDesc() :
	desc(CD3D11_DEFAULT()),
	factor_array{}
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::BlendStateDesc::~BlendStateDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::BlendStateDesc::Init(void)
{
	this->desc = CD3D11_BLEND_DESC(CD3D11_DEFAULT());
	this->factor_array.fill(0.0f);

	tml::GraphicResourceDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::BlendState::BlendState() :
	bs_(nullptr),
	factor_ary_{}
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::BlendState::~BlendState()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::BlendState::Release(void)
{
	if (this->bs_ != nullptr) {
		this->bs_->Release();

		this->bs_ = nullptr;
	}

	tml::GraphicResource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::BlendState::Init(void)
{
	this->Release();

	this->factor_ary_.fill(0.0f);

	tml::GraphicResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::BlendState::Create(tml::BlendStateDesc &desc)
{
	this->Init();

	if (tml::GraphicResource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	if (FAILED(this->GetManager()->GetDevice()->CreateBlendState(&desc.desc, &this->bs_))) {
		this->Init();

		return (-1);
	}

	this->factor_ary_ = desc.factor_array;

	return (0);
}
