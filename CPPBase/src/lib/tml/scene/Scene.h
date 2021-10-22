/**
 * @file
 * @brief Sceneヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include "ManagerResource.h"


namespace tml {
namespace input {
class Manager;
}
namespace graphic {
class Manager;
class Canvas2D;
class Camera2D;
class Model2D;
}
namespace sound {
class Manager;
}
}


namespace tml {
namespace scene {
/**
 * @brief SceneDescクラス
 */
class SceneDesc : public tml::scene::ManagerResourceDesc
{
public:
	std::wstring name;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	SceneDesc();
	virtual ~SceneDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::scene::SceneDesc::Release(void)
{
	return;
}


namespace tml {
namespace scene {
/**
 * @brief Sceneクラス
 */
class Scene : public tml::scene::ManagerResource
{
public: Scene(const tml::scene::Scene &) = delete;
public: tml::scene::Scene &operator =(const tml::scene::Scene &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT RESOURCE_MAIN_INDEX = static_cast<UINT>(tml::ConstantUtil::SCENE::RESOURCE_TYPE::SCENE);
	static const UINT RESOURCE_SUB_INDEX = static_cast<UINT>(tml::ConstantUtil::SCENE::SCENE_TYPE::BASE);

private:
	tml::input::Manager *input_mgr_;
	tml::graphic::Manager *graphic_mgr_;
	tml::sound::Manager *sound_mgr_;
	std::wstring name_;
	tml::ConstantUtil::SCENE::SCENE_TYPE type_;
	bool run_flg_;
	bool start_flg_;
	bool started_flg_;
	tml::shared_ptr<tml::scene::Node> root_node_;
	tml::shared_ptr<tml::graphic::Canvas2D> canvas_2d_;
	tml::shared_ptr<tml::graphic::Camera2D> camera_2d_;
	std::vector<tml::shared_ptr<tml::graphic::Model2D>> model_2d_cont_;
	tml::shared_ptr<tml::graphic::Model2D> empty_model_2d_;

private:
	void Release(void);

protected:
	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);

public:
	Scene();
	virtual ~Scene();

	virtual void Init(void);
	INT Create(const tml::scene::SceneDesc &);

	INT Start(void);
	void End(void);
	void Update(void);

	tml::input::Manager *GetInputManager(void);
	tml::graphic::Manager *GetGraphicManager(void);
	tml::sound::Manager *GetSoundManager(void);
	const std::wstring &GetName(void) const;
	void SetName(const WCHAR *);
	tml::ConstantUtil::SCENE::SCENE_TYPE GetType(void) const;
	bool GetRunFlag(void) const;
	void SetRunFlag(const bool);
	bool GetStartFlag(void) const;
	void SetStartFlag(const bool);
	bool IsStarted(void) const;
	const tml::shared_ptr<tml::scene::Node> &GetRootNode(void);
	void SetRootNode(void);
	const tml::shared_ptr<tml::graphic::Canvas2D> &GetCanvas2D(void);
	void SetCanvas2D(const tml::shared_ptr<tml::graphic::Canvas2D> &);
	const tml::shared_ptr<tml::graphic::Camera2D> &GetCamera2D(void);
	void SetCamera2D(const tml::shared_ptr<tml::graphic::Camera2D> &);
	UINT GetModel2DCount(void) const;
	const tml::shared_ptr<tml::graphic::Model2D> &GetModel2D(const UINT);
	const tml::shared_ptr<tml::graphic::Model2D> &GetModel2DFast(const UINT);
	void SetModel2D(const UINT, const tml::shared_ptr<tml::graphic::Model2D> &);
};
}
}


/**
 * @brief GetInputManager関数
 * @return input_mgr (input_manager)
 */
inline tml::input::Manager *tml::scene::Scene::GetInputManager(void)
{
	return (this->input_mgr_);
}


/**
 * @brief GetGraphicManager関数
 * @return graphic_mgr (graphic_manager)
 */
inline tml::graphic::Manager *tml::scene::Scene::GetGraphicManager(void)
{
	return (this->graphic_mgr_);
}


/**
 * @brief GetSoundManager関数
 * @return sound_mgr (sound_manager)
 */
inline tml::sound::Manager *tml::scene::Scene::GetSoundManager(void)
{
	return (this->sound_mgr_);
}


/**
 * @brief GetName関数
 * @return name (name)
 */
inline const std::wstring &tml::scene::Scene::GetName(void) const
{
	return (this->name_);
}


/**
 * @brief SetName関数
 * @param name (name)
 */
inline void tml::scene::Scene::SetName(const WCHAR *name)
{
	this->name_ = name;

	return;
}


/**
 * @brief GetType関数
 * @return type (type)
 */
inline tml::ConstantUtil::SCENE::SCENE_TYPE tml::scene::Scene::GetType(void) const
{
	return (this->type_);
}


/**
 * @brief GetRunFlag関数
 * @return run_flg (run_flag)
 */
inline bool tml::scene::Scene::GetRunFlag(void) const
{
	return (this->run_flg_);
}


/**
 * @brief GetStartFlag関数
 * @return start_flg (start_flag)
 */
inline bool tml::scene::Scene::GetStartFlag(void) const
{
	return (this->start_flg_);
}


/**
 * @brief SetStartFlag関数
 * @param start_flg (start_flag)
 */
inline void tml::scene::Scene::SetStartFlag(const bool start_flg)
{
	this->start_flg_ = start_flg;

	return;
}


/**
 * @brief IsStarted関数
 * @return result_flg (result_flag)<br>
 * false=非開始済み,true=開始済み
 */
inline bool tml::scene::Scene::IsStarted(void) const
{
	return (this->started_flg_);
}


/**
 * @brief GetRootNode関数
 * @return root_node (root_node)
 */
inline const tml::shared_ptr<tml::scene::Node> &tml::scene::Scene::GetRootNode(void)
{
	return (this->root_node_);
}


/**
 * @brief GetCanvas2D関数
 * @return canvas_2d (canvas_2d)
 */
inline const tml::shared_ptr<tml::graphic::Canvas2D> &tml::scene::Scene::GetCanvas2D(void)
{
	return (this->canvas_2d_);
}


/**
 * @brief GetCamera2D関数
 * @return camera_2d (camera_2d)
 */
inline const tml::shared_ptr<tml::graphic::Camera2D> &tml::scene::Scene::GetCamera2D(void)
{
	return (this->camera_2d_);
}


/**
 * @brief GetModel2DCount関数
 * @return model_2d_cnt (model_2d_count)
 */
inline UINT tml::scene::Scene::GetModel2DCount(void) const
{
	return (this->model_2d_cont_.size());
}


/**
 * @brief GetModel2D関数
 * @param index (index)
 * @return model_2d (model_2d)<br>
 * nullptr=失敗
 */
inline const tml::shared_ptr<tml::graphic::Model2D> &tml::scene::Scene::GetModel2D(const UINT index)
{
	if (index >= this->model_2d_cont_.size()) {
		return (this->empty_model_2d_);
	}

	return (this->model_2d_cont_[index]);
}


/**
 * @brief GetModel2DFast関数
 * @param index (index)
 * @return model_2d (model_2d)<br>
 * nullptr=失敗
 */
inline const tml::shared_ptr<tml::graphic::Model2D> &tml::scene::Scene::GetModel2DFast(const UINT index)
{
	return (this->model_2d_cont_[index]);
}
