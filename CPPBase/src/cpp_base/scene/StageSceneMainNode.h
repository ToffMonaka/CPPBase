/**
 * @file
 * @brief StageSceneMainNodeヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "Node.h"


namespace cpp_base {
namespace scene {
/**
 * @brief StageSceneMainNodeDescクラス
 */
class StageSceneMainNodeDesc : public cpp_base::scene::NodeDesc
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
	cpp_base::scene::NodeDesc::Release();

	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief StageSceneMainNodeクラス
 */
class StageSceneMainNode : public cpp_base::scene::Node
{
public: StageSceneMainNode(const cpp_base::scene::StageSceneMainNode &) = delete;
public: cpp_base::scene::StageSceneMainNode &operator =(const cpp_base::scene::StageSceneMainNode &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	UINT progress_type_;

public:
	tml::shared_ptr<tml::graphic::Canvas2D> canvas_2d;

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
