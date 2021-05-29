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
	tml::shared_ptr<tml::scene::Node> header_node_;
	bool started_flg_;

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
	const tml::shared_ptr<tml::scene::Node> &GetHeaderNode(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::scene::Scene::Release(void)
{
	tml::scene::ManagerResource::Release();

	return;
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
 * @brief GetHeaderNode関数
 * @return header_node (header_node)
 */
inline const tml::shared_ptr<tml::scene::Node> &tml::scene::Scene::GetHeaderNode(void)
{
	return (this->header_node_);
}
