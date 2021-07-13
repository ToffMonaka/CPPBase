/**
 * @file
 * @brief SelectSceneNodeヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "BaseNode.h"


namespace cpp_base {
namespace scene {
/**
 * @brief SelectSceneNodeDescクラス
 */
class SelectSceneNodeDesc : public cpp_base::scene::BaseNodeDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	SelectSceneNodeDesc();
	virtual ~SelectSceneNodeDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::SelectSceneNodeDesc::Release(void)
{
	cpp_base::scene::BaseNodeDesc::Release();

	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief SelectSceneNodeクラス
 */
class SelectSceneNode : public cpp_base::scene::BaseNode
{
public: SelectSceneNode(const cpp_base::scene::SelectSceneNode &) = delete;
public: cpp_base::scene::SelectSceneNode &operator =(const cpp_base::scene::SelectSceneNode &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

public:
	tml::shared_ptr<tml::graphic::Canvas2D> canvas_2d;
	tml::shared_ptr<tml::graphic::Model2D> bg_model;
	tml::shared_ptr<tml::graphic::Font> stage_font;
	tml::shared_ptr<tml::graphic::Model2D> stage_model;

protected:
	void Release(void);

public:
	SelectSceneNode();
	virtual ~SelectSceneNode();

	virtual void Init(void);
	INT Create(const cpp_base::scene::SelectSceneNodeDesc &);

	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);
};
}
}
