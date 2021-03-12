/**
 * @file
 * @brief KeyboardEvent�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Event.h"


namespace tml {
namespace input {
/**
 * @brief KeyboardEventData�N���X
 */
class KeyboardEventData
{
public:
	tml::ConstantUtil::INPUT::KEYBOARD_EVENT_DATA_TYPE type_flag;
	tml::ConstantUtil::INPUT::VIRTUAL_KEY_CODE virtual_key_code;

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
 * @brief KeyboardEvent�N���X
 */
class KeyboardEvent : public tml::input::Event
{
public: KeyboardEvent(const tml::input::KeyboardEvent &) = delete;
public: tml::input::KeyboardEvent &operator =(const tml::input::KeyboardEvent &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const tml::ConstantUtil::INPUT::EVENT_TYPE EVENT_TYPE = tml::ConstantUtil::INPUT::EVENT_TYPE::KEYBOARD;

private:
	tml::input::KeyboardEventData dat_;

protected:
	void Release(void);

public:
	KeyboardEvent();
	virtual ~KeyboardEvent();

	virtual void Init(void);
	INT Create(tml::input::Manager *);

	const tml::input::KeyboardEventData &GetData(void) const;
	void SetData(const tml::input::KeyboardEventData &);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::input::KeyboardEvent::Release(void)
{
	tml::input::Event::Release();

	return;
}


/**
 * @brief GetData�֐�
 * @return dat (data)
 */
inline const tml::input::KeyboardEventData &tml::input::KeyboardEvent::GetData(void) const
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
