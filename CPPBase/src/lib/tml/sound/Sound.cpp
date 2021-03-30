/**
 * @file
 * @brief Soundコードファイル
 */


#include "Sound.h"
#include <mmsystem.h>
#include <mmreg.h>
#include "../constant/ConstantInclude_LibOggBase.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::sound::SoundDesc::SoundDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::sound::SoundDesc::~SoundDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::sound::SoundDesc::Init(void)
{
	this->Release();

	this->file_read_desc.Init();

	tml::sound::ResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::sound::SoundDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::sound::ResourceDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Sound Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"SOUND");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::sound::Sound::Sound() :
	type_(tml::ConstantUtil::SOUND::SOUND_TYPE::NONE),
	buf_(0U),
	src_(0U)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::sound::Sound::~Sound()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::sound::Sound::Release(void)
{
	if (this->src_ != 0U) {
		alDeleteSources(1, &this->src_);

		this->src_ = 0U;
	}

	if (this->buf_ != 0U) {
		alDeleteBuffers(1, &this->buf_);

		this->buf_ = 0U;
	}

	tml::sound::Resource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::sound::Sound::Init(void)
{
	this->type_ = tml::ConstantUtil::SOUND::SOUND_TYPE::NONE;

	tml::sound::Resource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @param type (type)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::sound::Sound::Create(const tml::sound::SoundDesc &desc, const tml::ConstantUtil::SOUND::SOUND_TYPE type)
{
	if (type == tml::ConstantUtil::SOUND::SOUND_TYPE::NONE) {
		return (-1);
	}

	if (tml::sound::Resource::Create(desc, tml::ConstantUtil::SOUND::RESOURCE_TYPE::SOUND) < 0) {
		return (-1);
	}

	this->type_ = type;

	auto file_read_desc_dat = desc.file_read_desc.GetDataByParent();

	tml::BinaryFile bin_file;

	bin_file.read_desc.parent_data = file_read_desc_dat;

	if (bin_file.Read() < 0) {
		return (-1);
	}

	if (bin_file.data.file_buffer.GetLength() <= 0U) {
		return (-1);
	}

    UINT file_format = 0U;

    do {
		// Check WAVE File
        if ((bin_file.data.file_buffer.GetLength() >= 4U)
        && (strncmp(reinterpret_cast<CHAR *>(bin_file.data.file_buffer.Get()), "RIFF", 4U) == 0)) {
            file_format = 1U;

            break;
        }

		// Check Ogg File
        if ((bin_file.data.file_buffer.GetLength() >= 3U)
        && (strncmp(reinterpret_cast<CHAR *>(bin_file.data.file_buffer.Get()), "ID3", 3U) == 0)) {
            file_format = 2U;

            break;
        }

		// Check MP3 File
        if ((bin_file.data.file_buffer.GetLength() >= 4U)
        && (strncmp(reinterpret_cast<CHAR *>(bin_file.data.file_buffer.Get()), "OggS", 4U) == 0)) {
            file_format = 3U;

            break;
        }
    } while (0);

	switch (file_format) {
	case 1: {// Read WAVE File
		MMIOINFO mmio_info = {};

		mmio_info.fccIOProc = FOURCC_MEM;
		mmio_info.cchBuffer = bin_file.data.file_buffer.GetLength();
		mmio_info.pchBuffer = reinterpret_cast<HPSTR>(bin_file.data.file_buffer.Get());

		HMMIO mmio_handle = mmioOpen(nullptr, &mmio_info, MMIO_READ);

		if (mmio_handle == nullptr) {
			return (-1);
		}

		MMCKINFO riff_mmck_info = {};

		riff_mmck_info.fccType = mmioFOURCC('W', 'A', 'V', 'E');

		if (mmioDescend(mmio_handle, &riff_mmck_info, nullptr, MMIO_FINDRIFF) != MMSYSERR_NOERROR) {
			mmioClose(mmio_handle, 0U);

			return (-1);
		}

		MMCKINFO fmt_mmck_info = {};

		fmt_mmck_info.ckid = mmioFOURCC('f', 'm', 't', ' ');

		if (mmioDescend(mmio_handle, &fmt_mmck_info, &riff_mmck_info, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {
			mmioClose(mmio_handle, 0U);

			return (-1);
		}

		WAVEFORMATEX wav_format;

		if (fmt_mmck_info.cksize == sizeof(WAVEFORMATEXTENSIBLE)) {
			WAVEFORMATEXTENSIBLE tmp_wav_format;

			if (mmioRead(mmio_handle, reinterpret_cast<HPSTR>(&tmp_wav_format), sizeof(WAVEFORMATEXTENSIBLE)) != sizeof(WAVEFORMATEXTENSIBLE)) {
				mmioClose(mmio_handle, 0U);

				return (-1);
			}

			wav_format = tmp_wav_format.Format;
		} else if (fmt_mmck_info.cksize == sizeof(WAVEFORMATEX)) {
			WAVEFORMATEX tmp_wav_format;

			if (mmioRead(mmio_handle, reinterpret_cast<HPSTR>(&tmp_wav_format), sizeof(WAVEFORMATEX)) != sizeof(WAVEFORMATEX)) {
				mmioClose(mmio_handle, 0U);

				return (-1);
			}

			wav_format = tmp_wav_format;
		} else if (fmt_mmck_info.cksize == sizeof(PCMWAVEFORMAT)) {
			PCMWAVEFORMAT tmp_wav_format;

			if (mmioRead(mmio_handle, reinterpret_cast<HPSTR>(&tmp_wav_format), sizeof(PCMWAVEFORMAT)) != sizeof(PCMWAVEFORMAT)) {
				mmioClose(mmio_handle, 0U);

				return (-1);
			}

			tml::Copy(reinterpret_cast<PCMWAVEFORMAT *>(&wav_format), &tmp_wav_format, 1U);
			wav_format.cbSize = 0;
		} else {
			mmioClose(mmio_handle, 0U);

			return (-1);
		}

		mmioAscend(mmio_handle, &fmt_mmck_info, 0U);

		MMCKINFO dat_mmck_info = {};

		dat_mmck_info.ckid = mmioFOURCC('d', 'a', 't', 'a');

		if (mmioDescend(mmio_handle, &dat_mmck_info, &riff_mmck_info, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {
			mmioClose(mmio_handle, 0U);

			return (-1);
		}

		tml::DynamicBuffer buf;

		buf.SetSize(dat_mmck_info.cksize);
		buf.AddWriteIndex(buf.GetSize());

		if (mmioRead(mmio_handle, reinterpret_cast<HPSTR>(buf.Get()), buf.GetLength()) != buf.GetLength()) {
			mmioClose(mmio_handle, 0U);

			return (-1);
		}

		mmioClose(mmio_handle, 0U);

        ALenum buf_format = AL_NONE;

		if (wav_format.nChannels == 1) {
			buf_format = AL_FORMAT_MONO16;
		} else if (wav_format.nChannels == 2) {
			buf_format = AL_FORMAT_STEREO16;
		} else {
			return (-1);
		}

		ALsizei buf_sampling_rate = wav_format.nSamplesPerSec;

		alGenBuffers(1, &this->buf_);
        alBufferData(this->buf_, buf_format, buf.Get(), buf.GetLength(), buf_sampling_rate);

		if (alGetError() != AL_NO_ERROR) {
			return (-1);
		}

		break;
	}
	case 2: {// Read Ogg File
		break;
	}
	case 3: {// Read MP3 File
		break;
	}
	default: {
		return (-1);
	}
	}

	alGenSources(1, &this->src_);
    alSourcei(this->src_, AL_BUFFER, static_cast<ALint>(this->buf_));

	if (alGetError() != AL_NO_ERROR) {
		return (-1);
	}

	alSourcef(this->src_, AL_GAIN, 0.5f);
	alSourcei(this->src_, AL_LOOPING, AL_FALSE);

	/*
	OggVorbis_File vorbis_file;

	if (ov_fopen("res/title_bgm_sound1.ogg", &vorbis_file)) {
		this->Init();

		return (-1);
	}

	vorbis_info *vorbis_info = ov_info(&vorbis_file, -1);

	if (vorbis_info == nullptr) {
		ov_clear(&vorbis_file);

		this->Init();

		return (-1);
	}

	ov_clear(&vorbis_file);
	*/

	return (0);
}
