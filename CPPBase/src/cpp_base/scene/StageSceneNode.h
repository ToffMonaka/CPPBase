/**
 * @file
 * @brief StageSceneNodeヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "BaseNode.h"


namespace cpp_base {
namespace scene {
/**
 * @brief StageSceneNodeDescクラス
 */
class StageSceneNodeDesc : public cpp_base::scene::BaseNodeDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	StageSceneNodeDesc();
	virtual ~StageSceneNodeDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::StageSceneNodeDesc::Release(void)
{
	cpp_base::scene::BaseNodeDesc::Release();

	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief StageSceneNodeクラス
 */
class StageSceneNode : public cpp_base::scene::BaseNode
{
public: StageSceneNode(const cpp_base::scene::StageSceneNode &) = delete;
public: cpp_base::scene::StageSceneNode &operator =(const cpp_base::scene::StageSceneNode &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

public:
	tml::shared_ptr<tml::graphic::Canvas2D> canvas_2d;
	tml::shared_ptr<tml::graphic::Model2D> bg_model;
	tml::shared_ptr<tml::graphic::Font> name_font;
	tml::shared_ptr<tml::graphic::Model2D> name_model;

protected:
	void Release(void);

public:
	StageSceneNode();
	virtual ~StageSceneNode();

	virtual void Init(void);
	INT Create(const cpp_base::scene::StageSceneNodeDesc &);

	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);
};
}
}
