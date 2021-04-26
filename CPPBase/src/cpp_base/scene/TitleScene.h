/**
 * @file
 * @brief TitleSceneヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SCENE.h"
#include "../../lib/tml/graphic/ManagerResource.h"
#include "../../lib/tml/sound/ManagerResource.h"
#include "../../lib/tml/scene/Scene.h"


namespace cpp_base {
namespace scene {
/**
 * @brief TitleSceneDescクラス
 */
class TitleSceneDesc : public tml::scene::SceneDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	TitleSceneDesc();
	virtual ~TitleSceneDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::TitleSceneDesc::Release(void)
{
	tml::scene::SceneDesc::Release();

	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief TitleSceneクラス
 */
class TitleScene : public tml::scene::Scene
{
public: TitleScene(const cpp_base::scene::TitleScene &) = delete;
public: cpp_base::scene::TitleScene &operator =(const cpp_base::scene::TitleScene &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	tml::shared_ptr<tml::graphic::Camera> camera_;
	tml::shared_ptr<tml::graphic::SpriteModel> bg_sprite_model_;
	tml::shared_ptr<tml::graphic::SpriteModel> logo_sprite_model_;
	tml::shared_ptr<tml::graphic::SpriteModel> start_sprite_model_;
	tml::shared_ptr<tml::graphic::Font> start_font_;
	tml::shared_ptr<tml::graphic::SpriteModel> footer_sprite_model_;
	tml::shared_ptr<tml::graphic::Font> footer_font_;
	tml::shared_ptr<tml::graphic::SpriteModel> log_sprite_model_;
	tml::shared_ptr<tml::sound::BGMSound> bgm_sound_;
	tml::shared_ptr<tml::sound::SESound> start_se_sound_;
	tml::shared_ptr<tml::graphic::Font> log_font_;
	tml::TIME_REAL log_update_time_;

protected:
	void Release(void);

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Init(void);
	INT Create(const cpp_base::scene::TitleSceneDesc &);

	virtual INT Start(void);
	virtual void End(void);
	virtual void Update(void);
};
}
}
