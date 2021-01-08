/**
 * @file
 * @brief RasterizerStateヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "GraphicResource.h"


namespace tml {
/**
 * @brief RasterizerStateDescクラス
 */
class RasterizerStateDesc : public tml::GraphicResourceDesc
{
public:
	CD3D11_RASTERIZER_DESC rasterizer_state_desc;

public:
	RasterizerStateDesc();
	virtual ~RasterizerStateDesc();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief RasterizerStateクラス
 */
class RasterizerState : public tml::GraphicResource
{
public: RasterizerState(const tml::RasterizerState &) = delete;
public: tml::RasterizerState &operator =(const tml::RasterizerState &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	ID3D11RasterizerState *rs_;

private:
	void Release(void);

public:
	RasterizerState();
	virtual ~RasterizerState();

	virtual void Init(void);
	INT Create(tml::RasterizerStateDesc &);

	ID3D11RasterizerState *GetRasterizerState(void) const;
};
}


/**
 * @brief GetRasterizerState関数
 * @return rs (rasterizer_state)
 */
inline ID3D11RasterizerState *tml::RasterizerState::GetRasterizerState(void) const
{
	return (this->rs_);
}
