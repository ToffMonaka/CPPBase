/**
 * @file
 * @brief StageSceneヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "BaseScene.h"


namespace cpp_base {
namespace scene {
/**
 * @brief StageSceneDescクラス
 */
class StageSceneDesc : public cpp_base::scene::BaseSceneDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	StageSceneDesc();
	virtual ~StageSceneDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::StageSceneDesc::Release(void)
{
	cpp_base::scene::BaseSceneDesc::Release();

	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief StageSceneクラス
 */
class StageScene : public cpp_base::scene::BaseScene
{
public: StageScene(const cpp_base::scene::StageScene &) = delete;
public: cpp_base::scene::StageScene &operator =(const cpp_base::scene::StageScene &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

public:
	tml::shared_ptr<tml::graphic::Canvas2D> canvas_2d;
	tml::shared_ptr<tml::graphic::Camera2D> camera_2d;
	tml::shared_ptr<tml::graphic::Camera3D> camera_3d;

protected:
	void Release(void);

public:
	StageScene();
	virtual ~StageScene();

	virtual void Init(void);
	INT Create(const cpp_base::scene::StageSceneDesc &);

	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);
};
}
}
