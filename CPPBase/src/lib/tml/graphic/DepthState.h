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
 * @brief Release�֐�
 */
inline void tml::graphic::DepthStateDesc::Release(void)
{
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

public:
	static const UINT RESOURCE_TYPE = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::DEPTH_STATE);

private:
	const tml::graphic::DepthStateDesc *desc_;
	ID3D11DepthStencilState *ds_;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);

public:
	DepthState();
	virtual ~DepthState();

	virtual void Init(void);

	const tml::graphic::DepthStateDesc *GetDesc(void) const;
	ID3D11DepthStencilState *GetDepthState(void);
};
}
}


/**
 * @brief GetDesc�֐�
 * @return desc (desc)
 */
inline const tml::graphic::DepthStateDesc *tml::graphic::DepthState::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief GetDepthState�֐�
 * @return ds (depth_state)
 */
inline ID3D11DepthStencilState *tml::graphic::DepthState::GetDepthState(void)
{
	return (this->ds_);
}
