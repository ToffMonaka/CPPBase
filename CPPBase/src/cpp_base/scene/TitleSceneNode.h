/**
 * @file
 * @brief TitleSceneNodeヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_INPUT.h"
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
	tml::shared_ptr<tml::graphic::Camera> camera_;
	tml::shared_ptr<tml::graphic::Object2DModel> bg_model_;
	tml::shared_ptr<tml::graphic::Object2DModel> logo_model_;
	tml::shared_ptr<tml::graphic::Object2DModel> start_model_;
	tml::shared_ptr<tml::graphic::Font> start_font_;
	tml::shared_ptr<tml::sound::SESound> start_se_sound_;
	tml::shared_ptr<tml::graphic::Object2DModel> footer_model_;
	tml::shared_ptr<tml::graphic::Font> footer_font_;
	tml::shared_ptr<tml::sound::BGMSound> bgm_sound_;

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
