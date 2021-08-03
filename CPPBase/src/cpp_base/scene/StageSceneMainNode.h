/**
 * @file
 * @brief StageSceneMainNode�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "Node.h"


namespace cpp_base {
namespace scene {
/**
 * @brief StageSceneMainNodeDesc�N���X
 */
class StageSceneMainNodeDesc : public cpp_base::scene::NodeDesc
{
public:

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	StageSceneMainNodeDesc();
	virtual ~StageSceneMainNodeDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void cpp_base::scene::StageSceneMainNodeDesc::Release(void)
{
	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief StageSceneMainNode�N���X
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

private:
	void Release(void);

protected:
	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);

public:
	StageSceneMainNode();
	virtual ~StageSceneMainNode();

	virtual void Init(void);
	INT Create(const cpp_base::scene::StageSceneMainNodeDesc &);
};
}
}
