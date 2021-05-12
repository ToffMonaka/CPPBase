/**
 * @file
 * @brief TitleSceneヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "../constant/ConstantUtil_SOUND.h"
#include "BaseScene.h"


namespace cpp_base {
namespace scene {
/**
 * @brief TitleSceneDescクラス
 */
class TitleSceneDesc : public cpp_base::scene::BaseSceneDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	TitleSceneDesc();
	virtual ~TitleSceneDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::TitleSceneDesc::Release(void)
{
	cpp_base::scene::BaseSceneDesc::Release();

	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief TitleSceneクラス
 */
class TitleScene : public cpp_base::scene::BaseScene
{
public: TitleScene(const cpp_base::scene::TitleScene &) = delete;
public: cpp_base::scene::TitleScene &operator =(const cpp_base::scene::TitleScene &) = delete;
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
	TitleScene();
	virtual ~TitleScene();

	virtual void Init(void);
	INT Create(const cpp_base::scene::TitleSceneDesc &);

	virtual INT Start(void);
	virtual void End(void);
	virtual void Update(void);
};
}
}
