/**
 * @file
 * @brief DepthState�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ManagerResource.h"


namespace tml {
namespace graphic {
/**
 * @brief DepthStateDesc�N���X
 */
class DepthStateDesc : public tml::graphic::ManagerResourceDesc
{
public:
	CD3D11_DEPTH_STENCIL_DESC depth_state_desc;

protected:
	void Release(void);

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
 * @brief Release�֐�
 */
inline void tml::graphic::DepthStateDesc::Release(void)
{
	tml::graphic::ManagerResourceDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief DepthState�N���X
 */
class DepthState : public tml::graphic::ManagerResource
{
public: DepthState(const tml::graphic::DepthState &) = delete;
public: tml::graphic::DepthState &operator =(const tml::graphic::DepthState &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	ID3D11DepthStencilState *ds_;

protected:
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
 * @brief GetDepthState�֐�
 * @return ds (depth_state)
 */
inline ID3D11DepthStencilState *tml::graphic::DepthState::GetDepthState(void)
{
	return (this->ds_);
}
