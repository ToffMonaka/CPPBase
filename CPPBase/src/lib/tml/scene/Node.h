/**
 * @file
 * @brief NodeÉwÉbÉ_Å[ÉtÉ@ÉCÉã
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include "../math/Transform.h"
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
 * @brief NodeDescÉNÉâÉX
 */
class NodeDesc : public tml::scene::ManagerResourceDesc
{
public:
	std::wstring name;
	tml::Transform2D transform_2d;
	tml::Transform3D transform_3d;
	tml::XMFLOAT4EX color;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	NodeDesc();
	virtual ~NodeDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Releaseä÷êî
 */
inline void tml::scene::NodeDesc::Release(void)
{
	return;
}


namespace tml {
namespace scene {
/**
 * @brief NodeÉNÉâÉX
 */
class Node : public tml::scene::ManagerResource
{
public: Node(const tml::scene::Node &) = delete;
public: tml::scene::Node &operator =(const tml::scene::Node &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT RESOURCE_TYPE = static_cast<UINT>(tml::ConstantUtil::SCENE::RESOURCE_TYPE::NODE);

public:
	static const tml::shared_ptr<tml::scene::Node> empty_child_node;
	static const tml::shared_ptr<tml::graphic::Canvas> empty_canvas;
	static const tml::shared_ptr<tml::graphic::Light> empty_light;
	static const tml::shared_ptr<tml::graphic::Fog> empty_fog;
	static const tml::shared_ptr<tml::graphic::Model> empty_model;

private:
	const tml::scene::NodeDesc *desc_;
	tml::input::Manager *input_mgr_;
	tml::graphic::Manager *graphic_mgr_;
	tml::sound::Manager *sound_mgr_;
	bool run_flg_;
	bool start_flg_;
	bool started_flg_;
	tml::scene::Node *parent_node_;
	std::list<tml::shared_ptr<tml::scene::Node>> child_node_cont_;
	std::vector<tml::shared_ptr<tml::graphic::Canvas>> canvas_cont_;
	std::list<tml::graphic::Canvas2D *> canvas_2d_cont_;
	std::list<tml::graphic::Canvas3D *> canvas_3d_cont_;
	std::vector<tml::shared_ptr<tml::graphic::Light>> light_cont_;
	std::list<tml::graphic::Light2D *> light_2d_cont_;
	std::list<tml::graphic::Light3D *> light_3d_cont_;
	std::vector<tml::shared_ptr<tml::graphic::Fog>> fog_cont_;
	std::list<tml::graphic::Fog2D *> fog_2d_cont_;
	std::list<tml::graphic::Fog3D *> fog_3d_cont_;
	std::vector<tml::shared_ptr<tml::graphic::Model>> model_cont_;
	std::list<tml::graphic::Model2D *> model_2d_cont_;
	std::list<tml::graphic::Model3D *> model_3d_cont_;

	std::list<tml::graphic::Canvas2D *> *draw_canvas_2d_cont_;
	std::list<tml::graphic::Canvas3D *> *draw_canvas_3d_cont_;

public:
	std::wstring name;
	tml::Transform2D transform_2d;
	tml::Transform3D transform_3d;
	tml::XMFLOAT4EX color;

private:
	void Release(void);

	const tml::shared_ptr<tml::scene::Node> &GetChildNodeRecursivePart(const std::list<tml::shared_ptr<tml::scene::Node>> &, const WCHAR *);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);

public:
	Node();
	virtual ~Node();

	virtual void Init(void);

	INT Start(void);
	void End(void);
	void Update(void);

	const tml::scene::NodeDesc *GetDesc(void) const;
	tml::input::Manager *GetInputManager(void);
	tml::graphic::Manager *GetGraphicManager(void);
	tml::sound::Manager *GetSoundManager(void);
	bool GetRunFlag(void) const;
	void SetRunFlag(const bool);
	bool GetStartFlag(void) const;
	void SetStartFlag(const bool);
	bool IsStarted(void) const;
	tml::scene::Node *GetParentNode(void);
	tml::scene::Node *GetParentNode(const WCHAR *);
	void SetParentNode(tml::scene::Node *);
	const std::list<tml::shared_ptr<tml::scene::Node>> &GetChildNodeContainer(void);
	const tml::shared_ptr<tml::scene::Node> &GetChildNode(void);
	const tml::shared_ptr<tml::scene::Node> &GetChildNode(const WCHAR *);
	INT AddChildNode(const tml::shared_ptr<tml::scene::Node> &, const bool deferred_flg = true);
	void RemoveChildNode(const bool deferred_flg = true);
	void RemoveChildNode(const tml::shared_ptr<tml::scene::Node> &, const bool deferred_flg = true);
	void RemoveChildNodeFromParentNode(const bool deferred_flg = true);
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
 * @brief GetDescä÷êî
 * @return desc (desc)
 */
inline const tml::scene::NodeDesc *tml::scene::Node::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief GetInputManagerä÷êî
 * @return input_mgr (input_manager)
 */
inline tml::input::Manager *tml::scene::Node::GetInputManager(void)
{
	return (this->input_mgr_);
}


/**
 * @brief GetGraphicManagerä÷êî
 * @return graphic_mgr (graphic_manager)
 */
inline tml::graphic::Manager *tml::scene::Node::GetGraphicManager(void)
{
	return (this->graphic_mgr_);
}


/**
 * @brief GetSoundManagerä÷êî
 * @return sound_mgr (sound_manager)
 */
inline tml::sound::Manager *tml::scene::Node::GetSoundManager(void)
{
	return (this->sound_mgr_);
}


/**
 * @brief GetRunFlagä÷êî
 * @return run_flg (run_flag)
 */
inline bool tml::scene::Node::GetRunFlag(void) const
{
	return (this->run_flg_);
}


/**
 * @brief GetStartFlagä÷êî
 * @return start_flg (start_flag)
 */
inline bool tml::scene::Node::GetStartFlag(void) const
{
	return (this->start_flg_);
}


/**
 * @brief SetStartFlagä÷êî
 * @param start_flg (start_flag)
 */
inline void tml::scene::Node::SetStartFlag(const bool start_flg)
{
	this->start_flg_ = start_flg;

	return;
}


/**
 * @brief IsStartedä÷êî
 * @return result_flg (result_flag)<br>
 * false=îÒäJénçœÇ›,true=äJénçœÇ›
 */
inline bool tml::scene::Node::IsStarted(void) const
{
	return (this->started_flg_);
}


/**
 * @brief GetParentNodeä÷êî
 * @return parent_node (parent_node)
 */
inline tml::scene::Node *tml::scene::Node::GetParentNode(void)
{
	return (this->parent_node_);
}


/**
 * @brief GetParentNodeä÷êî
 * @param parent_node_name (parent_node_name)
 * @return parent_node (parent_node)
 */
inline tml::scene::Node *tml::scene::Node::GetParentNode(const WCHAR *parent_node_name)
{
	auto parent_node = this->parent_node_;

	while (parent_node != nullptr) {
		if (parent_node->name == parent_node_name) {
			break;
		}

		parent_node = parent_node->GetParentNode();
	}

	return (parent_node);
}


/**
 * @brief SetParentNodeä÷êî
 * @param parent_node (parent_node)
 */
inline void tml::scene::Node::SetParentNode(tml::scene::Node *parent_node)
{
	if (parent_node == this) {
		return;
	}

	this->parent_node_ = parent_node;

	return;
}


/**
 * @brief GetChildNodeContainerä÷êî
 * @return child_node_container (child_node_container)
 */
inline const std::list<tml::shared_ptr<tml::scene::Node>> &tml::scene::Node::GetChildNodeContainer(void)
{
	return (this->child_node_cont_);
}


/**
 * @brief GetChildNodeä÷êî
 * @return child_node (child_node)<br>
 * nullptr=é∏îs
 */
inline const tml::shared_ptr<tml::scene::Node> &tml::scene::Node::GetChildNode(void)
{
	if (this->child_node_cont_.empty()) {
		return (this->empty_child_node);
	}

	return (this->child_node_cont_.front());
}


/**
 * @brief GetChildNodeä÷êî
 * @param child_node_name (child_node_name)
 * @return child_node (child_node)<br>
 * nullptr=é∏îs
 */
inline const tml::shared_ptr<tml::scene::Node> &tml::scene::Node::GetChildNode(const WCHAR *child_node_name)
{
	if ((child_node_name == nullptr)
	|| (child_node_name[0] == 0)) {
		return (this->empty_child_node);
	}

	return (this->GetChildNodeRecursivePart(this->child_node_cont_, child_node_name));
}


/**
 * @brief GetCanvasCountä÷êî
 * @return canvas_cnt (canvas_count)
 */
inline UINT tml::scene::Node::GetCanvasCount(void) const
{
	return (this->canvas_cont_.size());
}


/**
 * @brief GetCanvasä÷êî
 * @param index (index)
 * @return canvas (canvas)<br>
 * nullptr=é∏îs
 */
inline const tml::shared_ptr<tml::graphic::Canvas> &tml::scene::Node::GetCanvas(const UINT index)
{
	if (index >= this->canvas_cont_.size()) {
		return (this->empty_canvas);
	}

	return (this->canvas_cont_[index]);
}


/**
 * @brief GetCanvasFastä÷êî
 * @param index (index)
 * @return canvas (canvas)<br>
 * nullptr=é∏îs
 */
inline const tml::shared_ptr<tml::graphic::Canvas> &tml::scene::Node::GetCanvasFast(const UINT index)
{
	return (this->canvas_cont_[index]);
}


/**
 * @brief GetLightCountä÷êî
 * @return light_cnt (light_count)
 */
inline UINT tml::scene::Node::GetLightCount(void) const
{
	return (this->light_cont_.size());
}


/**
 * @brief GetLightä÷êî
 * @param index (index)
 * @return light (light)<br>
 * nullptr=é∏îs
 */
inline const tml::shared_ptr<tml::graphic::Light> &tml::scene::Node::GetLight(const UINT index)
{
	if (index >= this->light_cont_.size()) {
		return (this->empty_light);
	}

	return (this->light_cont_[index]);
}


/**
 * @brief GetLightFastä÷êî
 * @param index (index)
 * @return light (light)<br>
 * nullptr=é∏îs
 */
inline const tml::shared_ptr<tml::graphic::Light> &tml::scene::Node::GetLightFast(const UINT index)
{
	return (this->light_cont_[index]);
}


/**
 * @brief GetFogCountä÷êî
 * @return fog_cnt (fog_count)
 */
inline UINT tml::scene::Node::GetFogCount(void) const
{
	return (this->fog_cont_.size());
}


/**
 * @brief GetFogä÷êî
 * @param index (index)
 * @return fog (fog)<br>
 * nullptr=é∏îs
 */
inline const tml::shared_ptr<tml::graphic::Fog> &tml::scene::Node::GetFog(const UINT index)
{
	if (index >= this->fog_cont_.size()) {
		return (this->empty_fog);
	}

	return (this->fog_cont_[index]);
}


/**
 * @brief GetFogFastä÷êî
 * @param index (index)
 * @return fog (fog)<br>
 * nullptr=é∏îs
 */
inline const tml::shared_ptr<tml::graphic::Fog> &tml::scene::Node::GetFogFast(const UINT index)
{
	return (this->fog_cont_[index]);
}


/**
 * @brief GetModelCountä÷êî
 * @return model_cnt (model_count)
 */
inline UINT tml::scene::Node::GetModelCount(void) const
{
	return (this->model_cont_.size());
}


/**
 * @brief GetModelä÷êî
 * @param index (index)
 * @return model (model)<br>
 * nullptr=é∏îs
 */
inline const tml::shared_ptr<tml::graphic::Model> &tml::scene::Node::GetModel(const UINT index)
{
	if (index >= this->model_cont_.size()) {
		return (this->empty_model);
	}

	return (this->model_cont_[index]);
}


/**
 * @brief GetModelFastä÷êî
 * @param index (index)
 * @return model (model)<br>
 * nullptr=é∏îs
 */
inline const tml::shared_ptr<tml::graphic::Model> &tml::scene::Node::GetModelFast(const UINT index)
{
	return (this->model_cont_[index]);
}


/**
 * @brief SetDrawCanvasä÷êî
 * @param draw_canvas_2d_cont (draw_canvas_2d_container)
 * @param draw_canvas_3d_cont (draw_canvas_3d_container)
 */
inline void tml::scene::Node::SetDrawCanvas(std::list<tml::graphic::Canvas2D *> *draw_canvas_2d_cont, std::list<tml::graphic::Canvas3D *> *draw_canvas_3d_cont)
{
	this->draw_canvas_2d_cont_ = draw_canvas_2d_cont;
	this->draw_canvas_3d_cont_ = draw_canvas_3d_cont;

	return;
}


/**
 * @brief ClearDrawCanvasä÷êî
 */
inline void tml::scene::Node::ClearDrawCanvas(void)
{
	this->draw_canvas_2d_cont_ = nullptr;
	this->draw_canvas_3d_cont_ = nullptr;

	return;
}
