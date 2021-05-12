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
public:
	cpp_base::scene::Manager *manager2;

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	BaseSceneDesc();
	virtual ~BaseSceneDesc();

	virtual void Init(void);

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
	cpp_base::scene::Manager *mgr2_;

protected:
	void Release(void);

public:
	BaseScene();
	virtual ~BaseScene();

	virtual void Init(void);
	INT Create(const cpp_base::scene::BaseSceneDesc &);

	cpp_base::scene::Manager *GetManager(void);

	virtual INT Start(void);
	virtual void End(void);
	virtual void Update(void);
};
}
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline cpp_base::scene::Manager *cpp_base::scene::BaseScene::GetManager(void)
{
	return (this->mgr2_);
}
