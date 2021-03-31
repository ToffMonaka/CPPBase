/**
 * @file
 * @brief Soundコードファイル
 */


#include "Sound.h"
#include <mmsystem.h>
#include <mmreg.h>
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
	src_(0U),
	ogg_file_buf_(0L),
	ogg_file_buf_size_(0L),
	ogg_file_buf_pos_(0L)
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
	this->ogg_file_buf_ = nullptr;
	this->ogg_file_buf_size_ = 0L;
	this->ogg_file_buf_pos_ = 0L;

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

		// Check MP3 File
        if ((bin_file.data.file_buffer.GetLength() >= 3U)
        && (strncmp(reinterpret_cast<CHAR *>(bin_file.data.file_buffer.Get()), "ID3", 3U) == 0)) {
            file_format = 2U;

            break;
        }

		// Check Ogg File
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

		WAVEFORMATEX wav_format = {};

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
	case 2: {// Read MP3 File
		break;
	}
	case 3: {// Read Ogg File
		this->ogg_file_buf_ = bin_file.data.file_buffer.Get();
		this->ogg_file_buf_size_ = bin_file.data.file_buffer.GetLength();
		this->ogg_file_buf_pos_ = 0L;

		OggVorbis_File ogg_file;
		ov_callbacks ogg_file_callback = {
			&tml::sound::Sound::ReadOggFile,
			&tml::sound::Sound::SeekOggFile,
			&tml::sound::Sound::CloseOggFile,
			&tml::sound::Sound::TellOggFile
		};

		if (ov_open_callbacks(this, &ogg_file, nullptr, 0L, ogg_file_callback) != 0) {
			return (-1);
		}

		vorbis_info *ogg_info = ov_info(&ogg_file, -1);

		if (ogg_info == nullptr) {
			ov_clear(&ogg_file);

			return (-1);
		}

		WAVEFORMATEX wav_format = {};

		wav_format.wFormatTag = WAVE_FORMAT_PCM;
		wav_format.nChannels = ogg_info->channels;
		wav_format.nSamplesPerSec = ogg_info->rate;
		wav_format.nAvgBytesPerSec = ogg_info->rate * ogg_info->channels * 2;
		wav_format.nBlockAlign = ogg_info->channels * 2;
		wav_format.wBitsPerSample = 16;
		wav_format.cbSize = 0;

		tml::DynamicBuffer buf;

		buf.SetSize(static_cast<size_t>(ov_pcm_total(&ogg_file, -1) * ogg_info->channels * 2));
		buf.AddWriteIndex(buf.GetSize());

		LONG read_size = 0L;
		INT read_res = 0;
		INT read_bitstream = 0;
 
		while (read_size < static_cast<LONG>(buf.GetLength())) {
			LONG tmp_read_size = ov_read(&ogg_file, reinterpret_cast<CHAR *>(&buf.Get()[read_size]), static_cast<LONG>(buf.GetLength()) - read_size, 0, 2, 1, &read_bitstream);
 
			if (tmp_read_size < 0L) {
				read_res = -1;

				break;
			} else if (tmp_read_size == 0L) {
				break;
			}
 
			read_size += tmp_read_size;
		}

		if (read_res < 0) {
			ov_clear(&ogg_file);

			return (-1);
		}

		ov_clear(&ogg_file);

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
	default: {
		return (-1);
	}
	}

	alGenSources(1, &this->src_);
    alSourcei(this->src_, AL_BUFFER, static_cast<ALint>(this->buf_));

	if (alGetError() != AL_NO_ERROR) {
		return (-1);
	}

	return (0);
}


/**
 * @brief ReadOggFile関数
 * @param buf (buffer)
 * @param size (size)
 * @param cnt (count)
 * @param src (source)
 * @return read_cnt (read_count)
 */
size_t tml::sound::Sound::ReadOggFile(void *buf, size_t size, size_t cnt, void *src)
{
	auto sound = reinterpret_cast<tml::sound::Sound *>(src);

	if (sound == nullptr) {
		return (0U);
	}

	size_t read_cnt = (sound->ogg_file_buf_size_ - sound->ogg_file_buf_pos_) / size;

	if (read_cnt > cnt) {
		read_cnt = cnt;
	}

	memcpy(buf, &sound->ogg_file_buf_[sound->ogg_file_buf_pos_], size * read_cnt);

	sound->ogg_file_buf_pos_ += size * read_cnt;

	return (read_cnt);
}


/**
 * @brief SeekOggFile関数
 * @param src (source)
 * @param offset (offset)
 * @param flg (flag)
 * @return res (result)<br>
 * 0以外=失敗
 */
int tml::sound::Sound::SeekOggFile(void *src, ogg_int64_t offset, int flg)
{
	auto sound = reinterpret_cast<tml::sound::Sound *>(src);

	if (sound == nullptr) {
		return (-1);
	}

	switch (flg) {
	case SEEK_SET: {
		sound->ogg_file_buf_pos_ = static_cast<LONG>(offset);

		break;
	}
	case SEEK_CUR: {
		sound->ogg_file_buf_pos_ += static_cast<LONG>(offset);

		break;
	}
	case SEEK_END: {
		sound->ogg_file_buf_pos_ = sound->ogg_file_buf_size_ + static_cast<LONG>(offset);

		break;
	}
	default: {
		return (-1);
	}
	}

	if (sound->ogg_file_buf_pos_ < 0L) {
		sound->ogg_file_buf_pos_ = 0L;

		return (-1);
	} else if (sound->ogg_file_buf_pos_ > sound->ogg_file_buf_size_) {
		sound->ogg_file_buf_pos_ = sound->ogg_file_buf_size_;

		return (-1);
	}

	return (0);
}


/**
 * @brief CloseOggFile関数
 * @param src (source)
 * @return res (result)<br>
 * -1=失敗
 */
int tml::sound::Sound::CloseOggFile(void *src)
{
	return (0);
}


/**
 * @brief TellOggFile関数
 * @param src (source)
 * @return res (result)<br>
 * -1=失敗
 */
long tml::sound::Sound::TellOggFile(void *src)
{
	auto sound = reinterpret_cast<tml::sound::Sound *>(src);

	if (sound == nullptr) {
		return (-1L);
	}

	return (sound->ogg_file_buf_pos_);
}
