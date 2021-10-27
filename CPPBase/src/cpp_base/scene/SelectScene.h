/**
 * @file
 * @brief SelectSceneヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "../constant/ConstantUtil_SOUND.h"
#include "Scene.h"


namespace cpp_base {
namespace scene {
/**
 * @brief SelectSceneDescクラス
 */
class SelectSceneDesc : public cpp_base::scene::SceneDesc
{
public:

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	SelectSceneDesc();
	virtual ~SelectSceneDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::SelectSceneDesc::Release(void)
{
	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief SelectSceneクラス
 */
class SelectScene : public cpp_base::scene::Scene
{
public: SelectScene(const cpp_base::scene::SelectScene &) = delete;
public: cpp_base::scene::SelectScene &operator =(const cpp_base::scene::SelectScene &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	UINT progress_type_;

public:
	tml::shared_ptr<tml::graphic::Canvas2D> canvas_2d;
	tml::shared_ptr<tml::graphic::Canvas3D> canvas_3d;
	tml::shared_ptr<tml::graphic::Camera2D> camera_2d;
	tml::shared_ptr<tml::graphic::Camera3D> camera_3d;
	tml::shared_ptr<tml::graphic::FigureModel2D> bg_model;
	tml::shared_ptr<tml::sound::BGMSound> bgm_sound;
	tml::shared_ptr<tml::graphic::Font> stage_font;
	tml::shared_ptr<tml::graphic::FigureModel2D> stage_model;
	tml::shared_ptr<tml::sound::SESound> stage_se_sound;
	tml::shared_ptr<tml::scene::Node> main_node;

private:
	void Release(void);

protected:
	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);

public:
	SelectScene();
	virtual ~SelectScene();

	virtual void Init(void);
	INT Create(const cpp_base::scene::SelectSceneDesc &);
};
}
}
