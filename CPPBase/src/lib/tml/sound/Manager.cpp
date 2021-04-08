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
	window_handle(nullptr),
	window_device_context_handle(nullptr)
{
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

	this->window_handle = nullptr;
	this->window_device_context_handle = nullptr;
	this->volume_array.fill(0.5f);
	this->mute_flag_array.fill(false);

	return;
}


/**
 * @brief コンストラクタ
 */
tml::sound::Manager::Manager() :
	wnd_handle_(nullptr),
	wnd_dc_handle_(nullptr),
	event_cnt_ary_{},
	front_event_index_(0U),
	back_event_index_(0U),
	stock_event_cnt_ary_{},
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

	for (auto &res_cont : this->res_cont_ary_) {
		for (auto &res : res_cont) {
			res->Init();
		}

		res_cont.clear();
	}

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

	this->wnd_handle_ = nullptr;
	this->wnd_dc_handle_ = nullptr;
	this->event_cnt_ary_.fill(0U);

	for (auto &event_cont : this->event_cont_ary_) {
		event_cont.clear();
	}

	this->front_event_index_ = 0U;
	this->back_event_index_ = 0U;

	this->stock_event_cnt_ary_.fill(0U);

	for (auto &stock_event_cont : this->stock_event_cont_ary_) {
		stock_event_cont.clear();
	}

	this->volume_ary_.fill(0.5f);
	this->mute_flg_ary_.fill(false);

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
	if ((desc.window_handle == nullptr)
	|| (desc.window_device_context_handle == nullptr)) {
		this->Init();

		return (-1);
	}

	this->Init();

	this->wnd_handle_ = desc.window_handle;
	this->wnd_dc_handle_ = desc.window_device_context_handle;

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
	this->UpdateEvent();

	return;
}


/**
 * @brief UpdateEvent関数
 */
void tml::sound::Manager::UpdateEvent(void)
{
	if (this->front_event_index_ == this->back_event_index_) {
		this->front_event_index_ = 0U;
		this->back_event_index_ = 1U;
	} else {
		auto tmp_event_index = this->front_event_index_;

		this->front_event_index_ = this->back_event_index_;
		this->back_event_index_ = tmp_event_index;
	}

	auto &back_event_cnt = this->event_cnt_ary_[this->back_event_index_];
	auto &back_event_cont = this->event_cont_ary_[this->back_event_index_];

	for (UINT back_event_i = 0U; back_event_i < back_event_cnt; ++back_event_i) {
		tml::unique_ptr<tml::sound::Event> &event = back_event_cont[back_event_i];

		auto event_index = static_cast<UINT>(event->GetEventType());
		auto &stock_event_cnt = this->stock_event_cnt_ary_[event_index];
		auto &stock_event_cont = this->stock_event_cont_ary_[event_index];

		if (stock_event_cnt >= stock_event_cont.size()) {
			stock_event_cont.resize(stock_event_cnt + 128U);
		}

		stock_event_cont[stock_event_cnt] = std::move(event);

		++stock_event_cnt;
	}

	back_event_cnt = 0U;

	return;
}


/**
 * @brief SetVolume関数
 * @param volume (volume)
 */
void tml::sound::Manager::SetVolume(const tml::ConstantUtil::SOUND::SOUND_TYPE type, const FLOAT volume)
{
	this->volume_ary_[static_cast<UINT>(type)] = volume;

	for (auto &res : this->res_cont_ary_[static_cast<UINT>(tml::ConstantUtil::SOUND::RESOURCE_TYPE::SOUND)]) {
		auto sound = reinterpret_cast<tml::sound::Sound *>(res.get());

		if ((sound->GetType() != type)
		|| (sound->GetSource() == 0U)) {
			continue;
		}

		alSourcef(sound->GetSource(), AL_GAIN, (this->mute_flg_ary_[static_cast<UINT>(sound->GetType())]) ? 0.0f : this->volume_ary_[static_cast<UINT>(sound->GetType())]);
	}

	return;
}


/**
 * @brief SetMuteFlag関数
 * @param mute_flg (mute_flag)
 */
void tml::sound::Manager::SetMuteFlag(const tml::ConstantUtil::SOUND::SOUND_TYPE type, const bool mute_flg)
{
	this->mute_flg_ary_[static_cast<UINT>(type)] = mute_flg;

	for (auto &res : this->res_cont_ary_[static_cast<UINT>(tml::ConstantUtil::SOUND::RESOURCE_TYPE::SOUND)]) {
		auto sound = reinterpret_cast<tml::sound::Sound *>(res.get());

		if ((sound->GetType() != type)
		|| (sound->GetSource() == 0U)) {
			continue;
		}

		alSourcef(sound->GetSource(), AL_GAIN, (this->mute_flg_ary_[static_cast<UINT>(sound->GetType())]) ? 0.0f : this->volume_ary_[static_cast<UINT>(sound->GetType())]);
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
