/**
 * @file
 * @brief Managerコードファイル
 */


#include "Manager.h"
#include "Sound.h"
#include "BGMSound.h"
#include "SESound.h"


/**
 * @brief コンストラクタ
 */
tml::sound::ManagerDesc::ManagerDesc() :
	bgm_sound_volume(0.5f),
	bgm_sound_mute_flag(false),
	se_sound_volume(0.5f),
	se_sound_mute_flag(false)
{
	this->resource_count = tml::ConstantUtil::SOUND::RESOURCE_TYPE_COUNT;
	this->task_count = tml::ConstantUtil::SOUND::TASK_TYPE_COUNT;
	this->event_count = tml::ConstantUtil::SOUND::EVENT_TYPE_COUNT;

	return;
}


/**
 * @brief デストラクタ
 */
tml::sound::ManagerDesc::~ManagerDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::sound::ManagerDesc::Init(void)
{
	this->Release();

	this->bgm_sound_volume = 0.5f;
	this->bgm_sound_mute_flag = false;
	this->se_sound_volume = 0.5f;
	this->se_sound_mute_flag = false;

	tml::ManagerDesc::Init();

	this->resource_count = tml::ConstantUtil::SOUND::RESOURCE_TYPE_COUNT;
	this->task_count = tml::ConstantUtil::SOUND::TASK_TYPE_COUNT;
	this->event_count = tml::ConstantUtil::SOUND::EVENT_TYPE_COUNT;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::sound::Manager::Manager() :
	device_(nullptr),
	device_context_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::sound::Manager::~Manager()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::sound::Manager::Release(void)
{
	this->common.Init();

	this->DeleteResourceContainer();
	this->DeleteTaskContainer();
	this->DeleteEventContainer();

	if (this->device_context_ != nullptr) {
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(this->device_context_);

		this->device_context_ = nullptr;
	}

	if (this->device_ != nullptr) {
		alcCloseDevice(this->device_);

		this->device_ = nullptr;
	}

	return;
}


/**
 * @brief Init関数
 */
void tml::sound::Manager::Init(void)
{
	this->Release();

	this->sound_volume_cont_.clear();
	this->sound_mute_flg_cont_.clear();

	tml::Manager::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::sound::Manager::Create(const tml::sound::ManagerDesc &desc)
{
	this->Init();

	if (tml::Manager::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	{// Device Create
		this->device_ = alcOpenDevice(nullptr);

		if (this->device_ == nullptr) {
			this->Init();

			return (-1);
		}

		this->device_context_ = alcCreateContext(this->device_, nullptr);

		if (this->device_context_ == nullptr) {
			this->Init();

			return (-1);
		}

		if (alcMakeContextCurrent(this->device_context_) == ALC_FALSE) {
			this->Init();

			return (-1);
		}
	}

	this->sound_volume_cont_.resize(desc.resource_count);
	this->sound_mute_flg_cont_.resize(desc.resource_count);

	this->sound_volume_cont_[static_cast<UINT>(tml::ConstantUtil::SOUND::RESOURCE_TYPE::BGM_SOUND)] = desc.bgm_sound_volume;
	this->sound_mute_flg_cont_[static_cast<UINT>(tml::ConstantUtil::SOUND::RESOURCE_TYPE::BGM_SOUND)] = desc.bgm_sound_mute_flag;

	this->sound_volume_cont_[static_cast<UINT>(tml::ConstantUtil::SOUND::RESOURCE_TYPE::SE_SOUND)] = desc.se_sound_volume;
	this->sound_mute_flg_cont_[static_cast<UINT>(tml::ConstantUtil::SOUND::RESOURCE_TYPE::SE_SOUND)] = desc.se_sound_mute_flag;

	{// ResourceFactory Set
	}

	if (this->common.Create(this) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief Update関数
 */
void tml::sound::Manager::Update(void)
{
	tml::Manager::Update();

	return;
}


/**
 * @brief SetSoundVolumePart関数
 * @param res_type (resource_type)
 */
void tml::sound::Manager::SetSoundVolumePart(const UINT res_type)
{
	auto res_cont = this->GetResourceContainer(res_type);

	if (res_cont == nullptr) {
		return;
	}

	for (auto &res : (*res_cont)) {
		auto sound = reinterpret_cast<tml::sound::Sound *>(res.get());

		if (sound->GetSource() == 0U) {
			continue;
		}

		alSourcef(sound->GetSource(), AL_GAIN, (this->sound_mute_flg_cont_[sound->GetResourceType()]) ? 0.0f : this->sound_volume_cont_[sound->GetResourceType()]);
	}

	return;
}


/**
 * @brief SetSoundMuteFlagPart関数
 * @param res_type (resource_type)
 */
void tml::sound::Manager::SetSoundMuteFlagPart(const UINT res_type)
{
	auto res_cont = this->GetResourceContainer(res_type);

	if (res_cont == nullptr) {
		return;
	}

	for (auto &res : (*res_cont)) {
		auto sound = reinterpret_cast<tml::sound::Sound *>(res.get());

		if (sound->GetSource() == 0U) {
			continue;
		}

		alSourcef(sound->GetSource(), AL_GAIN, (this->sound_mute_flg_cont_[sound->GetResourceType()]) ? 0.0f : this->sound_volume_cont_[sound->GetResourceType()]);
	}

	return;
}


/**
 * @brief PlaySound関数
 * @param sound (sound)
 * @param loop_flg (loop_flag)
 */
void tml::sound::Manager::PlaySound(tml::sound::Sound *sound, const bool loop_flg)
{
	if ((sound == nullptr)
	|| (sound->GetSource() == 0U)) {
		return;
	}

	alSourcef(sound->GetSource(), AL_GAIN, (this->sound_mute_flg_cont_[sound->GetResourceType()]) ? 0.0f : this->sound_volume_cont_[sound->GetResourceType()]);
	alSourcei(sound->GetSource(), AL_LOOPING, loop_flg);

	alSourcePlay(sound->GetSource());

	return;
}


/**
 * @brief StopSound関数
 * @param sound (sound)
 */
void tml::sound::Manager::StopSound(tml::sound::Sound *sound)
{
	if ((sound == nullptr)
	|| (sound->GetSource() == 0U)) {
		return;
	}

	alSourceStop(sound->GetSource());

	return;
}


/**
 * @brief PauseSound関数
 * @param sound (sound)
 */
void tml::sound::Manager::PauseSound(tml::sound::Sound *sound)
{
	if ((sound == nullptr)
	|| (sound->GetSource() == 0U)) {
		return;
	}

	alSourcePause(sound->GetSource());

	return;
}
