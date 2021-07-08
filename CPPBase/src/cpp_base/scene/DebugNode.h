/**
 * @file
 * @brief DebugNodeヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "BaseNode.h"


namespace cpp_base {
namespace scene {
/**
 * @brief DebugNodeDescクラス
 */
class DebugNodeDesc : public cpp_base::scene::BaseNodeDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	DebugNodeDesc();
	virtual ~DebugNodeDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::DebugNodeDesc::Release(void)
{
	cpp_base::scene::BaseNodeDesc::Release();

	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief DebugNodeクラス
 */
class DebugNode : public cpp_base::scene::BaseNode
{
public: DebugNode(const cpp_base::scene::DebugNode &) = delete;
public: cpp_base::scene::DebugNode &operator =(const cpp_base::scene::DebugNode &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

public:
	tml::shared_ptr<tml::graphic::Canvas2D> canvas_2d;
	tml::TIME_REAL update_time;
	tml::shared_ptr<tml::graphic::Font> font;
	tml::shared_ptr<tml::graphic::Model2D> model;

protected:
	void Release(void);

public:
	DebugNode();
	virtual ~DebugNode();

	virtual void Init(void);
	INT Create(const cpp_base::scene::DebugNodeDesc &);

	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);
};
}
}
