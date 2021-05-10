/**
 * @file
 * @brief Managerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../../lib/tml/scene/Manager.h"
#include "ManagerCommon.h"


namespace cpp_base {
namespace input {
class Manager;
}
namespace graphic {
class Manager;
}
namespace sound {
class Manager;
}
}


namespace cpp_base {
namespace scene {
/**
 * @brief ManagerDescクラス
 */
class ManagerDesc : public tml::scene::ManagerDesc
{
public:
	cpp_base::input::Manager *input_manager2;
	cpp_base::graphic::Manager *graphic_manager2;
	cpp_base::sound::Manager *sound_manager2;

private:
	void InitResourceCount(void);
	void InitEventCount(void);

protected:
	void Release(void);

public:
	ManagerDesc();
	virtual ~ManagerDesc();

	virtual void Init(void);

	void SetInputManager(cpp_base::input::Manager *);
	void SetGraphicManager(cpp_base::graphic::Manager *);
	void SetSoundManager(cpp_base::sound::Manager *);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::ManagerDesc::Release(void)
{
	tml::scene::ManagerDesc::Release();

	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief Managerクラス
 */
class Manager : public tml::scene::Manager
{
public: Manager(const cpp_base::scene::Manager &) = delete;
public: cpp_base::scene::Manager &operator =(const cpp_base::scene::Manager &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	cpp_base::scene::ManagerCommon common2_;

	cpp_base::input::Manager *input_mgr2_;
	cpp_base::graphic::Manager *graphic_mgr2_;
	cpp_base::sound::Manager *sound_mgr2_;

protected:
	void Release(void);

	INT CreateCommon2(void);
	void DeleteCommon2(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(const cpp_base::scene::ManagerDesc &);

	cpp_base::scene::ManagerCommon &GetCommon2(void);

	cpp_base::input::Manager *GetInputManager2(void);
	cpp_base::graphic::Manager *GetGraphicManager2(void);
	cpp_base::sound::Manager *GetSoundManager2(void);
};
}
}


/**
 * @brief GetCommon2関数
 * @return common2 (common2)
 */
inline cpp_base::scene::ManagerCommon &cpp_base::scene::Manager::GetCommon2(void)
{
	return (this->common2_);
}


/**
 * @brief GetInputManager2関数
 * @return input_mgr2 (input_manager2)
 */
inline cpp_base::input::Manager *cpp_base::scene::Manager::GetInputManager2(void)
{
	return (this->input_mgr2_);
}


/**
 * @brief GetGraphicManager2関数
 * @return graphic_mgr2 (graphic_manager2)
 */
inline cpp_base::graphic::Manager *cpp_base::scene::Manager::GetGraphicManager2(void)
{
	return (this->graphic_mgr2_);
}


/**
 * @brief GetSoundManager2関数
 * @return sound_mgr2 (sound_manager2)
 */
inline cpp_base::sound::Manager *cpp_base::scene::Manager::GetSoundManager2(void)
{
	return (this->sound_mgr2_);
}
