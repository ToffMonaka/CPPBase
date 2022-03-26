/**
 * @file
 * @brief Field2DGroundNodeヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "Node.h"


namespace cpp_base {
namespace scene {
/**
 * @brief Field2DGroundNodeDescクラス
 */
class Field2DGroundNodeDesc : public cpp_base::scene::NodeDesc
{
public:

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	Field2DGroundNodeDesc();
	virtual ~Field2DGroundNodeDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::Field2DGroundNodeDesc::Release(void)
{
	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief Field2DGroundNodeクラス
 */
class Field2DGroundNode : public cpp_base::scene::Node
{
public: Field2DGroundNode(const cpp_base::scene::Field2DGroundNode &) = delete;
public: cpp_base::scene::Field2DGroundNode &operator =(const cpp_base::scene::Field2DGroundNode &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	const cpp_base::scene::Field2DGroundNodeDesc *desc_;
	cpp_base::scene::Field2DNode *field_node_;

public:
	tml::shared_ptr<tml::graphic::GroundModel2D> model;

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
	Field2DGroundNode();
	virtual ~Field2DGroundNode();

	virtual void Init(void);

	const cpp_base::scene::Field2DGroundNodeDesc *GetDesc(void) const;
};
}
}


/**
 * @brief GetDesc関数
 * @return desc (desc)
 */
inline const cpp_base::scene::Field2DGroundNodeDesc *cpp_base::scene::Field2DGroundNode::GetDesc(void) const
{
	return (this->desc_);
}
