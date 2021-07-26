/**
 * @file
 * @brief Test2DStageNode�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "BaseNode.h"


namespace cpp_base {
namespace scene {
/**
 * @brief Test2DStageNodeDesc�N���X
 */
class Test2DStageNodeDesc : public cpp_base::scene::BaseNodeDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	Test2DStageNodeDesc();
	virtual ~Test2DStageNodeDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void cpp_base::scene::Test2DStageNodeDesc::Release(void)
{
	cpp_base::scene::BaseNodeDesc::Release();

	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief Test2DStageNode�N���X
 */
class Test2DStageNode : public cpp_base::scene::BaseNode
{
public: Test2DStageNode(const cpp_base::scene::Test2DStageNode &) = delete;
public: cpp_base::scene::Test2DStageNode &operator =(const cpp_base::scene::Test2DStageNode &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	tml::shared_ptr<tml::graphic::Canvas2D> canvas_2d;
	tml::shared_ptr<tml::graphic::Model2D> ground_model;
	tml::shared_ptr<tml::graphic::Model2D> pl_model;

protected:
	void Release(void);

public:
	Test2DStageNode();
	virtual ~Test2DStageNode();

	virtual void Init(void);
	INT Create(const cpp_base::scene::Test2DStageNodeDesc &);

	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);
};
}
}
