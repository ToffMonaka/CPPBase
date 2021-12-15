/**
 * @file
 * @brief Field2DPlayerNodeヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "Node.h"


namespace cpp_base {
namespace scene {
/**
 * @brief Field2DPlayerNodeDescクラス
 */
class Field2DPlayerNodeDesc : public cpp_base::scene::NodeDesc
{
public:

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	Field2DPlayerNodeDesc();
	virtual ~Field2DPlayerNodeDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::Field2DPlayerNodeDesc::Release(void)
{
	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief Field2DPlayerNodeクラス
 */
class Field2DPlayerNode : public cpp_base::scene::Node
{
public: Field2DPlayerNode(const cpp_base::scene::Field2DPlayerNode &) = delete;
public: cpp_base::scene::Field2DPlayerNode &operator =(const cpp_base::scene::Field2DPlayerNode &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	cpp_base::scene::Field2DNode *field_node_;
	tml::TIME_REAL attack_cool_time_;

public:
	tml::shared_ptr<tml::graphic::FigureModel2D> model;
	tml::shared_ptr<tml::graphic::FigureModel2D> shadow_model;

private:
	void Release(void);

protected:
	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);

public:
	Field2DPlayerNode();
	virtual ~Field2DPlayerNode();

	virtual void Init(void);
	INT Create(const cpp_base::scene::Field2DPlayerNodeDesc &);

	void Move(const tml::XMFLOAT2EX &);
	void Attack(const tml::XMFLOAT2EX &);
};
}
}
