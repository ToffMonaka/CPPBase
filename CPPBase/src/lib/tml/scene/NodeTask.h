/**
 * @file
 * @brief NodeTaskヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ManagerTask.h"


namespace tml {
namespace scene {
/**
 * @brief NodeTaskDescクラス
 */
class NodeTaskDesc : public tml::scene::ManagerTaskDesc
{
public:
	tml::ConstantUtil::SCENE::NODE_TASK_RUN_TYPE run_type;
	tml::shared_ptr<tml::scene::Node> node;
	tml::shared_ptr<tml::scene::Node> child_node;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	NodeTaskDesc();
	virtual ~NodeTaskDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::scene::NodeTaskDesc::Release(void)
{
	return;
}


namespace tml {
namespace scene {
/**
 * @brief NodeTaskクラス
 */
class NodeTask : public tml::scene::ManagerTask
{
public: NodeTask(const tml::scene::NodeTask &) = delete;
public: tml::scene::NodeTask &operator =(const tml::scene::NodeTask &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT TASK_TYPE = static_cast<UINT>(tml::ConstantUtil::SCENE::TASK_TYPE::NODE);

private:
	tml::ConstantUtil::SCENE::NODE_TASK_RUN_TYPE run_type_;
	tml::shared_ptr<tml::scene::Node> node_;
	tml::shared_ptr<tml::scene::Node> child_node_;

private:
	void Release(void);

protected:
	virtual void OnRun(void);

public:
	NodeTask();
	virtual ~NodeTask();

	virtual void Init(void);
	INT Create(const tml::scene::NodeTaskDesc &);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::scene::NodeTask::Release(void)
{
	return;
}
