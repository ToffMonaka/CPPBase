/**
 * @file
 * @brief SelectSceneヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "BaseScene.h"


namespace cpp_base {
namespace scene {
/**
 * @brief SelectSceneDescクラス
 */
class SelectSceneDesc : public cpp_base::scene::BaseSceneDesc
{
public:

protected:
	void Release(void);

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
	cpp_base::scene::BaseSceneDesc::Release();

	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief SelectSceneクラス
 */
class SelectScene : public cpp_base::scene::BaseScene
{
public: SelectScene(const cpp_base::scene::SelectScene &) = delete;
public: cpp_base::scene::SelectScene &operator =(const cpp_base::scene::SelectScene &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

public:
	tml::shared_ptr<tml::graphic::Canvas2D> canvas_2d;
	tml::shared_ptr<tml::graphic::Camera2D> camera_2d;
	tml::shared_ptr<tml::graphic::Camera3D> camera_3d;

protected:
	void Release(void);

public:
	SelectScene();
	virtual ~SelectScene();

	virtual void Init(void);
	INT Create(const cpp_base::scene::SelectSceneDesc &);

	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);
};
}
}
