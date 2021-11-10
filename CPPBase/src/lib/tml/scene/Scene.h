/**
 * @file
 * @brief Scene�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include "../math/XNAMathVector.h"
#include "../math/XNAMathPosition.h"
#include "ManagerResource.h"


namespace tml {
namespace input {
class Manager;
}
namespace graphic {
class Manager;
class Canvas;
class Canvas2D;
class Canvas3D;
class Light;
class Light2D;
class Light3D;
class Fog;
class Fog2D;
class Fog3D;
class Model;
class Model2D;
class Model3D;
}
namespace sound {
class Manager;
}
}


namespace tml {
namespace scene {
/**
 * @brief SceneDesc�N���X
 */
class SceneDesc : public tml::scene::ManagerResourceDesc
{
public:
	std::wstring name;
	tml::XMPosition2D position_2d;
	tml::XMPosition3D position_3d;

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
 * @brief Release�֐�
 */
inline void tml::scene::SceneDesc::Release(void)
{
	return;
}


namespace tml {
namespace scene {
/**
 * @brief Scene�N���X
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
	std::vector<tml::shared_ptr<tml::graphic::Canvas>> canvas_cont_;
	tml::shared_ptr<tml::graphic::Canvas> empty_canvas_;
	std::list<tml::graphic::Canvas2D *> canvas_2d_cont_;
	std::list<tml::graphic::Canvas3D *> canvas_3d_cont_;
	std::vector<tml::shared_ptr<tml::graphic::Light>> light_cont_;
	tml::shared_ptr<tml::graphic::Light> empty_light_;
	std::list<tml::graphic::Light2D *> light_2d_cont_;
	std::list<tml::graphic::Light3D *> light_3d_cont_;
	std::vector<tml::shared_ptr<tml::graphic::Fog>> fog_cont_;
	tml::shared_ptr<tml::graphic::Fog> empty_fog_;
	std::list<tml::graphic::Fog2D *> fog_2d_cont_;
	std::list<tml::graphic::Fog3D *> fog_3d_cont_;
	std::vector<tml::shared_ptr<tml::graphic::Model>> model_cont_;
	tml::shared_ptr<tml::graphic::Model> empty_model_;
	std::list<tml::graphic::Model2D *> model_2d_cont_;
	std::list<tml::graphic::Model3D *> model_3d_cont_;

	std::list<tml::graphic::Canvas2D *> *draw_canvas_2d_cont_;
	std::list<tml::graphic::Canvas3D *> *draw_canvas_3d_cont_;

public:
	tml::XMPosition2D position_2d;
	tml::XMPosition3D position_3d;

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
	UINT GetCanvasCount(void) const;
	const tml::shared_ptr<tml::graphic::Canvas> &GetCanvas(const UINT);
	const tml::shared_ptr<tml::graphic::Canvas> &GetCanvasFast(const UINT);
	void SetCanvas(const UINT, const tml::shared_ptr<tml::graphic::Canvas> &);
	UINT GetLightCount(void) const;
	const tml::shared_ptr<tml::graphic::Light> &GetLight(const UINT);
	const tml::shared_ptr<tml::graphic::Light> &GetLightFast(const UINT);
	void SetLight(const UINT, const tml::shared_ptr<tml::graphic::Light> &);
	UINT GetFogCount(void) const;
	const tml::shared_ptr<tml::graphic::Fog> &GetFog(const UINT);
	const tml::shared_ptr<tml::graphic::Fog> &GetFogFast(const UINT);
	void SetFog(const UINT, const tml::shared_ptr<tml::graphic::Fog> &);
	UINT GetModelCount(void) const;
	const tml::shared_ptr<tml::graphic::Model> &GetModel(const UINT);
	const tml::shared_ptr<tml::graphic::Model> &GetModelFast(const UINT);
	void SetModel(const UINT, const tml::shared_ptr<tml::graphic::Model> &);

	void SetDrawCanvas(std::list<tml::graphic::Canvas2D *> *, std::list<tml::graphic::Canvas3D *> *);
	void ClearDrawCanvas(void);
};
}
}


/**
 * @brief GetInputManager�֐�
 * @return input_mgr (input_manager)
 */
inline tml::input::Manager *tml::scene::Scene::GetInputManager(void)
{
	return (this->input_mgr_);
}


/**
 * @brief GetGraphicManager�֐�
 * @return graphic_mgr (graphic_manager)
 */
inline tml::graphic::Manager *tml::scene::Scene::GetGraphicManager(void)
{
	return (this->graphic_mgr_);
}


/**
 * @brief GetSoundManager�֐�
 * @return sound_mgr (sound_manager)
 */
inline tml::sound::Manager *tml::scene::Scene::GetSoundManager(void)
{
	return (this->sound_mgr_);
}


/**
 * @brief GetName�֐�
 * @return name (name)
 */
inline const std::wstring &tml::scene::Scene::GetName(void) const
{
	return (this->name_);
}


/**
 * @brief SetName�֐�
 * @param name (name)
 */
inline void tml::scene::Scene::SetName(const WCHAR *name)
{
	this->name_ = name;

	return;
}


/**
 * @brief GetType�֐�
 * @return type (type)
 */
inline tml::ConstantUtil::SCENE::SCENE_TYPE tml::scene::Scene::GetType(void) const
{
	return (this->type_);
}


/**
 * @brief GetRunFlag�֐�
 * @return run_flg (run_flag)
 */
inline bool tml::scene::Scene::GetRunFlag(void) const
{
	return (this->run_flg_);
}


/**
 * @brief GetStartFlag�֐�
 * @return start_flg (start_flag)
 */
inline bool tml::scene::Scene::GetStartFlag(void) const
{
	return (this->start_flg_);
}


/**
 * @brief SetStartFlag�֐�
 * @param start_flg (start_flag)
 */
inline void tml::scene::Scene::SetStartFlag(const bool start_flg)
{
	this->start_flg_ = start_flg;

	return;
}


/**
 * @brief IsStarted�֐�
 * @return result_flg (result_flag)<br>
 * false=��J�n�ς�,true=�J�n�ς�
 */
inline bool tml::scene::Scene::IsStarted(void) const
{
	return (this->started_flg_);
}


/**
 * @brief GetRootNode�֐�
 * @return root_node (root_node)
 */
inline const tml::shared_ptr<tml::scene::Node> &tml::scene::Scene::GetRootNode(void)
{
	return (this->root_node_);
}


/**
 * @brief GetCanvasCount�֐�
 * @return canvas_cnt (canvas_count)
 */
inline UINT tml::scene::Scene::GetCanvasCount(void) const
{
	return (this->canvas_cont_.size());
}


/**
 * @brief GetCanvas�֐�
 * @param index (index)
 * @return canvas (canvas)<br>
 * nullptr=���s
 */
inline const tml::shared_ptr<tml::graphic::Canvas> &tml::scene::Scene::GetCanvas(const UINT index)
{
	if (index >= this->canvas_cont_.size()) {
		return (this->empty_canvas_);
	}

	return (this->canvas_cont_[index]);
}


/**
 * @brief GetCanvasFast�֐�
 * @param index (index)
 * @return canvas (canvas)<br>
 * nullptr=���s
 */
inline const tml::shared_ptr<tml::graphic::Canvas> &tml::scene::Scene::GetCanvasFast(const UINT index)
{
	return (this->canvas_cont_[index]);
}


/**
 * @brief GetLightCount�֐�
 * @return light_cnt (light_count)
 */
inline UINT tml::scene::Scene::GetLightCount(void) const
{
	return (this->light_cont_.size());
}


/**
 * @brief GetLight�֐�
 * @param index (index)
 * @return light (light)<br>
 * nullptr=���s
 */
inline const tml::shared_ptr<tml::graphic::Light> &tml::scene::Scene::GetLight(const UINT index)
{
	if (index >= this->light_cont_.size()) {
		return (this->empty_light_);
	}

	return (this->light_cont_[index]);
}


/**
 * @brief GetLightFast�֐�
 * @param index (index)
 * @return light (light)<br>
 * nullptr=���s
 */
inline const tml::shared_ptr<tml::graphic::Light> &tml::scene::Scene::GetLightFast(const UINT index)
{
	return (this->light_cont_[index]);
}


/**
 * @brief GetFogCount�֐�
 * @return fog_cnt (fog_count)
 */
inline UINT tml::scene::Scene::GetFogCount(void) const
{
	return (this->fog_cont_.size());
}


/**
 * @brief GetFog�֐�
 * @param index (index)
 * @return fog (fog)<br>
 * nullptr=���s
 */
inline const tml::shared_ptr<tml::graphic::Fog> &tml::scene::Scene::GetFog(const UINT index)
{
	if (index >= this->fog_cont_.size()) {
		return (this->empty_fog_);
	}

	return (this->fog_cont_[index]);
}


/**
 * @brief GetFogFast�֐�
 * @param index (index)
 * @return fog (fog)<br>
 * nullptr=���s
 */
inline const tml::shared_ptr<tml::graphic::Fog> &tml::scene::Scene::GetFogFast(const UINT index)
{
	return (this->fog_cont_[index]);
}


/**
 * @brief GetModelCount�֐�
 * @return model_cnt (model_count)
 */
inline UINT tml::scene::Scene::GetModelCount(void) const
{
	return (this->model_cont_.size());
}


/**
 * @brief GetModel�֐�
 * @param index (index)
 * @return model (model)<br>
 * nullptr=���s
 */
inline const tml::shared_ptr<tml::graphic::Model> &tml::scene::Scene::GetModel(const UINT index)
{
	if (index >= this->model_cont_.size()) {
		return (this->empty_model_);
	}

	return (this->model_cont_[index]);
}


/**
 * @brief GetModelFast�֐�
 * @param index (index)
 * @return model (model)<br>
 * nullptr=���s
 */
inline const tml::shared_ptr<tml::graphic::Model> &tml::scene::Scene::GetModelFast(const UINT index)
{
	return (this->model_cont_[index]);
}


/**
 * @brief SetDrawCanvas�֐�
 * @param draw_canvas_2d_cont (draw_canvas_2d_container)
 * @param draw_canvas_3d_cont (draw_canvas_3d_container)
 */
inline void tml::scene::Scene::SetDrawCanvas(std::list<tml::graphic::Canvas2D *> *draw_canvas_2d_cont, std::list<tml::graphic::Canvas3D *> *draw_canvas_3d_cont)
{
	this->draw_canvas_2d_cont_ = draw_canvas_2d_cont;
	this->draw_canvas_3d_cont_ = draw_canvas_3d_cont;

	return;
}


/**
 * @brief ClearDrawCanvas�֐�
 */
inline void tml::scene::Scene::ClearDrawCanvas(void)
{
	this->draw_canvas_2d_cont_ = nullptr;
	this->draw_canvas_3d_cont_ = nullptr;

	return;
}
