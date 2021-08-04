/**
 * @file
 * @brief DepthStateヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ManagerResource.h"


namespace tml {
namespace graphic {
/**
 * @brief DepthStateDescクラス
 */
class DepthStateDesc : public tml::graphic::ManagerResourceDesc
{
public:
	CD3D11_DEPTH_STENCIL_DESC depth_state_desc;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	DepthStateDesc();
	virtual ~DepthStateDesc();

	virtual void Init(void);

	void SetDepthStateDesc(const tml::ConstantUtil::GRAPHIC::DEPTH_STATE_DESC_TYPE);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::DepthStateDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief DepthStateクラス
 */
class DepthState : public tml::graphic::ManagerResource
{
public: DepthState(const tml::graphic::DepthState &) = delete;
public: tml::graphic::DepthState &operator =(const tml::graphic::DepthState &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT RESOURCE_MAIN_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::DEPTH_STATE);
	static const UINT RESOURCE_SUB_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::DEPTH_STATE_TYPE::BASE);

private:
	ID3D11DepthStencilState *ds_;

private:
	void Release(void);

public:
	DepthState();
	virtual ~DepthState();

	virtual void Init(void);
	INT Create(const tml::graphic::DepthStateDesc &);

	ID3D11DepthStencilState *GetDepthState(void);
};
}
}


/**
 * @brief GetDepthState関数
 * @return ds (depth_state)
 */
inline ID3D11DepthStencilState *tml::graphic::DepthState::GetDepthState(void)
{
	return (this->ds_);
}
