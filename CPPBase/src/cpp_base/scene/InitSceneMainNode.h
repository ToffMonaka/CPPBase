/**
 * @file
 * @brief InitSceneMainNodeヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "Node.h"


namespace cpp_base {
namespace scene {
/**
 * @brief InitSceneMainNodeDescクラス
 */
class InitSceneMainNodeDesc : public cpp_base::scene::NodeDesc
{
public:

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	InitSceneMainNodeDesc();
	virtual ~InitSceneMainNodeDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::InitSceneMainNodeDesc::Release(void)
{
	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief InitSceneMainNodeクラス
 */
class InitSceneMainNode : public cpp_base::scene::Node
{
public: InitSceneMainNode(const cpp_base::scene::InitSceneMainNode &) = delete;
public: cpp_base::scene::InitSceneMainNode &operator =(const cpp_base::scene::InitSceneMainNode &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	UINT progress_type_;

public:
	tml::shared_ptr<tml::graphic::Canvas2D> canvas_2d;
	tml::shared_ptr<tml::graphic::Model2D> bg_model;
	tml::TIME_REAL wait_update_time;
	tml::shared_ptr<tml::graphic::Font> wait_font;
	tml::shared_ptr<tml::graphic::Model2D> wait_model;

private:
	void Release(void);

protected:
	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);

public:
	InitSceneMainNode();
	virtual ~InitSceneMainNode();

	virtual void Init(void);
	INT Create(const cpp_base::scene::InitSceneMainNodeDesc &);
};
}
}
