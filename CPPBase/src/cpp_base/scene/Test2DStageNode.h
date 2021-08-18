/**
 * @file
 * @brief Test2DStageNodeヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "Node.h"


namespace cpp_base {
namespace scene {
/**
 * @brief Test2DStageNodeDescクラス
 */
class Test2DStageNodeDesc : public cpp_base::scene::NodeDesc
{
public:

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	Test2DStageNodeDesc();
	virtual ~Test2DStageNodeDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::Test2DStageNodeDesc::Release(void)
{
	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief Test2DStageNodeクラス
 */
class Test2DStageNode : public cpp_base::scene::Node
{
public: Test2DStageNode(const cpp_base::scene::Test2DStageNode &) = delete;
public: cpp_base::scene::Test2DStageNode &operator =(const cpp_base::scene::Test2DStageNode &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	tml::shared_ptr<tml::graphic::Canvas2D> canvas_2d;
	tml::shared_ptr<tml::graphic::Model2D> ground_model;
	tml::shared_ptr<tml::graphic::Model2D> player_character_model;
	tml::shared_ptr<tml::scene::Node> ground_layout_node;
	tml::shared_ptr<tml::scene::Node> player_character_layout_node;

private:
	void Release(void);

protected:
	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);

public:
	Test2DStageNode();
	virtual ~Test2DStageNode();

	virtual void Init(void);
	INT Create(const cpp_base::scene::Test2DStageNodeDesc &);
};
}
}
