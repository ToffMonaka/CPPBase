/**
 * @file
 * @brief StageSceneヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "Scene.h"


namespace cpp_base {
namespace scene {
/**
 * @brief StageSceneDescクラス
 */
class StageSceneDesc : public cpp_base::scene::SceneDesc
{
public:

private:
	void Release(void);

protected:
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
	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief StageSceneクラス
 */
class StageScene : public cpp_base::scene::Scene
{
public: StageScene(const cpp_base::scene::StageScene &) = delete;
public: cpp_base::scene::StageScene &operator =(const cpp_base::scene::StageScene &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	const cpp_base::scene::StageSceneDesc *desc_;
	UINT progress_type_;

public:
	tml::shared_ptr<tml::graphic::Canvas2D> canvas_2d;
	tml::shared_ptr<tml::graphic::Canvas3D> canvas_3d;
	tml::shared_ptr<tml::graphic::Camera2D> camera_2d;
	tml::shared_ptr<tml::graphic::Camera3D> camera_3d;
	tml::shared_ptr<tml::scene::Node> main_node;
	tml::shared_ptr<tml::scene::Node> stage_layout_node;
	tml::shared_ptr<tml::scene::Node> stage_node;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);

public:
	StageScene();
	virtual ~StageScene();

	virtual void Init(void);

	const cpp_base::scene::StageSceneDesc *GetDesc(void) const;

};
}
}


/**
 * @brief GetDesc関数
 * @return desc (desc)
 */
inline const cpp_base::scene::StageSceneDesc *cpp_base::scene::StageScene::GetDesc(void) const
{
	return (this->desc_);
}
