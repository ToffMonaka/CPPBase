/**
 * @file
 * @brief Field2DNode�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "Node.h"


namespace cpp_base {
namespace scene {
/**
 * @brief Field2DNodeDesc�N���X
 */
class Field2DNodeDesc : public cpp_base::scene::NodeDesc
{
public:

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	Field2DNodeDesc();
	virtual ~Field2DNodeDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void cpp_base::scene::Field2DNodeDesc::Release(void)
{
	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief Field2DNode�N���X
 */
class Field2DNode : public cpp_base::scene::Node
{
public: Field2DNode(const cpp_base::scene::Field2DNode &) = delete;
public: cpp_base::scene::Field2DNode &operator =(const cpp_base::scene::Field2DNode &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	tml::shared_ptr<tml::scene::Node> ground_layout_node_;
	tml::shared_ptr<tml::scene::Node> pl_layout_node_;
	tml::shared_ptr<tml::scene::Node> mob_layout_node_;
	tml::shared_ptr<tml::scene::Node> bullet_layout_node_;

public:

private:
	void Release(void);

protected:
	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);

public:
	Field2DNode();
	virtual ~Field2DNode();

	virtual void Init(void);
	INT Create(const cpp_base::scene::Field2DNodeDesc &);
	const tml::shared_ptr<tml::scene::Node> &GetGroundNode(void);
	INT AddGroundNode(const tml::shared_ptr<tml::scene::Node> &, const bool event_flg = true);
	void RemoveGroundNode(const bool event_flg = true);
	const tml::shared_ptr<tml::scene::Node> &GetPlayerNode(void);
	INT AddPlayerNode(const tml::shared_ptr<tml::scene::Node> &, const bool event_flg = true);
	void RemovePlayerNode(const bool event_flg = true);
	const std::list<tml::shared_ptr<tml::scene::Node>> &GetMobNodeContainer(void);
	const tml::shared_ptr<tml::scene::Node> &GetMobNode(void);
	INT AddMobNode(const tml::shared_ptr<tml::scene::Node> &, const bool event_flg = true);
	void RemoveMobNode(const bool event_flg = true);
	const std::list<tml::shared_ptr<tml::scene::Node>> &GetBulletNodeContainer(void);
	const tml::shared_ptr<tml::scene::Node> &GetBulletNode(void);
	INT AddBulletNode(const tml::shared_ptr<tml::scene::Node> &, const bool event_flg = true);
	void RemoveBulletNode(const bool event_flg = true);
};
}
}


/**
 * @brief GetGroundNode�֐�
 * @return ground_node (ground_node)<br>
 * nullptr=���s
 */
inline const tml::shared_ptr<tml::scene::Node> &cpp_base::scene::Field2DNode::GetGroundNode(void)
{
	return (this->ground_layout_node_->GetChildNode());
}


/**
 * @brief GetPlayerNode�֐�
 * @return pl_node (player_node)<br>
 * nullptr=���s
 */
inline const tml::shared_ptr<tml::scene::Node> &cpp_base::scene::Field2DNode::GetPlayerNode(void)
{
	return (this->pl_layout_node_->GetChildNode());
}


/**
 * @brief GetMobNodeContainer�֐�
 * @return mob_node_cont (mob_node_container)<br>
 * nullptr=���s
 */
inline const std::list<tml::shared_ptr<tml::scene::Node>> &cpp_base::scene::Field2DNode::GetMobNodeContainer(void)
{
	return (this->mob_layout_node_->GetChildNodeContainer());
}


/**
 * @brief GetMobNode�֐�
 * @return mob_node (mob_node)<br>
 * nullptr=���s
 */
inline const tml::shared_ptr<tml::scene::Node> &cpp_base::scene::Field2DNode::GetMobNode(void)
{
	return (this->mob_layout_node_->GetChildNode());
}


/**
 * @brief GetBulletNodeContainer�֐�
 * @return bullet_node_cont (bullet_node_container)<br>
 * nullptr=���s
 */
inline const std::list<tml::shared_ptr<tml::scene::Node>> &cpp_base::scene::Field2DNode::GetBulletNodeContainer(void)
{
	return (this->bullet_layout_node_->GetChildNodeContainer());
}


/**
 * @brief GetBulletNode�֐�
 * @return bullet_node (bullet_node)<br>
 * nullptr=���s
 */
inline const tml::shared_ptr<tml::scene::Node> &cpp_base::scene::Field2DNode::GetBulletNode(void)
{
	return (this->bullet_layout_node_->GetChildNode());
}
