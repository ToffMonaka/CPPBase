/**
 * @file
 * @brief Field2DMobNodeヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "Node.h"


namespace cpp_base {
namespace scene {
/**
 * @brief Field2DMobNodeDescクラス
 */
class Field2DMobNodeDesc : public cpp_base::scene::NodeDesc
{
public:

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	Field2DMobNodeDesc();
	virtual ~Field2DMobNodeDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::Field2DMobNodeDesc::Release(void)
{
	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief Field2DMobNodeクラス
 */
class Field2DMobNode : public cpp_base::scene::Node
{
public: Field2DMobNode(const cpp_base::scene::Field2DMobNode &) = delete;
public: cpp_base::scene::Field2DMobNode &operator =(const cpp_base::scene::Field2DMobNode &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	const cpp_base::scene::Field2DMobNodeDesc *desc_;
	cpp_base::scene::Field2DNode *field_node_;

public:
	tml::shared_ptr<tml::graphic::FigureModel2D> model;
	tml::shared_ptr<tml::graphic::FigureModel2D> shadow_model;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);

public:
	Field2DMobNode();
	virtual ~Field2DMobNode();

	virtual void Init(void);

	const cpp_base::scene::Field2DMobNodeDesc *GetDesc(void) const;
};
}
}


/**
 * @brief GetDesc関数
 * @return desc (desc)
 */
inline const cpp_base::scene::Field2DMobNodeDesc *cpp_base::scene::Field2DMobNode::GetDesc(void) const
{
	return (this->desc_);
}
