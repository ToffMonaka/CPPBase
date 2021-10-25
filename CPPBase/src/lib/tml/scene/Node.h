/**
 * @file
 * @brief Node�w�b�_�[�t�@�C��
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
class Model2D;
}
namespace sound {
class Manager;
}
}


namespace tml {
namespace scene {
/**
 * @brief NodeDesc�N���X
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
 * @brief Release�֐�
 */
inline void tml::scene::NodeDesc::Release(void)
{
	return;
}


namespace tml {
namespace scene {
/**
 * @brief Node�N���X
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
	tml::shared_ptr<tml::graphic::Canvas2D> canvas_2d_;
	std::vector<tml::shared_ptr<tml::graphic::Model2D>> model_2d_cont_;
	tml::shared_ptr<tml::graphic::Model2D> empty_model_2d_;
	tml::graphic::Canvas2D *draw_canvas_2d_;

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
	const tml::shared_ptr<tml::graphic::Canvas2D> &GetCanvas2D(void);
	void SetCanvas2D(const tml::shared_ptr<tml::graphic::Canvas2D> &);
	UINT GetModel2DCount(void) const;
	const tml::shared_ptr<tml::graphic::Model2D> &GetModel2D(const UINT);
	const tml::shared_ptr<tml::graphic::Model2D> &GetModel2DFast(const UINT);
	void SetModel2D(const UINT, const tml::shared_ptr<tml::graphic::Model2D> &);
	tml::graphic::Canvas2D *GetDrawCanvas2D(void);
	void SetDrawCanvas2D(tml::graphic::Canvas2D *);
};
}
}


/**
 * @brief GetInputManager�֐�
 * @return input_mgr (input_manager)
 */
inline tml::input::Manager *tml::scene::Node::GetInputManager(void)
{
	return (this->input_mgr_);
}


/**
 * @brief GetGraphicManager�֐�
 * @return graphic_mgr (graphic_manager)
 */
inline tml::graphic::Manager *tml::scene::Node::GetGraphicManager(void)
{
	return (this->graphic_mgr_);
}


/**
 * @brief GetSoundManager�֐�
 * @return sound_mgr (sound_manager)
 */
inline tml::sound::Manager *tml::scene::Node::GetSoundManager(void)
{
	return (this->sound_mgr_);
}


/**
 * @brief GetName�֐�
 * @return name (name)
 */
inline const std::wstring &tml::scene::Node::GetName(void) const
{
	return (this->name_);
}


/**
 * @brief SetName�֐�
 * @param name (name)
 */
inline void tml::scene::Node::SetName(const WCHAR *name)
{
	this->name_ = name;

	return;
}


/**
 * @brief GetType�֐�
 * @return type (type)
 */
inline tml::ConstantUtil::SCENE::NODE_TYPE tml::scene::Node::GetType(void) const
{
	return (this->type_);
}


/**
 * @brief GetRunFlag�֐�
 * @return run_flg (run_flag)
 */
inline bool tml::scene::Node::GetRunFlag(void) const
{
	return (this->run_flg_);
}


/**
 * @brief GetStartFlag�֐�
 * @return start_flg (start_flag)
 */
inline bool tml::scene::Node::GetStartFlag(void) const
{
	return (this->start_flg_);
}


/**
 * @brief SetStartFlag�֐�
 * @param start_flg (start_flag)
 */
inline void tml::scene::Node::SetStartFlag(const bool start_flg)
{
	this->start_flg_ = start_flg;

	return;
}


/**
 * @brief IsStarted�֐�
 * @return result_flg (result_flag)<br>
 * false=��J�n�ς�,true=�J�n�ς�
 */
inline bool tml::scene::Node::IsStarted(void) const
{
	return (this->started_flg_);
}


/**
 * @brief GetParentNode�֐�
 * @return parent_node (parent_node)
 */
inline tml::scene::Node *tml::scene::Node::GetParentNode(void)
{
	return (this->parent_node_);
}


/**
 * @brief GetChildNodeContainer�֐�
 * @return child_node_container (child_node_container)
 */
inline const std::list<tml::shared_ptr<tml::scene::Node>> &tml::scene::Node::GetChildNodeContainer(void)
{
	return (this->child_node_cont_);
}


/**
 * @brief GetChildNode�֐�
 * @param child_node_name (child_node_name)
 * @return child_node (child_node)<br>
 * nullptr=���s
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
 * @brief GetCanvas2D�֐�
 * @return canvas_2d (canvas_2d)
 */
inline const tml::shared_ptr<tml::graphic::Canvas2D> &tml::scene::Node::GetCanvas2D(void)
{
	return (this->canvas_2d_);
}


/**
 * @brief GetModel2DCount�֐�
 * @return model_2d_cnt (model_2d_count)
 */
inline UINT tml::scene::Node::GetModel2DCount(void) const
{
	return (this->model_2d_cont_.size());
}


/**
 * @brief GetModel2D�֐�
 * @param index (index)
 * @return model_2d (model_2d)<br>
 * nullptr=���s
 */
inline const tml::shared_ptr<tml::graphic::Model2D> &tml::scene::Node::GetModel2D(const UINT index)
{
	if (index >= this->model_2d_cont_.size()) {
		return (this->empty_model_2d_);
	}

	return (this->model_2d_cont_[index]);
}


/**
 * @brief GetModel2DFast�֐�
 * @param index (index)
 * @return model_2d (model_2d)<br>
 * nullptr=���s
 */
inline const tml::shared_ptr<tml::graphic::Model2D> &tml::scene::Node::GetModel2DFast(const UINT index)
{
	return (this->model_2d_cont_[index]);
}


/**
 * @brief GetDrawCanvas2D�֐�
 * @return draw_canvas_2d (draw_canvas_2d)
 */
inline tml::graphic::Canvas2D *tml::scene::Node::GetDrawCanvas2D(void)
{
	return (this->draw_canvas_2d_);
}


/**
 * @brief SetDrawCanvas2D�֐�
 * @param draw_canvas_2d (draw_canvas_2d)
 */
inline void tml::scene::Node::SetDrawCanvas2D(tml::graphic::Canvas2D *draw_canvas_2d)
{
	this->draw_canvas_2d_ = draw_canvas_2d;

	return;
}
