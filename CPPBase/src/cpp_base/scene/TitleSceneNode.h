/**
 * @file
 * @brief TitleSceneNodeヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "../constant/ConstantUtil_SOUND.h"
#include "BaseNode.h"


namespace cpp_base {
namespace scene {
/**
 * @brief TitleSceneNodeDescクラス
 */
class TitleSceneNodeDesc : public cpp_base::scene::BaseNodeDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	TitleSceneNodeDesc();
	virtual ~TitleSceneNodeDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::TitleSceneNodeDesc::Release(void)
{
	cpp_base::scene::BaseNodeDesc::Release();

	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief TitleSceneNodeクラス
 */
class TitleSceneNode : public cpp_base::scene::BaseNode
{
public: TitleSceneNode(const cpp_base::scene::TitleSceneNode &) = delete;
public: cpp_base::scene::TitleSceneNode &operator =(const cpp_base::scene::TitleSceneNode &) = delete;
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
	TitleSceneNode();
	virtual ~TitleSceneNode();

	virtual void Init(void);
	INT Create(const cpp_base::scene::TitleSceneNodeDesc &);

	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);
};
}
}
