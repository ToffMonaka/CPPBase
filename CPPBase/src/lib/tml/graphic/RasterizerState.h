/**
 * @file
 * @brief RasterizerStateヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ManagerResource.h"


namespace tml {
namespace graphic {
/**
 * @brief RasterizerStateDescクラス
 */
class RasterizerStateDesc : public tml::graphic::ManagerResourceDesc
{
public:
	CD3D11_RASTERIZER_DESC rasterizer_state_desc;

private:
	void Release(void);

protected:
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
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief RasterizerStateクラス
 */
class RasterizerState : public tml::graphic::ManagerResource
{
public: RasterizerState(const tml::graphic::RasterizerState &) = delete;
public: tml::graphic::RasterizerState &operator =(const tml::graphic::RasterizerState &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT RESOURCE_TYPE = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::RASTERIZER_STATE);

private:
	const tml::graphic::RasterizerStateDesc *desc_;
	ID3D11RasterizerState *rs_;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);

public:
	RasterizerState();
	virtual ~RasterizerState();

	virtual void Init(void);

	const tml::graphic::RasterizerStateDesc *GetDesc(void) const;
	ID3D11RasterizerState *GetRasterizerState(void);
};
}
}


/**
 * @brief GetDesc関数
 * @return desc (desc)
 */
inline const tml::graphic::RasterizerStateDesc *tml::graphic::RasterizerState::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief GetRasterizerState関数
 * @return rs (rasterizer_state)
 */
inline ID3D11RasterizerState *tml::graphic::RasterizerState::GetRasterizerState(void)
{
	return (this->rs_);
}
