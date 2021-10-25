/**
 * @file
 * @brief DebugNodeヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "Node.h"


namespace cpp_base {
namespace scene {
/**
 * @brief DebugNodeDescクラス
 */
class DebugNodeDesc : public cpp_base::scene::NodeDesc
{
public:

private:
	void Release(void);

protected:
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
	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief DebugNodeクラス
 */
class DebugNode : public cpp_base::scene::Node
{
public: DebugNode(const cpp_base::scene::DebugNode &) = delete;
public: cpp_base::scene::DebugNode &operator =(const cpp_base::scene::DebugNode &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

public:
	tml::TIME_REAL update_time;
	tml::shared_ptr<tml::graphic::Font> font;
	tml::shared_ptr<tml::graphic::FigureModel2D> model;

private:
	void Release(void);

protected:
	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);

public:
	DebugNode();
	virtual ~DebugNode();

	virtual void Init(void);
	INT Create(const cpp_base::scene::DebugNodeDesc &);
};
}
}
