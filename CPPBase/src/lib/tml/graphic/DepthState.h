/**
 * @file
 * @brief DepthStateヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "GraphicResource.h"


namespace tml {
/**
 * @brief DepthStateDescクラス
 */
class DepthStateDesc : public tml::GraphicResourceDesc
{
public:
	CD3D11_DEPTH_STENCIL_DESC depth_state_desc;

public:
	DepthStateDesc();
	virtual ~DepthStateDesc();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief DepthStateクラス
 */
class DepthState : public tml::GraphicResource
{
public: DepthState(const tml::DepthState &) = delete;
public: tml::DepthState &operator =(const tml::DepthState &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	ID3D11DepthStencilState *ds_;

private:
	void Release(void);

public:
	DepthState();
	virtual ~DepthState();

	virtual void Init(void);
	INT Create(tml::DepthStateDesc &);

	ID3D11DepthStencilState *GetDepthState(void) const;
};
}


/**
 * @brief GetDepthState関数
 * @return ds (depth_state)
 */
inline ID3D11DepthStencilState *tml::DepthState::GetDepthState(void) const
{
	return (this->ds_);
}
