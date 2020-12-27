/**
 * @file
 * @brief InputResource�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"


namespace tml {
class InputManager;
}


namespace tml {
/**
 * @brief InputResourceDesc�N���X
 */
class InputResourceDesc
{
public:
	tml::InputManager *manager;

public:
	InputResourceDesc();
	virtual ~InputResourceDesc();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief InputResource�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class InputResource
{
public: InputResource(const tml::InputResource &) = delete;
public: tml::InputResource &operator =(const tml::InputResource &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::InputManager *mgr_;

protected:
	void Release(void);
	INT Create(const tml::InputResourceDesc &);

public:
	InputResource();
	virtual ~InputResource();

	virtual void Init(void);

	tml::InputManager *GetManager(void) const;
};
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::InputManager *tml::InputResource::GetManager(void) const
{
	return (this->mgr_);
}
