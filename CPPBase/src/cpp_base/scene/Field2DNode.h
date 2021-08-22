/**
 * @file
 * @brief Field2DNodeヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "Node.h"


namespace cpp_base {
namespace scene {
/**
 * @brief Field2DNodeDescクラス
 */
class Field2DNodeDesc : public cpp_base::scene::NodeDesc
{
public:

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	Field2DNodeDesc();
	virtual ~Field2DNodeDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::Field2DNodeDesc::Release(void)
{
	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief Field2DNodeクラス
 */
class Field2DNode : public cpp_base::scene::Node
{
public: Field2DNode(const cpp_base::scene::Field2DNode &) = delete;
public: cpp_base::scene::Field2DNode &operator =(const cpp_base::scene::Field2DNode &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	tml::shared_ptr<tml::graphic::Canvas2D> canvas_2d;
	tml::shared_ptr<tml::graphic::Model2D> ground_model;
	tml::shared_ptr<tml::graphic::Model2D> player_model;
	tml::shared_ptr<tml::graphic::Model2D> mob_model;
	tml::shared_ptr<tml::scene::Node> ground_layout_node;
	tml::shared_ptr<tml::scene::Node> player_layout_node;
	tml::shared_ptr<tml::scene::Node> mob_layout_node;

private:
	void Release(void);

protected:
	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);

public:
	Field2DNode();
	virtual ~Field2DNode();

	virtual void Init(void);
	INT Create(const cpp_base::scene::Field2DNodeDesc &);
};
}
}
