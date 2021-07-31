/**
 * @file
 * @brief Node�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SCENE.h"
#include "../../lib/tml/scene/Node.h"


namespace cpp_base {
namespace scene {
/**
 * @brief NodeDesc�N���X
 */
class NodeDesc : public tml::scene::NodeDesc
{
private:
	cpp_base::scene::Manager *mgr_;

public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	NodeDesc();
	virtual ~NodeDesc();

	virtual void Init(void);

	cpp_base::scene::Manager *GetManager(void) const;
	void SetManager(cpp_base::scene::Manager *);
};
}
}


/**
 * @brief Release�֐�
 */
inline void cpp_base::scene::NodeDesc::Release(void)
{
	tml::scene::NodeDesc::Release();

	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline cpp_base::scene::Manager *cpp_base::scene::NodeDesc::GetManager(void) const
{
	return (this->mgr_);
}


namespace cpp_base {
namespace scene {
/**
 * @brief Node�N���X
 */
class Node : public tml::scene::Node
{
public: Node(const cpp_base::scene::Node &) = delete;
public: cpp_base::scene::Node &operator =(const cpp_base::scene::Node &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	cpp_base::scene::Manager *mgr_;

protected:
	void Release(void);

public:
	Node();
	virtual ~Node();

	virtual void Init(void);
	INT Create(const cpp_base::scene::NodeDesc &);

	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);

	cpp_base::scene::Manager *GetManager(void);
};
}
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline cpp_base::scene::Manager *cpp_base::scene::Node::GetManager(void)
{
	return (this->mgr_);
}
