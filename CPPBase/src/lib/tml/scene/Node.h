/**
 * @file
 * @brief Nodeヘッダーファイル
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
class Canvas;
class Canvas2D;
class Canvas3D;
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
 * @brief NodeDescクラス
 */
class NodeDesc : public tml::scene::ManagerResourceDesc
{
public:
	std::wstring name;

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
 * @brief Release関数
 */
inline void tml::scene::NodeDesc::Release(void)
{
	return;
}


namespace tml {
namespace scene {
/**
 * @brief Nodeクラス
 */
class Node : public tml::scene::ManagerResource
{
public: Node(const tml::scene::Node &) = delete;
public: tml::scene::Node &operator =(const tml::scene::Node &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT RESOURCE_MAIN_INDEX = static_cast<UINT>(tml::ConstantUtil::SCENE::RESOURCE_TYPE::NODE);
	static const UINT RESOURCE_SUB_INDEX = static_cast<UINT>(tml::ConstantUtil::SCENE::NODE_TYPE::BASE);

private:
	tml::input::Manager *input_mgr_;
	tml::graphic::Manager *graphic_mgr_;
	tml::sound::Manager *sound_mgr_;
	std::wstring name_;
	tml::ConstantUtil::SCENE::NODE_TYPE type_;
	bool run_flg_;
	bool start_flg_;
	bool started_flg_;
	tml::scene::Node *parent_node_;
	std::list<tml::shared_ptr<tml::scene::Node>> child_node_cont_;
	tml::shared_ptr<tml::scene::Node> empty_child_node_;
	std::vector<tml::shared_ptr<tml::graphic::Canvas>> canvas_cont_;
	tml::shared_ptr<tml::graphic::Canvas> empty_canvas_;
	std::list<tml::graphic::Canvas2D *> canvas_2d_cont_;
	std::list<tml::graphic::Canvas3D *> canvas_3d_cont_;
	std::vector<tml::shared_ptr<tml::graphic::Model>> model_cont_;
	tml::shared_ptr<tml::graphic::Model> empty_model_;
	std::list<tml::graphic::Model2D *> model_2d_cont_;
	std::list<tml::graphic::Model3D *> model_3d_cont_;

	std::list<tml::graphic::Canvas2D *> *draw_canvas_2d_cont_;
	std::list<tml::graphic::Canvas3D *> *draw_canvas_3d_cont_;

private:
	void Release(void);

	const tml::shared_ptr<tml::scene::Node> &GetChildNodeRecursivePart(const std::list<tml::shared_ptr<tml::scene::Node>> &, const WCHAR *);

protected:
	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);

public:
	Node();
	virtual ~Node();

	virtual void Init(void);
	INT Create(const tml::scene::NodeDesc &);

	INT Start(void);
	void End(void);
	void Update(void);

	tml::input::Manager *GetInputManager(void);
	tml::graphic::Manager *GetGraphicManager(void);
	tml::sound::Manager *GetSoundManager(void);
	const std::wstring &GetName(void) const;
	void SetName(const WCHAR *);
	tml::ConstantUtil::SCENE::NODE_TYPE GetType(void) const;
	bool GetRunFlag(void) const;
	void SetRunFlag(const bool);
	bool GetStartFlag(void) const;
	void SetStartFlag(const bool);
	bool IsStarted(void) const;
	tml::scene::Node *GetParentNode(void);
	void SetParentNode(tml::scene::Node *);
	const std::list<tml::shared_ptr<tml::scene::Node>> &GetChildNodeContainer(void);
	const tml::shared_ptr<tml::scene::Node> &GetChildNode(const WCHAR *);
	INT AddChildNode(const tml::shared_ptr<tml::scene::Node> &, const bool event_flg = true);
	void RemoveChildNode(const bool event_flg = true);
	void RemoveChildNode(const tml::shared_ptr<tml::scene::Node> &, const bool event_flg = true);
	void RemoveChildNodeFromParentNode(const bool event_flg = true);
	UINT GetCanvasCount(void) const;
	const tml::shared_ptr<tml::graphic::Canvas> &GetCanvas(const UINT);
	const tml::shared_ptr<tml::graphic::Canvas> &GetCanvasFast(const UINT);
	void SetCanvas(const UINT, const tml::shared_ptr<tml::graphic::Canvas> &);
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
 * @brief GetInputManager関数
 * @return input_mgr (input_manager)
 */
inline tml::input::Manager *tml::scene::Node::GetInputManager(void)
{
	return (this->input_mgr_);
}


/**
 * @brief GetGraphicManager関数
 * @return graphic_mgr (graphic_manager)
 */
inline tml::graphic::Manager *tml::scene::Node::GetGraphicManager(void)
{
	return (this->graphic_mgr_);
}


/**
 * @brief GetSoundManager関数
 * @return sound_mgr (sound_manager)
 */
inline tml::sound::Manager *tml::scene::Node::GetSoundManager(void)
{
	return (this->sound_mgr_);
}


/**
 * @brief GetName関数
 * @return name (name)
 */
inline const std::wstring &tml::scene::Node::GetName(void) const
{
	return (this->name_);
}


/**
 * @brief SetName関数
 * @param name (name)
 */
inline void tml::scene::Node::SetName(const WCHAR *name)
{
	this->name_ = name;

	return;
}


/**
 * @brief GetType関数
 * @return type (type)
 */
inline tml::ConstantUtil::SCENE::NODE_TYPE tml::scene::Node::GetType(void) const
{
	return (this->type_);
}


/**
 * @brief GetRunFlag関数
 * @return run_flg (run_flag)
 */
inline bool tml::scene::Node::GetRunFlag(void) const
{
	return (this->run_flg_);
}


/**
 * @brief GetStartFlag関数
 * @return start_flg (start_flag)
 */
inline bool tml::scene::Node::GetStartFlag(void) const
{
	return (this->start_flg_);
}


/**
 * @brief SetStartFlag関数
 * @param start_flg (start_flag)
 */
inline void tml::scene::Node::SetStartFlag(const bool start_flg)
{
	this->start_flg_ = start_flg;

	return;
}


/**
 * @brief IsStarted関数
 * @return result_flg (result_flag)<br>
 * false=非開始済み,true=開始済み
 */
inline bool tml::scene::Node::IsStarted(void) const
{
	return (this->started_flg_);
}


/**
 * @brief GetParentNode関数
 * @return parent_node (parent_node)
 */
inline tml::scene::Node *tml::scene::Node::GetParentNode(void)
{
	return (this->parent_node_);
}


/**
 * @brief GetChildNodeContainer関数
 * @return child_node_container (child_node_container)
 */
inline const std::list<tml::shared_ptr<tml::scene::Node>> &tml::scene::Node::GetChildNodeContainer(void)
{
	return (this->child_node_cont_);
}


/**
 * @brief GetChildNode関数
 * @param child_node_name (child_node_name)
 * @return child_node (child_node)<br>
 * nullptr=失敗
 */
inline const tml::shared_ptr<tml::scene::Node> &tml::scene::Node::GetChildNode(const WCHAR *child_node_name)
{
	if ((child_node_name == nullptr)
	|| (child_node_name[0] == 0)) {
		return (this->empty_child_node_);
	}

	return (this->GetChildNodeRecursivePart(this->child_node_cont_, child_node_name));
}


/**
 * @brief GetCanvasCount関数
 * @return canvas_cnt (canvas_count)
 */
inline UINT tml::scene::Node::GetCanvasCount(void) const
{
	return (this->canvas_cont_.size());
}


/**
 * @brief GetCanvas関数
 * @param index (index)
 * @return canvas (canvas)<br>
 * nullptr=失敗
 */
inline const tml::shared_ptr<tml::graphic::Canvas> &tml::scene::Node::GetCanvas(const UINT index)
{
	if (index >= this->canvas_cont_.size()) {
		return (this->empty_canvas_);
	}

	return (this->canvas_cont_[index]);
}


/**
 * @brief GetCanvasFast関数
 * @param index (index)
 * @return canvas (canvas)<br>
 * nullptr=失敗
 */
inline const tml::shared_ptr<tml::graphic::Canvas> &tml::scene::Node::GetCanvasFast(const UINT index)
{
	return (this->canvas_cont_[index]);
}


/**
 * @brief GetModelCount関数
 * @return model_cnt (model_count)
 */
inline UINT tml::scene::Node::GetModelCount(void) const
{
	return (this->model_cont_.size());
}


/**
 * @brief GetModel関数
 * @param index (index)
 * @return model (model)<br>
 * nullptr=失敗
 */
inline const tml::shared_ptr<tml::graphic::Model> &tml::scene::Node::GetModel(const UINT index)
{
	if (index >= this->model_cont_.size()) {
		return (this->empty_model_);
	}

	return (this->model_cont_[index]);
}


/**
 * @brief GetModelFast関数
 * @param index (index)
 * @return model (model)<br>
 * nullptr=失敗
 */
inline const tml::shared_ptr<tml::graphic::Model> &tml::scene::Node::GetModelFast(const UINT index)
{
	return (this->model_cont_[index]);
}


/**
 * @brief SetDrawCanvas関数
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
 * @brief ClearDrawCanvas関数
 */
inline void tml::scene::Node::ClearDrawCanvas(void)
{
	this->draw_canvas_2d_cont_ = nullptr;
	this->draw_canvas_3d_cont_ = nullptr;

	return;
}
