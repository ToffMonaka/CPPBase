/**
 * @file
 * @brief Sceneヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ManagerResource.h"


namespace tml {
namespace scene {
/**
 * @brief SceneDescクラス
 */
class SceneDesc : public tml::scene::ManagerResourceDesc
{
public:

protected:
	void Release(void);

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
	tml::scene::ManagerResourceDesc::Release();

	return;
}


namespace tml {
namespace scene {
/**
 * @brief Sceneクラス
 *
 * インターフェースパターン
 */
class Scene : public tml::scene::ManagerResource
{
public: Scene(const tml::scene::Scene &) = delete;
public: tml::scene::Scene &operator =(const tml::scene::Scene &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::ConstantUtil::SCENE::SCENE_TYPE type_;
	bool run_flg_;
	bool start_flg_;
	bool started_flg_;
	tml::shared_ptr<tml::scene::Node> header_node_;

protected:
	void Release(void);
	INT Create(const tml::scene::SceneDesc &, const tml::ConstantUtil::SCENE::SCENE_TYPE);

public:
	Scene();
	virtual ~Scene();

	virtual void Init(void);

	INT Start(void);
	void End(void);
	void Update(void);

	virtual INT OnStart(void) = 0;
	virtual void OnEnd(void) = 0;
	virtual void OnUpdate(void) = 0;

	tml::ConstantUtil::SCENE::SCENE_TYPE GetType(void) const;
	bool GetRunFlag(void) const;
	void SetRunFlag(const bool);
	bool GetStartFlag(void) const;
	void SetStartFlag(const bool);
	bool IsStarted(void) const;
	const tml::shared_ptr<tml::scene::Node> &GetHeaderNode(void);
};
}
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
 * @return res_flg (result_flag)<br>
 * false=非開始済み,true=開始済み
 */
inline bool tml::scene::Scene::IsStarted(void) const
{
	return (this->started_flg_);
}


/**
 * @brief GetHeaderNode関数
 * @return header_node (header_node)
 */
inline const tml::shared_ptr<tml::scene::Node> &tml::scene::Scene::GetHeaderNode(void)
{
	return (this->header_node_);
}
