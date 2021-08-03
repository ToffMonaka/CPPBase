/**
 * @file
 * @brief SelectSceneMainNodeヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "../constant/ConstantUtil_SOUND.h"
#include "Node.h"


namespace cpp_base {
namespace scene {
/**
 * @brief SelectSceneMainNodeDescクラス
 */
class SelectSceneMainNodeDesc : public cpp_base::scene::NodeDesc
{
public:

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	SelectSceneMainNodeDesc();
	virtual ~SelectSceneMainNodeDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::SelectSceneMainNodeDesc::Release(void)
{
	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief SelectSceneMainNodeクラス
 */
class SelectSceneMainNode : public cpp_base::scene::Node
{
public: SelectSceneMainNode(const cpp_base::scene::SelectSceneMainNode &) = delete;
public: cpp_base::scene::SelectSceneMainNode &operator =(const cpp_base::scene::SelectSceneMainNode &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	UINT progress_type_;

public:
	tml::shared_ptr<tml::graphic::Canvas2D> canvas_2d;
	tml::shared_ptr<tml::graphic::Model2D> bg_model;
	tml::shared_ptr<tml::sound::BGMSound> bgm_sound;
	tml::shared_ptr<tml::graphic::Font> stage_font;
	tml::shared_ptr<tml::graphic::Model2D> stage_model;
	tml::shared_ptr<tml::sound::SESound> stage_se_sound;

private:
	void Release(void);

protected:
	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);

public:
	SelectSceneMainNode();
	virtual ~SelectSceneMainNode();

	virtual void Init(void);
	INT Create(const cpp_base::scene::SelectSceneMainNodeDesc &);
};
}
}
