/**
 * @file
 * @brief ManagerTaskヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_INPUT.h"
#include "../manager/ManagerTask.h"


namespace tml {
namespace input {
/**
 * @brief ManagerTaskDescクラス
 */
class ManagerTaskDesc : public tml::ManagerTaskDesc
{
private:
	tml::input::Manager *mgr_;

public:

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

	virtual void OnSetManager(tml::Manager *);

public:
	ManagerTaskDesc();
	virtual ~ManagerTaskDesc();

	virtual void Init(void);

	tml::input::Manager *GetManager(void) const;
};
}
}


/**
 * @brief Release関数
 */
inline void tml::input::ManagerTaskDesc::Release(void)
{
	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::input::Manager *tml::input::ManagerTaskDesc::GetManager(void) const
{
	return (this->mgr_);
}


namespace tml {
namespace input {
/**
 * @brief ManagerTaskクラス
 *
 * インターフェースパターン
 */
class ManagerTask : public tml::ManagerTask
{
public: ManagerTask(const tml::input::ManagerTask &) = delete;
public: tml::input::ManagerTask &operator =(const tml::input::ManagerTask &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::input::Manager *mgr_;

private:
	void Release(void);

protected:
	virtual void OnSetManager(tml::Manager *);

public:
	ManagerTask();
	virtual ~ManagerTask();

	virtual void Init(void);
	INT Create(const tml::input::ManagerTaskDesc &);

	tml::input::Manager *GetManager(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::input::ManagerTask::Release(void)
{
	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::input::Manager *tml::input::ManagerTask::GetManager(void)
{
	return (this->mgr_);
}
