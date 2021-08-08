/**
 * @file
 * @brief SceneEventヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../memory/MemoryUtil.h"
#include "ManagerEvent.h"


namespace tml {
namespace scene {
/**
 * @brief SceneEventDataクラス
 */
class SceneEventData
{
public:
	tml::ConstantUtil::SCENE::SCENE_EVENT_DATA_TYPE type;
	tml::shared_ptr<tml::scene::Scene> scene;

private:
	void Release(void);

public:
	SceneEventData();
	virtual ~SceneEventData();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::scene::SceneEventData::Release(void)
{
	return;
}


namespace tml {
namespace scene {
/**
 * @brief SceneEventDescクラス
 */
class SceneEventDesc : public tml::scene::ManagerEventDesc
{
public:
	tml::scene::SceneEventData data;

private:
	void Release(void);

public:
	SceneEventDesc();
	virtual ~SceneEventDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::scene::SceneEventDesc::Release(void)
{
	return;
}


namespace tml {
namespace scene {
/**
 * @brief SceneEventクラス
 */
class SceneEvent : public tml::scene::ManagerEvent
{
public: SceneEvent(const tml::scene::SceneEvent &) = delete;
public: tml::scene::SceneEvent &operator =(const tml::scene::SceneEvent &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT EVENT_MAIN_INDEX = static_cast<UINT>(tml::ConstantUtil::SCENE::EVENT_TYPE::SCENE);
	static const UINT EVENT_SUB_INDEX = static_cast<UINT>(tml::ConstantUtil::SCENE::SCENE_EVENT_TYPE::BASE);

private:
	tml::ConstantUtil::SCENE::SCENE_EVENT_TYPE type_;

public:
	tml::scene::SceneEventData data;

private:
	void Release(void);

public:
	SceneEvent();
	virtual ~SceneEvent();

	virtual void Init(void);
	INT Create(const tml::scene::SceneEventDesc &);

	tml::ConstantUtil::SCENE::SCENE_EVENT_TYPE GetType(void) const;
};
}
}


/**
 * @brief Release関数
 */
inline void tml::scene::SceneEvent::Release(void)
{
	return;
}


/**
 * @brief GetType関数
 * @return type (type)
 */
inline tml::ConstantUtil::SCENE::SCENE_EVENT_TYPE tml::scene::SceneEvent::GetType(void) const
{
	return (this->type_);
}
