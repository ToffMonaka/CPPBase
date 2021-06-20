/**
 * @file
 * @brief Manager�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../time/FrameRate.h"
#include "../manager/Manager.h"
#include "ManagerCommon.h"
#include "Scene.h"
#include "Node.h"


namespace tml {
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


namespace tml {
namespace scene {
/**
 * @brief ManagerDesc�N���X
 */
class ManagerDesc : public tml::ManagerDesc
{
private:
	tml::input::Manager *input_mgr_;
	tml::graphic::Manager *graphic_mgr_;
	tml::sound::Manager *sound_mgr_;

public:

protected:
	void Release(void);

	void InitResourceCount(void);
	void InitEventCount(void);

public:
	ManagerDesc();
	virtual ~ManagerDesc();

	virtual void Init(void);

	tml::input::Manager *GetInputManager(void) const;
	void SetInputManager(tml::input::Manager *);
	tml::graphic::Manager *GetGraphicManager(void) const;
	void SetGraphicManager(tml::graphic::Manager *);
	tml::sound::Manager *GetSoundManager(void) const;
	void SetSoundManager(tml::sound::Manager *);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::scene::ManagerDesc::Release(void)
{
	tml::ManagerDesc::Release();

	return;
}


/**
 * @brief GetInputManager�֐�
 * @return input_mgr (input_manager)
 */
inline tml::input::Manager *tml::scene::ManagerDesc::GetInputManager(void) const
{
	return (this->input_mgr_);
}


/**
 * @brief GetGraphicManager�֐�
 * @return graphic_mgr (graphic_manager)
 */
inline tml::graphic::Manager *tml::scene::ManagerDesc::GetGraphicManager(void) const
{
	return (this->graphic_mgr_);
}


/**
 * @brief GetSoundManager�֐�
 * @return sound_mgr (sound_manager)
 */
inline tml::sound::Manager *tml::scene::ManagerDesc::GetSoundManager(void) const
{
	return (this->sound_mgr_);
}


namespace tml {
namespace scene {
/**
 * @brief Manager�N���X
 */
class Manager : public tml::Manager
{
public: Manager(const tml::scene::Manager &) = delete;
public: tml::scene::Manager &operator =(const tml::scene::Manager &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	tml::input::Manager *input_mgr_;
	tml::graphic::Manager *graphic_mgr_;
	tml::sound::Manager *sound_mgr_;
	tml::FrameRate frame_rate_;
	tml::shared_ptr<tml::scene::Scene> scene_;

public:
	tml::ManagerResourceFactory<tml::scene::Scene, tml::INIFileReadDesc> scene_factory_by_ini_file;
	tml::ManagerResourceFactory<tml::scene::Scene, tml::XMLFileReadDesc> scene_factory_by_xml_file;
	tml::ManagerResourceFactory<tml::scene::Node, tml::INIFileReadDesc> node_factory_by_ini_file;
	tml::ManagerResourceFactory<tml::scene::Node, tml::XMLFileReadDesc> node_factory_by_xml_file;
	tml::scene::ManagerCommon common;

protected:
	void Release(void);

	INT CreateCommon(void);
	void DeleteCommon(void);

public:
	Manager();
	virtual ~Manager();

	virtual void Init(void);
	INT Create(const tml::scene::ManagerDesc &);

	void Update(void);

	tml::input::Manager *GetInputManager(void);
	tml::graphic::Manager *GetGraphicManager(void);
	tml::sound::Manager *GetSoundManager(void);
	const tml::FrameRate &GetFrameRate(void) const;

	const tml::shared_ptr<tml::scene::Scene> &GetScene(void);
	INT StartScene(tml::shared_ptr<tml::scene::Scene> &);
	void EndScene(void);
	INT AddNode(tml::shared_ptr<tml::scene::Node> &, tml::shared_ptr<tml::scene::Node> &);
	void RemoveNode(tml::shared_ptr<tml::scene::Node> &, tml::shared_ptr<tml::scene::Node> &);
};
}
}


/**
 * @brief GetInputManager�֐�
 * @return input_mgr (input_manager)
 */
inline tml::input::Manager *tml::scene::Manager::GetInputManager(void)
{
	return (this->input_mgr_);
}


/**
 * @brief GetGraphicManager�֐�
 * @return graphic_mgr (graphic_manager)
 */
inline tml::graphic::Manager *tml::scene::Manager::GetGraphicManager(void)
{
	return (this->graphic_mgr_);
}


/**
 * @brief GetSoundManager�֐�
 * @return sound_mgr (sound_manager)
 */
inline tml::sound::Manager *tml::scene::Manager::GetSoundManager(void)
{
	return (this->sound_mgr_);
}


/**
 * @brief GetFrameRate�֐�
 * @return frame_rate (frame_rate)
 */
inline const tml::FrameRate &tml::scene::Manager::GetFrameRate(void) const
{
	return (this->frame_rate_);
}


/**
 * @brief GetScene�֐�
 * @return scene (scene)
 */
inline const tml::shared_ptr<tml::scene::Scene> &tml::scene::Manager::GetScene(void)
{
	return (this->scene_);
}
