/**
 * @file
 * @brief SceneTaskヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ManagerTask.h"


namespace tml {
namespace scene {
/**
 * @brief SceneTaskDescクラス
 */
class SceneTaskDesc : public tml::scene::ManagerTaskDesc
{
public:
	tml::ConstantUtil::SCENE::SCENE_TASK_RUN_TYPE run_type;
	tml::shared_ptr<tml::scene::Scene> scene;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	SceneTaskDesc();
	virtual ~SceneTaskDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::scene::SceneTaskDesc::Release(void)
{
	return;
}


namespace tml {
namespace scene {
/**
 * @brief SceneTaskクラス
 */
class SceneTask : public tml::scene::ManagerTask
{
public: SceneTask(const tml::scene::SceneTask &) = delete;
public: tml::scene::SceneTask &operator =(const tml::scene::SceneTask &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT TASK_TYPE = static_cast<UINT>(tml::ConstantUtil::SCENE::TASK_TYPE::SCENE);

private:
	tml::ConstantUtil::SCENE::SCENE_TASK_RUN_TYPE run_type_;
	tml::shared_ptr<tml::scene::Scene> scene_;

private:
	void Release(void);

protected:
	virtual void OnRun(void);

public:
	SceneTask();
	virtual ~SceneTask();

	virtual void Init(void);
	INT Create(const tml::scene::SceneTaskDesc &);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::scene::SceneTask::Release(void)
{
	return;
}
