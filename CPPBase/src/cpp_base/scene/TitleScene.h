/**
 * @file
 * @brief TitleSceneヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "../constant/ConstantUtil_SOUND.h"
#include "Scene.h"


namespace cpp_base {
namespace scene {
/**
 * @brief TitleSceneDescクラス
 */
class TitleSceneDesc : public cpp_base::scene::SceneDesc
{
public:

private:
	void Release(void);

protected:
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
	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief TitleSceneクラス
 */
class TitleScene : public cpp_base::scene::Scene
{
public: TitleScene(const cpp_base::scene::TitleScene &) = delete;
public: cpp_base::scene::TitleScene &operator =(const cpp_base::scene::TitleScene &) = delete;
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
	tml::shared_ptr<tml::graphic::FigureModel2D> logo_model;
	tml::shared_ptr<tml::graphic::Font> start_font;
	tml::shared_ptr<tml::graphic::FigureModel2D> start_model;
	tml::shared_ptr<tml::sound::SESound> start_se_sound;
	tml::shared_ptr<tml::graphic::Font> footer_font;
	tml::shared_ptr<tml::graphic::FigureModel2D> footer_model;
	tml::shared_ptr<tml::scene::Node> main_node;

private:
	void Release(void);

protected:
	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Init(void);
	INT Create(const cpp_base::scene::TitleSceneDesc &);
};
}
}
