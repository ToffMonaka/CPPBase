/**
 * @file
 * @brief KeyboardEvent�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ManagerEvent.h"


namespace tml {
namespace input {
/**
 * @brief KeyboardEventData�N���X
 */
class KeyboardEventData
{
public:
	tml::ConstantUtil::INPUT::KEYBOARD_EVENT_DATA_TYPE type_flag;
	tml::ConstantUtil::INPUT::KEYBOARD_CODE code;

protected:
	void Release(void);

public:
	KeyboardEventData();
	virtual ~KeyboardEventData();

	virtual void Init(void);

	void SetRawInput(const RAWKEYBOARD &);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::input::KeyboardEventData::Release(void)
{
	return;
}


namespace tml {
namespace input {
/**
 * @brief KeyboardEventDesc�N���X
 */
class KeyboardEventDesc : public tml::input::ManagerEventDesc
{
public:
	tml::input::KeyboardEventData data;

protected:
	void Release(void);

public:
	KeyboardEventDesc();
	virtual ~KeyboardEventDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::input::KeyboardEventDesc::Release(void)
{
	tml::input::ManagerEventDesc::Release();

	return;
}


namespace tml {
namespace input {
/**
 * @brief KeyboardEvent�N���X
 */
class KeyboardEvent : public tml::input::ManagerEvent
{
public: KeyboardEvent(const tml::input::KeyboardEvent &) = delete;
public: tml::input::KeyboardEvent &operator =(const tml::input::KeyboardEvent &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT EVENT_MAIN_INDEX = static_cast<UINT>(tml::ConstantUtil::INPUT::EVENT_TYPE::DEVICE);
	static const UINT EVENT_SUB_INDEX = static_cast<UINT>(tml::ConstantUtil::INPUT::DEVICE_EVENT_TYPE::KEYBOARD);

private:
	tml::input::KeyboardEventData dat_;

protected:
	void Release(void);

public:
	KeyboardEvent();
	virtual ~KeyboardEvent();

	virtual void Init(void);
	INT Create(const tml::input::KeyboardEventDesc &);

	tml::input::KeyboardEventData &GetData(void);
	void SetData(const tml::input::KeyboardEventData &);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::input::KeyboardEvent::Release(void)
{
	tml::input::ManagerEvent::Release();

	return;
}


/**
 * @brief GetData�֐�
 * @return dat (data)
 */
inline tml::input::KeyboardEventData &tml::input::KeyboardEvent::GetData(void)
{
	return (this->dat_);
}


/**
 * @brief SetData�֐�
 * @param dat (data)
 */
inline void tml::input::KeyboardEvent::SetData(const tml::input::KeyboardEventData &dat)
{
	this->dat_ = dat;

	return;
}
