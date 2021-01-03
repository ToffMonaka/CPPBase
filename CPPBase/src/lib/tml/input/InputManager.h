/**
 * @file
 * @brief InputManagerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_INPUT.h"


namespace tml {
/**
 * @brief InputManagerDescクラス
 */
class InputManagerDesc
{
public:

public:
	InputManagerDesc();
	virtual ~InputManagerDesc();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief InputManagerクラス
 */
class InputManager
{
public: InputManager(const tml::InputManager &) = delete;
public: tml::InputManager &operator =(const tml::InputManager &) = delete;

private:

private:
	void Release(void);

public:
	InputManager();
	virtual ~InputManager();

	virtual void Init(void);
	INT Create(const tml::InputManagerDesc &);
};
}
