/**
 * @file
 * @brief RasterizerState�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ManagerResource.h"


namespace tml {
namespace graphic {
/**
 * @brief RasterizerStateDesc�N���X
 */
class RasterizerStateDesc : public tml::graphic::ManagerResourceDesc
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
 * @brief Release�֐�
 */
inline void tml::graphic::RasterizerStateDesc::Release(void)
{
	tml::graphic::ManagerResourceDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief RasterizerState�N���X
 */
class RasterizerState : public tml::graphic::ManagerResource
{
public: RasterizerState(const tml::graphic::RasterizerState &) = delete;
public: tml::graphic::RasterizerState &operator =(const tml::graphic::RasterizerState &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT RESOURCE_MAIN_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::RASTERIZER_STATE);
	static const UINT RESOURCE_SUB_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RASTERIZER_STATE_TYPE::BASE);

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
 * @brief GetRasterizerState�֐�
 * @return rs (rasterizer_state)
 */
inline ID3D11RasterizerState *tml::graphic::RasterizerState::GetRasterizerState(void)
{
	return (this->rs_);
}
