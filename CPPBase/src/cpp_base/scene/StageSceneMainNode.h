/**
 * @file
 * @brief StageSceneMainNodeヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "BaseNode.h"


namespace cpp_base {
namespace scene {
/**
 * @brief StageSceneMainNodeDescクラス
 */
class StageSceneMainNodeDesc : public cpp_base::scene::BaseNodeDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	StageSceneMainNodeDesc();
	virtual ~StageSceneMainNodeDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::StageSceneMainNodeDesc::Release(void)
{
	cpp_base::scene::BaseNodeDesc::Release();

	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief StageSceneMainNodeクラス
 */
class StageSceneMainNode : public cpp_base::scene::BaseNode
{
public: StageSceneMainNode(const cpp_base::scene::StageSceneMainNode &) = delete;
public: cpp_base::scene::StageSceneMainNode &operator =(const cpp_base::scene::StageSceneMainNode &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	UINT progress_type_;

public:
	tml::shared_ptr<tml::graphic::Canvas2D> canvas_2d;
	tml::shared_ptr<tml::graphic::Model2D> bg_model;
	tml::shared_ptr<tml::graphic::Font> name_font;
	tml::shared_ptr<tml::graphic::Model2D> name_model;

protected:
	void Release(void);

public:
	StageSceneMainNode();
	virtual ~StageSceneMainNode();

	virtual void Init(void);
	INT Create(const cpp_base::scene::StageSceneMainNodeDesc &);

	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);
};
}
}
