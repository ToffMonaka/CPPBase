/**
 * @file
 * @brief InputManager�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_INPUT.h"


namespace tml {
/**
 * @brief InputManager�N���X
 */
class InputManager
{
public: InputManager(const tml::InputManager &) = delete;
public: tml::InputManager &operator =(const tml::InputManager &) = delete;

private:
	void Release(void);

public:
	InputManager();
	virtual ~InputManager();

	virtual void Init(void);
	INT Create(void);
};
}
