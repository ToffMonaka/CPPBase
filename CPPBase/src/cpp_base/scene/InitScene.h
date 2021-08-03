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

public:
	tml::shared_ptr<tml::graphic::Canvas2D> canvas_2d;
	tml::shared_ptr<tml::graphic::Camera2D> camera_2d;
	tml::shared_ptr<tml::graphic::Camera3D> camera_3d;

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
