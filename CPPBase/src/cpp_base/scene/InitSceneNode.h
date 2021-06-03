/**
 * @file
 * @brief InitSceneNodeヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "BaseNode.h"


namespace cpp_base {
namespace scene {
/**
 * @brief InitSceneNodeDescクラス
 */
class InitSceneNodeDesc : public cpp_base::scene::BaseNodeDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	InitSceneNodeDesc();
	virtual ~InitSceneNodeDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::InitSceneNodeDesc::Release(void)
{
	cpp_base::scene::BaseNodeDesc::Release();

	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief InitSceneNodeクラス
 */
class InitSceneNode : public cpp_base::scene::BaseNode
{
public: InitSceneNode(const cpp_base::scene::InitSceneNode &) = delete;
public: cpp_base::scene::InitSceneNode &operator =(const cpp_base::scene::InitSceneNode &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	tml::shared_ptr<tml::graphic::Camera> camera_;
	tml::shared_ptr<tml::graphic::Object2DModel> bg_model_;
	tml::TIME_REAL wait_update_time_;
	tml::shared_ptr<tml::graphic::Object2DModel> wait_model_;
	tml::shared_ptr<tml::graphic::Font> wait_font_;

protected:
	void Release(void);

public:
	InitSceneNode();
	virtual ~InitSceneNode();

	virtual void Init(void);
	INT Create(const cpp_base::scene::InitSceneNodeDesc &);

	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);
};
}
}
