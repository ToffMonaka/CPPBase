/**
 * @file
 * @brief BaseSceneヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SCENE.h"
#include "../../lib/tml/scene/BaseScene.h"


namespace cpp_base {
namespace scene {
/**
 * @brief BaseSceneDescクラス
 */
class BaseSceneDesc : public tml::scene::BaseSceneDesc
{
private:
	cpp_base::scene::Manager *mgr_;

public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	BaseSceneDesc();
	virtual ~BaseSceneDesc();

	virtual void Init(void);

	cpp_base::scene::Manager *GetManager(void) const;
	void SetManager(cpp_base::scene::Manager *);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::BaseSceneDesc::Release(void)
{
	tml::scene::BaseSceneDesc::Release();

	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline cpp_base::scene::Manager *cpp_base::scene::BaseSceneDesc::GetManager(void) const
{
	return (this->mgr_);
}


namespace cpp_base {
namespace scene {
/**
 * @brief BaseSceneクラス
 */
class BaseScene : public tml::scene::BaseScene
{
public: BaseScene(const cpp_base::scene::BaseScene &) = delete;
public: cpp_base::scene::BaseScene &operator =(const cpp_base::scene::BaseScene &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	cpp_base::scene::Manager *mgr_;

protected:
	void Release(void);

public:
	BaseScene();
	virtual ~BaseScene();

	virtual void Init(void);
	INT Create(const cpp_base::scene::BaseSceneDesc &);

	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);

	cpp_base::scene::Manager *GetManager(void);
};
}
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline cpp_base::scene::Manager *cpp_base::scene::BaseScene::GetManager(void)
{
	return (this->mgr_);
}
