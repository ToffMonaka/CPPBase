/**
 * @file
 * @brief InitSceneヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "BaseScene.h"


namespace cpp_base {
namespace scene {
/**
 * @brief InitSceneDescクラス
 */
class InitSceneDesc : public cpp_base::scene::BaseSceneDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	InitSceneDesc();
	virtual ~InitSceneDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::InitSceneDesc::Release(void)
{
	cpp_base::scene::BaseSceneDesc::Release();

	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief InitSceneクラス
 */
class InitScene : public cpp_base::scene::BaseScene
{
public: InitScene(const cpp_base::scene::InitScene &) = delete;
public: cpp_base::scene::InitScene &operator =(const cpp_base::scene::InitScene &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

protected:
	void Release(void);

public:
	InitScene();
	virtual ~InitScene();

	virtual void Init(void);
	INT Create(const cpp_base::scene::InitSceneDesc &);

	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);
};
}
}
