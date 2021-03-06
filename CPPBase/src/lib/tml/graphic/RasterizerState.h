/**
 * @file
 * @brief RasterizerStateヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Resource.h"


namespace tml {
namespace graphic {
/**
 * @brief RasterizerStateDescクラス
 */
class RasterizerStateDesc : public tml::graphic::ResourceDesc
{
public:
	CD3D11_RASTERIZER_DESC rasterizer_state_desc;

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	RasterizerStateDesc();
	virtual ~RasterizerStateDesc();

	virtual void Init(void);

	void SetRasterizerStateDesc(const tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_DESC_TYPE);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::RasterizerStateDesc::Release(void)
{
	tml::graphic::ResourceDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief RasterizerStateクラス
 */
class RasterizerState : public tml::graphic::Resource
{
public: RasterizerState(const tml::graphic::RasterizerState &) = delete;
public: tml::graphic::RasterizerState &operator =(const tml::graphic::RasterizerState &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	ID3D11RasterizerState *rs_;

protected:
	void Release(void);

public:
	RasterizerState();
	virtual ~RasterizerState();

	virtual void Init(void);
	INT Create(const tml::graphic::RasterizerStateDesc &);

	ID3D11RasterizerState *GetRasterizerState(void);
};
}
}


/**
 * @brief GetRasterizerState関数
 * @return rs (rasterizer_state)
 */
inline ID3D11RasterizerState *tml::graphic::RasterizerState::GetRasterizerState(void)
{
	return (this->rs_);
}
