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
	cpp_base::scene::Field2DNode *field_node_;
	tml::TIME_REAL update_time_;

public:
	tml::shared_ptr<tml::graphic::FigureModel2D> model;

private:
	void Release(void);

protected:
	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);

public:
	Field2DBulletNode();
	virtual ~Field2DBulletNode();

	virtual void Init(void);
	INT Create(const cpp_base::scene::Field2DBulletNodeDesc &);
};
}
}
