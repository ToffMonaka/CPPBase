/**
 * @file
 * @brief Managerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../../lib/tml/scene/Manager.h"
#include "ManagerFactory.h"
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
private:
	cpp_base::input::Manager *input_mgr_;
	cpp_base::graphic::Manager *graphic_mgr_;
	cpp_base::sound::Manager *sound_mgr_;

public:

private:
	void Release(void);

protected:
	void InitResourceCount(void);
	void InitEventCount(void);

public:
	ManagerDesc();
	virtual ~ManagerDesc();

	virtual void Init(void);

	cpp_base::input::Manager *GetInputManager(void) const;
	void SetInputManager(cpp_base::input::Manager *);
	cpp_base::graphic::Manager *GetGraphicManager(void) const;
	void SetGraphicManager(cpp_base::graphic::Manager *);
	cpp_base::sound::Manager *GetSoundManager(void) const;
	void SetSoundManager(cpp_base::sound::Manager *);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::ManagerDesc::Release(void)
{
	return;
}


/**
 * @brief GetInputManager関数
 * @return input_mgr (input_manager)
 */
inline cpp_base::input::Manager *cpp_base::scene::ManagerDesc::GetInputManager(void) const
{
	return (this->input_mgr_);
}


/**
 * @brief GetGraphicManager関数
 * @return graphic_mgr (graphic_manager)
 */
inline cpp_base::graphic::Manager *cpp_base::scene::ManagerDesc::GetGraphicManager(void) const
{
	return (this->graphic_mgr_);
}


/**
 * @brief GetSoundManager関数
 * @return sound_mgr (sound_manager)
 */
inline cpp_base::sound::Manager *cpp_base::scene::ManagerDesc::GetSoundManager(void) const
{
	return (this->sound_mgr_);
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
	cpp_base::input::Manager *input_mgr_;
	cpp_base::graphic::Manager *graphic_mgr_;
	cpp_base::sound::Manager *sound_mgr_;

public:
	cpp_base::scene::ManagerFactory factory2;
	cpp_base::scene::ManagerCommon common2;

private:
	void Release(void);

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
	return (this->input_mgr_);
}


/**
 * @brief GetGraphicManager関数
 * @return graphic_mgr (graphic_manager)
 */
inline cpp_base::graphic::Manager *cpp_base::scene::Manager::GetGraphicManager(void)
{
	return (this->graphic_mgr_);
}


/**
 * @brief GetSoundManager関数
 * @return sound_mgr (sound_manager)
 */
inline cpp_base::sound::Manager *cpp_base::scene::Manager::GetSoundManager(void)
{
	return (this->sound_mgr_);
}
