/**
 * @file
 * @brief TitleSceneヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SCENE.h"
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

protected:
	void Release(void);

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Init(void);
	INT Create(const cpp_base::scene::TitleSceneDesc &);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::TitleScene::Release(void)
{
	tml::scene::Scene::Release();

	return;
}
