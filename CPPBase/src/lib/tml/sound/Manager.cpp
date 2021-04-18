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
tml::sound::ManagerDesc::ManagerDesc()
{
	this->resource_count_container.clear();
	this->resource_count_container.resize(tml::ConstantUtil::SOUND::RESOURCE_TYPE_COUNT);
	this->resource_count_container[static_cast<UINT>(tml::ConstantUtil::SOUND::RESOURCE_TYPE::SOUND)] = tml::ConstantUtil::SOUND::SOUND_TYPE_COUNT;
	this->event_count = tml::ConstantUtil::SOUND::EVENT_TYPE_COUNT;

	this->volume_array.fill(0.5f);
	this->mute_flag_array.fill(false);

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

	this->resource_count_container.clear();
	this->resource_count_container.resize(tml::ConstantUtil::SOUND::RESOURCE_TYPE_COUNT);
	this->resource_count_container[static_cast<UINT>(tml::ConstantUtil::SOUND::RESOURCE_TYPE::SOUND)] = tml::ConstantUtil::SOUND::SOUND_TYPE_COUNT;
	this->event_count = tml::ConstantUtil::SOUND::EVENT_TYPE_COUNT;

	this->volume_array.fill(0.5f);
	this->mute_flag_array.fill(false);

	tml::ManagerDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::sound::Manager::Manager() :
	device_(nullptr),
	device_context_(nullptr)
{
	this->volume_ary_.fill(0.5f);
	this->mute_flg_ary_.fill(false);

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
	this->common_.Init();
	this->DeleteResourceContainer();

	if (this->device_context_ != nullptr) {
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(this->device_context_);

		this->device_context_ = nullptr;
	}

	if (this->device_ != nullptr) {
		alcCloseDevice(this->device_);

		this->device_ = nullptr;
	}

	tml::Manager::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::sound::Manager::Init(void)
{
	this->Release();

	this->volume_ary_.fill(0.5f);
	this->mute_flg_ary_.fill(false);

	tml::Manager::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
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

	this->volume_ary_ = desc.volume_array;
	this->mute_flg_ary_ = desc.mute_flag_array;

	if (this->common_.Create(this) < 0) {
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
 * @brief SetVolume関数
 * @param type (type)
 * @param volume (volume)
 */
void tml::sound::Manager::SetVolume(const tml::ConstantUtil::SOUND::SOUND_TYPE type, const FLOAT volume)
{
	this->volume_ary_[static_cast<UINT>(type)] = volume;

	auto res_cont = this->GetResourceContainer(static_cast<UINT>(tml::ConstantUtil::SOUND::RESOURCE_TYPE::SOUND), static_cast<UINT>(type));

	if (res_cont != nullptr) {
		for (auto &res : (*res_cont)) {
			auto sound = reinterpret_cast<tml::sound::Sound *>(res.get());

			if (sound->GetSource() == 0U) {
				continue;
			}

			alSourcef(sound->GetSource(), AL_GAIN, (this->mute_flg_ary_[static_cast<UINT>(sound->GetType())]) ? 0.0f : this->volume_ary_[static_cast<UINT>(sound->GetType())]);
		}
	}

	return;
}


/**
 * @brief SetMuteFlag関数
 * @param type (type)
 * @param mute_flg (mute_flag)
 */
void tml::sound::Manager::SetMuteFlag(const tml::ConstantUtil::SOUND::SOUND_TYPE type, const bool mute_flg)
{
	this->mute_flg_ary_[static_cast<UINT>(type)] = mute_flg;

	auto res_cont = this->GetResourceContainer(static_cast<UINT>(tml::ConstantUtil::SOUND::RESOURCE_TYPE::SOUND), static_cast<UINT>(type));

	if (res_cont != nullptr) {
		for (auto &res : (*res_cont)) {
			auto sound = reinterpret_cast<tml::sound::Sound *>(res.get());

			if (sound->GetSource() == 0U) {
				continue;
			}

			alSourcef(sound->GetSource(), AL_GAIN, (this->mute_flg_ary_[static_cast<UINT>(sound->GetType())]) ? 0.0f : this->volume_ary_[static_cast<UINT>(sound->GetType())]);
		}
	}

	return;
}


/**
 * @brief Play関数
 * @param sound (sound)
 * @param loop_flg (loop_flag)
 */
void tml::sound::Manager::Play(tml::sound::Sound *sound, const bool loop_flg)
{
	if ((sound == nullptr)
	|| (sound->GetSource() == 0U)) {
		return;
	}

	alSourcef(sound->GetSource(), AL_GAIN, (this->mute_flg_ary_[static_cast<UINT>(sound->GetType())]) ? 0.0f : this->volume_ary_[static_cast<UINT>(sound->GetType())]);
	alSourcei(sound->GetSource(), AL_LOOPING, loop_flg);

	alSourcePlay(sound->GetSource());

	return;
}


/**
 * @brief Stop関数
 * @param sound (sound)
 */
void tml::sound::Manager::Stop(tml::sound::Sound *sound)
{
	if ((sound == nullptr)
	|| (sound->GetSource() == 0U)) {
		return;
	}

	alSourceStop(sound->GetSource());

	return;
}


/**
 * @brief Pause関数
 * @param sound (sound)
 */
void tml::sound::Manager::Pause(tml::sound::Sound *sound)
{
	if ((sound == nullptr)
	|| (sound->GetSource() == 0U)) {
		return;
	}

	alSourcePause(sound->GetSource());

	return;
}
