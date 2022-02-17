/**
 * @file
 * @brief Test2DStageNodeヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "Node.h"


namespace cpp_base {
namespace scene {
/**
 * @brief Test2DStageNodeDescクラス
 */
class Test2DStageNodeDesc : public cpp_base::scene::NodeDesc
{
public:

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	Test2DStageNodeDesc();
	virtual ~Test2DStageNodeDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void cpp_base::scene::Test2DStageNodeDesc::Release(void)
{
	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief Test2DStageNodeクラス
 */
class Test2DStageNode : public cpp_base::scene::Node
{
public: Test2DStageNode(const cpp_base::scene::Test2DStageNode &) = delete;
public: cpp_base::scene::Test2DStageNode &operator =(const cpp_base::scene::Test2DStageNode &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	tml::shared_ptr<tml::scene::Node> field_layout_node_;

public:

private:
	void Release(void);

protected:
	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);

public:
	Test2DStageNode();
	virtual ~Test2DStageNode();

	virtual void Init(void);
	INT Create(const cpp_base::scene::Test2DStageNodeDesc &);

	const tml::shared_ptr<tml::scene::Node> &GetFieldNode(void);
	INT AddFieldNode(const tml::shared_ptr<tml::scene::Node> &, const bool deferred_flg = true);
	void RemoveFieldNode(const bool deferred_flg = true);
};
}
}


/**
 * @brief GetFieldNode関数
 * @return field_node (field_node)<br>
 * nullptr=失敗
 */
inline const tml::shared_ptr<tml::scene::Node> &cpp_base::scene::Test2DStageNode::GetFieldNode(void)
{
	return (this->field_layout_node_->GetChildNode());
}
