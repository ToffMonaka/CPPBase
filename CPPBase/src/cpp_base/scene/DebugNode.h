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
	const cpp_base::scene::DebugNodeDesc *desc_;
	tml::TIME_REAL update_time_;
	tml::TIME_REAL cpu_elapsed_time_;
	UINT cpu_elapsed_cnt_;
	tml::TIME_REAL gpu_elapsed_time_;
	UINT gpu_elapsed_cnt_;

public:
	tml::shared_ptr<tml::graphic::Font> font;
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
	DebugNode();
	virtual ~DebugNode();

	virtual void Init(void);

	const cpp_base::scene::DebugNodeDesc *GetDesc(void) const;
};
}
}


/**
 * @brief GetDesc関数
 * @return desc (desc)
 */
inline const cpp_base::scene::DebugNodeDesc *cpp_base::scene::DebugNode::GetDesc(void) const
{
	return (this->desc_);
}
