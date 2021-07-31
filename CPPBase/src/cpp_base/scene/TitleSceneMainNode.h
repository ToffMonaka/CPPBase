/**
 * @file
 * @brief TitleSceneMainNodeヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "../constant/ConstantUtil_SOUND.h"
#include "Node.h"


namespace cpp_base {
namespace scene {
/**
 * @brief TitleSceneMainNodeDescクラス
 */
class TitleSceneMainNodeDesc : public cpp_base::scene::NodeDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	TitleSceneMainNodeDesc();
	virtual ~TitleSceneMainNodeDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::TitleSceneMainNodeDesc::Release(void)
{
	cpp_base::scene::NodeDesc::Release();

	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief TitleSceneMainNodeクラス
 */
class TitleSceneMainNode : public cpp_base::scene::Node
{
public: TitleSceneMainNode(const cpp_base::scene::TitleSceneMainNode &) = delete;
public: cpp_base::scene::TitleSceneMainNode &operator =(const cpp_base::scene::TitleSceneMainNode &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	UINT progress_type_;

public:
	tml::shared_ptr<tml::graphic::Canvas2D> canvas_2d;
	tml::shared_ptr<tml::graphic::Model2D> bg_model;
	tml::shared_ptr<tml::sound::BGMSound> bgm_sound;
	tml::shared_ptr<tml::graphic::Model2D> logo_model;
	tml::shared_ptr<tml::graphic::Font> start_font;
	tml::shared_ptr<tml::graphic::Model2D> start_model;
	tml::shared_ptr<tml::sound::SESound> start_se_sound;
	tml::shared_ptr<tml::graphic::Font> footer_font;
	tml::shared_ptr<tml::graphic::Model2D> footer_model;

protected:
	void Release(void);

public:
	TitleSceneMainNode();
	virtual ~TitleSceneMainNode();

	virtual void Init(void);
	INT Create(const cpp_base::scene::TitleSceneMainNodeDesc &);

	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);
};
}
}
