/**
 * @file
 * @brief MainThreadヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../../lib/tml/time/FrameRate.h"
#include "../../lib/tml/thread/MainThread.h"
#include "../../lib/tml/input/Manager.h"
#include "../../lib/tml/graphic/Manager.h"
#include "../../lib/tml/sound/Manager.h"
#include "../data/SystemConfigFile.h"


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
	tml::FrameRate frame_rate_;
	cpp_base::SystemConfigFile sys_conf_file_;

	tml::input::Manager input_mgr_;
	tml::graphic::Manager graphic_mgr_;
	tml::sound::Manager sound_mgr_;

	tml::shared_ptr<tml::graphic::Camera> camera_;
	tml::shared_ptr<tml::graphic::SpriteModel> title_bg_sprite_model_;
	tml::shared_ptr<tml::graphic::SpriteModel> title_logo_sprite_model_;
	tml::shared_ptr<tml::graphic::SpriteModel> log_sprite_model_;
	tml::shared_ptr<tml::graphic::Font> log_font_;
	tml::TIME_REAL log_update_time_;
	tml::shared_ptr<tml::sound::BGMSound> title_bgm_sound_;
	tml::shared_ptr<tml::sound::SESound> click_se_sound_;

private:
	static LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

protected:
	void Release(void);

public:
	MainThread();
	virtual ~MainThread();

	virtual void Init(void);
	INT Create(const HINSTANCE, const WCHAR *, const INT);

	virtual INT Start(void);
	virtual void End(void);
	virtual void Update(void);
	const tml::FrameRate &GetFrameRate(void) const;
	cpp_base::SystemConfigFile &GetSystemConfigFile(void);
	tml::input::Manager &GetInputManager(void);
	tml::graphic::Manager &GetGraphicManager(void);
	tml::sound::Manager &GetSoundManager(void);
};
}


/**
 * @brief GetFrameRate関数
 * @return frame_rate (frame_rate)
 */
inline const tml::FrameRate &cpp_base::MainThread::GetFrameRate(void) const
{
	return (this->frame_rate_);
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
inline tml::input::Manager &cpp_base::MainThread::GetInputManager(void)
{
	return (this->input_mgr_);
}


/**
 * @brief GetGraphicManager関数
 * @return graphic_mgr (graphic_manager)
 */
inline tml::graphic::Manager &cpp_base::MainThread::GetGraphicManager(void)
{
	return (this->graphic_mgr_);
}


/**
 * @brief GetSoundManager関数
 * @return sound_mgr (sound_manager)
 */
inline tml::sound::Manager &cpp_base::MainThread::GetSoundManager(void)
{
	return (this->sound_mgr_);
}
