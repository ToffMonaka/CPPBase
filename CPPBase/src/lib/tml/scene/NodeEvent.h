/**
 * @file
 * @brief NodeEventヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../memory/MemoryUtil.h"
#include "ManagerEvent.h"


namespace tml {
namespace scene {
/**
 * @brief NodeEventDataクラス
 */
class NodeEventData
{
public:
	tml::ConstantUtil::SCENE::NODE_EVENT_DATA_TYPE type;
	tml::shared_ptr<tml::scene::Node> parent_node;
	tml::shared_ptr<tml::scene::Node> child_node;

private:
	void Release(void);

public:
	NodeEventData();
	virtual ~NodeEventData();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::scene::NodeEventData::Release(void)
{
	return;
}


namespace tml {
namespace scene {
/**
 * @brief NodeEventDescクラス
 */
class NodeEventDesc : public tml::scene::ManagerEventDesc
{
public:
	tml::scene::NodeEventData data;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	NodeEventDesc();
	virtual ~NodeEventDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::scene::NodeEventDesc::Release(void)
{
	return;
}


namespace tml {
namespace scene {
/**
 * @brief NodeEventクラス
 */
class NodeEvent : public tml::scene::ManagerEvent
{
public: NodeEvent(const tml::scene::NodeEvent &) = delete;
public: tml::scene::NodeEvent &operator =(const tml::scene::NodeEvent &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT EVENT_MAIN_INDEX = static_cast<UINT>(tml::ConstantUtil::SCENE::EVENT_TYPE::NODE);
	static const UINT EVENT_SUB_INDEX = static_cast<UINT>(tml::ConstantUtil::SCENE::NODE_EVENT_TYPE::BASE);

private:
	tml::ConstantUtil::SCENE::NODE_EVENT_TYPE type_;

public:
	tml::scene::NodeEventData data;

private:
	void Release(void);

public:
	NodeEvent();
	virtual ~NodeEvent();

	virtual void Init(void);
	INT Create(const tml::scene::NodeEventDesc &);

	tml::ConstantUtil::SCENE::NODE_EVENT_TYPE GetType(void) const;
};
}
}


/**
 * @brief Release関数
 */
inline void tml::scene::NodeEvent::Release(void)
{
	return;
}


/**
 * @brief GetType関数
 * @return type (type)
 */
inline tml::ConstantUtil::SCENE::NODE_EVENT_TYPE tml::scene::NodeEvent::GetType(void) const
{
	return (this->type_);
}
