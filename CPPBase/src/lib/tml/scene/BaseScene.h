/**
 * @file
 * @brief BaseSceneヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathPosition.h"
#include "Scene.h"


namespace tml {
namespace scene {
/**
 * @brief BaseSceneDescクラス
 */
class BaseSceneDesc : public tml::scene::SceneDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	BaseSceneDesc();
	virtual ~BaseSceneDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::scene::BaseSceneDesc::Release(void)
{
	tml::scene::SceneDesc::Release();

	return;
}


namespace tml {
namespace scene {
/**
 * @brief BaseSceneクラス
 */
class BaseScene : public tml::scene::Scene
{
public: BaseScene(const tml::scene::BaseScene &) = delete;
public: tml::scene::BaseScene &operator =(const tml::scene::BaseScene &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT RESOURCE_SUB_INDEX = static_cast<UINT>(tml::ConstantUtil::SCENE::SCENE_TYPE::BASE);

private:

protected:
	void Release(void);

public:
	BaseScene();
	virtual ~BaseScene();

	virtual void Init(void);
	INT Create(const tml::scene::BaseSceneDesc &);

	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);
};
}
}
