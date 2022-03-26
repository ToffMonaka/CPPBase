/**
 * @file
 * @brief DeviceEvent�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ManagerEvent.h"


namespace tml {
namespace input {
/**
 * @brief DeviceEventData�N���X
 */
class DeviceEventData : public tml::input::ManagerEventData
{
public:

private:
	void Release(void);

public:
	DeviceEventData();
	virtual ~DeviceEventData();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::input::DeviceEventData::Release(void)
{
	return;
}


namespace tml {
namespace input {
/**
 * @brief DeviceEventDesc�N���X
 */
class DeviceEventDesc : public tml::input::ManagerEventDesc
{
public:

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	DeviceEventDesc();
	virtual ~DeviceEventDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::input::DeviceEventDesc::Release(void)
{
	return;
}


namespace tml {
namespace input {
/**
 * @brief DeviceEvent�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class DeviceEvent : public tml::input::ManagerEvent
{
public: DeviceEvent(const tml::input::DeviceEvent &) = delete;
public: tml::input::DeviceEvent &operator =(const tml::input::DeviceEvent &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:

private:
	void Release(void);

public:
	DeviceEvent();
	virtual ~DeviceEvent();

	virtual void Init(void);
	INT Create(const tml::input::DeviceEventDesc &);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::input::DeviceEvent::Release(void)
{
	return;
}
