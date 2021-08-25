/**
 * @file
 * @brief InitSceneヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "Scene.h"


namespace cpp_base {
namespace scene {
/**
 * @brief InitSceneDescクラス
 */
class InitSceneDesc : public cpp_base::scene::SceneDesc
{
public:

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	InitSceneDesc();
	virtual ~InitSceneDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::InitSceneDesc::Release(void)
{
	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief InitSceneクラス
 */
class InitScene : public cpp_base::scene::Scene
{
public: InitScene(const cpp_base::scene::InitScene &) = delete;
public: cpp_base::scene::InitScene &operator =(const cpp_base::scene::InitScene &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	UINT progress_type_;
	std::list<tml::shared_ptr<tml::ManagerResource>> deferred_create_res_cont_;
	std::list<tml::shared_ptr<tml::ManagerResource>>::iterator deferred_create_res_itr_;

public:
	tml::shared_ptr<tml::graphic::Canvas2D> canvas_2d;
	tml::shared_ptr<tml::graphic::Camera2D> camera_2d;
	tml::shared_ptr<tml::graphic::Camera3D> camera_3d;
	tml::shared_ptr<tml::graphic::FigureModel2D> bg_model;
	tml::TIME_REAL wait_update_time;
	tml::shared_ptr<tml::graphic::Font> wait_font;
	tml::shared_ptr<tml::graphic::FigureModel2D> wait_model;
	tml::shared_ptr<tml::scene::Node> main_node;

private:
	void Release(void);

protected:
	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);

public:
	InitScene();
	virtual ~InitScene();

	virtual void Init(void);
	INT Create(const cpp_base::scene::InitSceneDesc &);
};
}
}
