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
	cpp_base::input::Manager *input_mgr2_;
	cpp_base::graphic::Manager *graphic_mgr2_;
	cpp_base::sound::Manager *sound_mgr2_;

public:
	cpp_base::scene::ManagerCommon common2;

protected:
	void Release(void);

	INT CreateCommon2(void);
	void DeleteCommon2(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(const cpp_base::scene::ManagerDesc &);

	cpp_base::input::Manager *GetInputManager(void);
	cpp_base::graphic::Manager *GetGraphicManager(void);
	cpp_base::sound::Manager *GetSoundManager(void);
};
}
}


/**
 * @brief GetInputManager関数
 * @return input_mgr (input_manager)
 */
inline cpp_base::input::Manager *cpp_base::scene::Manager::GetInputManager(void)
{
	return (this->input_mgr2_);
}


/**
 * @brief GetGraphicManager関数
 * @return graphic_mgr (graphic_manager)
 */
inline cpp_base::graphic::Manager *cpp_base::scene::Manager::GetGraphicManager(void)
{
	return (this->graphic_mgr2_);
}


/**
 * @brief GetSoundManager関数
 * @return sound_mgr (sound_manager)
 */
inline cpp_base::sound::Manager *cpp_base::scene::Manager::GetSoundManager(void)
{
	return (this->sound_mgr2_);
}
