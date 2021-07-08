/**
 * @file
 * @brief TitleSceneヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "BaseScene.h"


namespace cpp_base {
namespace scene {
/**
 * @brief TitleSceneDescクラス
 */
class TitleSceneDesc : public cpp_base::scene::BaseSceneDesc
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
	cpp_base::scene::BaseSceneDesc::Release();

	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief TitleSceneクラス
 */
class TitleScene : public cpp_base::scene::BaseScene
{
public: TitleScene(const cpp_base::scene::TitleScene &) = delete;
public: cpp_base::scene::TitleScene &operator =(const cpp_base::scene::TitleScene &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

public:
	tml::shared_ptr<tml::graphic::Canvas2D> canvas_2d;
	tml::shared_ptr<tml::graphic::Camera2D> camera_2d;
	tml::shared_ptr<tml::graphic::Camera3D> camera_3d;

protected:
	void Release(void);

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Init(void);
	INT Create(const cpp_base::scene::TitleSceneDesc &);

	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);
};
}
}
