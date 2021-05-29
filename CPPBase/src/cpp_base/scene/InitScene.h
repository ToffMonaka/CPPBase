/**
 * @file
 * @brief InitSceneヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "BaseScene.h"


namespace cpp_base {
namespace scene {
/**
 * @brief InitSceneDescクラス
 */
class InitSceneDesc : public cpp_base::scene::BaseSceneDesc
{
public:

protected:
	void Release(void);

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
	cpp_base::scene::BaseSceneDesc::Release();

	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief InitSceneクラス
 */
class InitScene : public cpp_base::scene::BaseScene
{
public: InitScene(const cpp_base::scene::InitScene &) = delete;
public: cpp_base::scene::InitScene &operator =(const cpp_base::scene::InitScene &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	tml::shared_ptr<tml::graphic::Camera> camera_;
	tml::shared_ptr<tml::graphic::Object2DModel> bg_model_;
	tml::TIME_REAL wait_update_time_;
	tml::shared_ptr<tml::graphic::Object2DModel> wait_model_;
	tml::shared_ptr<tml::graphic::Font> wait_font_;

protected:
	void Release(void);

public:
	InitScene();
	virtual ~InitScene();

	virtual void Init(void);
	INT Create(const cpp_base::scene::InitSceneDesc &);

	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);
};
}
}
