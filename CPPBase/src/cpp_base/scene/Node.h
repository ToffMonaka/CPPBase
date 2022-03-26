/**
 * @file
 * @brief Node�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SCENE.h"
#include "../../lib/tml/scene/Node.h"


namespace cpp_base {
namespace input {
class Manager;
}
namespace graphic {
class Manager;
}
namespace sound {
class Manager;
}
}


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

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

	virtual void OnSetManager(tml::Manager *);

public:
	NodeDesc();
	virtual ~NodeDesc();

	virtual void Init(void);

	cpp_base::scene::Manager *GetManager(void) const;
};
}
}


/**
 * @brief Release�֐�
 */
inline void cpp_base::scene::NodeDesc::Release(void)
{
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
	const cpp_base::scene::NodeDesc *desc_;
	cpp_base::scene::Manager *mgr_;
	cpp_base::input::Manager *input_mgr_;
	cpp_base::graphic::Manager *graphic_mgr_;
	cpp_base::sound::Manager *sound_mgr_;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);
	virtual void OnSetManager(tml::Manager *);

public:
	Node();
	virtual ~Node();

	virtual void Init(void);

	const cpp_base::scene::NodeDesc *GetDesc(void) const;
	cpp_base::scene::Manager *GetManager(void);
	cpp_base::input::Manager *GetInputManager(void);
	cpp_base::graphic::Manager *GetGraphicManager(void);
	cpp_base::sound::Manager *GetSoundManager(void);
};
}
}


/**
 * @brief GetDesc�֐�
 * @return desc (desc)
 */
inline const cpp_base::scene::NodeDesc *cpp_base::scene::Node::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline cpp_base::scene::Manager *cpp_base::scene::Node::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetInputManager�֐�
 * @return input_mgr (input_manager)
 */
inline cpp_base::input::Manager *cpp_base::scene::Node::GetInputManager(void)
{
	return (this->input_mgr_);
}


/**
 * @brief GetGraphicManager�֐�
 * @return graphic_mgr (graphic_manager)
 */
inline cpp_base::graphic::Manager *cpp_base::scene::Node::GetGraphicManager(void)
{
	return (this->graphic_mgr_);
}


/**
 * @brief GetSoundManager�֐�
 * @return sound_mgr (sound_manager)
 */
inline cpp_base::sound::Manager *cpp_base::scene::Node::GetSoundManager(void)
{
	return (this->sound_mgr_);
}
