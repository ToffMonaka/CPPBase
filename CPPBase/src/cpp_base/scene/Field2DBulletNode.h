/**
 * @file
 * @brief Field2DBulletNodeヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "Node.h"


namespace cpp_base {
namespace scene {
/**
 * @brief Field2DBulletNodeDescクラス
 */
class Field2DBulletNodeDesc : public cpp_base::scene::NodeDesc
{
public:

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	Field2DBulletNodeDesc();
	virtual ~Field2DBulletNodeDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::Field2DBulletNodeDesc::Release(void)
{
	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief Field2DBulletNodeクラス
 */
class Field2DBulletNode : public cpp_base::scene::Node
{
public: Field2DBulletNode(const cpp_base::scene::Field2DBulletNode &) = delete;
public: cpp_base::scene::Field2DBulletNode &operator =(const cpp_base::scene::Field2DBulletNode &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	const cpp_base::scene::Field2DBulletNodeDesc *desc_;
	cpp_base::scene::Field2DNode *field_node_;
	tml::TIME_REAL update_time_;

public:
	tml::shared_ptr<tml::graphic::FigureModel2D> model;

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
	Field2DBulletNode();
	virtual ~Field2DBulletNode();

	virtual void Init(void);

	const cpp_base::scene::Field2DBulletNodeDesc *GetDesc(void) const;
};
}
}


/**
 * @brief GetDesc関数
 * @return desc (desc)
 */
inline const cpp_base::scene::Field2DBulletNodeDesc *cpp_base::scene::Field2DBulletNode::GetDesc(void) const
{
	return (this->desc_);
}
