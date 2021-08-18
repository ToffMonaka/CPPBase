/**
 * @file
 * @brief Nodeヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ManagerResource.h"


namespace tml {
namespace input {
class Manager;
}
namespace graphic {
class Manager;
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

private:
	void Release(void);

	const tml::shared_ptr<tml::scene::Node> &GetChildNodeRecursivePart(tml::shared_ptr<tml::scene::Node> &, const std::list<tml::shared_ptr<tml::scene::Node>> &, const WCHAR *);

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
	const tml::shared_ptr<tml::scene::Node> &GetChildNode(tml::shared_ptr<tml::scene::Node> &, const WCHAR *);
	INT AddChildNode(const tml::shared_ptr<tml::scene::Node> &, const bool event_flg = true);
	void RemoveChildNode(const bool event_flg = true);
	void RemoveChildNode(const tml::shared_ptr<tml::scene::Node> &, const bool event_flg = true);
	void RemoveChildNodeFromParentNode(const bool event_flg = true);
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
 * @param dst_child_node (dst_child_node)
 * @param child_node_name (child_node_name)
 * @return dst_child_node (dst_child_node)
 */
inline const tml::shared_ptr<tml::scene::Node> &tml::scene::Node::GetChildNode(tml::shared_ptr<tml::scene::Node> &dst_child_node, const WCHAR *child_node_name)
{
	dst_child_node.reset();

	if ((child_node_name == nullptr)
	|| (child_node_name[0] == 0)) {
		return (dst_child_node);
	}

	return (this->GetChildNodeRecursivePart(dst_child_node, this->child_node_cont_, child_node_name));
}
