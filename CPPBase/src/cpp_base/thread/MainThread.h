/**
 * @file
 * @brief MainThreadヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../../lib/tml/thread/MainThread.h"
#include "../data/SystemConfigFile.h"
#include "../manager/ManagerFactory.h"
#include "../input/Manager.h"
#include "../graphic/Manager.h"
#include "../sound/Manager.h"
#include "../scene/Manager.h"


namespace cpp_base {
/**
 * @brief MainThreadクラス
 */
class MainThread : public tml::MainThread
{
public: MainThread(const cpp_base::MainThread &) = delete;
public: cpp_base::MainThread &operator =(const cpp_base::MainThread &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	cpp_base::SystemConfigFile sys_conf_file_;
	cpp_base::ManagerFactory mgr_factory_;
	cpp_base::input::Manager input_mgr_;
	cpp_base::graphic::Manager graphic_mgr_;
	cpp_base::sound::Manager sound_mgr_;
	cpp_base::scene::Manager scene_mgr_;

private:
	static LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

private:
	void Release(void);

protected:
	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);

public:
	MainThread();
	virtual ~MainThread();

	virtual void Init(void);
	INT Create(const HINSTANCE, const WCHAR *, const INT);

	cpp_base::SystemConfigFile &GetSystemConfigFile(void);
	cpp_base::input::Manager &GetInputManager(void);
	cpp_base::graphic::Manager &GetGraphicManager(void);
	cpp_base::sound::Manager &GetSoundManager(void);
	cpp_base::scene::Manager &GetSceneManager(void);
};
}


/**
 * @brief GetSystemConfigFile関数
 * @return sys_conf_file (system_config_file)
 */
inline cpp_base::SystemConfigFile &cpp_base::MainThread::GetSystemConfigFile(void)
{
	return (this->sys_conf_file_);
}


/**
 * @brief GetInputManager関数
 * @return input_mgr (input_manager)
 */
inline cpp_base::input::Manager &cpp_base::MainThread::GetInputManager(void)
{
	return (this->input_mgr_);
}


/**
 * @brief GetGraphicManager関数
 * @return graphic_mgr (graphic_manager)
 */
inline cpp_base::graphic::Manager &cpp_base::MainThread::GetGraphicManager(void)
{
	return (this->graphic_mgr_);
}


/**
 * @brief GetSoundManager関数
 * @return sound_mgr (sound_manager)
 */
inline cpp_base::sound::Manager &cpp_base::MainThread::GetSoundManager(void)
{
	return (this->sound_mgr_);
}


/**
 * @brief GetSceneManager関数
 * @return scene_mgr (scene_manager)
 */
inline cpp_base::scene::Manager &cpp_base::MainThread::GetSceneManager(void)
{
	return (this->scene_mgr_);
}
