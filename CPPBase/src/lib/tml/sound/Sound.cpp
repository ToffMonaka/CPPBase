/**
 * @file
 * @brief Soundコードファイル
 */


#include "Sound.h"
#include <mmsystem.h>
#include <mmreg.h>
#include <msacm.h>
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

	tml::sound::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::sound::SoundDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::sound::ManagerResourceDesc::ReadValue(ini_file) < 0) {
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
	ogg_file_buf_index_(0L)
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

	tml::sound::ManagerResource::Release();

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
	this->ogg_file_buf_index_ = 0L;

	tml::sound::ManagerResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @param type (type)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::sound::Sound::Create(const tml::sound::SoundDesc &desc, const tml::ConstantUtil::SOUND::SOUND_TYPE type)
{
	if (type == tml::ConstantUtil::SOUND::SOUND_TYPE::NONE) {
		return (-1);
	}

	if (tml::sound::ManagerResource::Create(desc, tml::ConstantUtil::SOUND::RESOURCE_TYPE::SOUND, static_cast<UINT>(type)) < 0) {
		return (-1);
	}

	this->type_ = type;

	auto file_read_desc_dat = desc.file_read_desc.GetDataByParent();

	tml::BinaryFile bin_file;

	bin_file.read_desc.parent_data = file_read_desc_dat;

	if (bin_file.Read() < 0) {
		return (-1);
	}

	auto &bin_file_buf = bin_file.data.buffer;

	if (bin_file_buf.GetLength() <= 0U) {
		return (-1);
	}

	tml::DynamicBuffer buf;
	ALenum buf_format = AL_NONE;
	ALsizei buf_sampling_rate = 0;

	UINT file_format = 0U;

	do {
		// Check WAVE File
		if ((bin_file_buf.GetLength() >= 4U)
		&& (strncmp(reinterpret_cast<CHAR *>(bin_file_buf.Get()), "RIFF", 4U) == 0)) {
			file_format = 1U;

			break;
		}

		// Check MP3 File
		if ((bin_file_buf.GetLength() >= 3U)
		&& (strncmp(reinterpret_cast<CHAR *>(bin_file_buf.Get()), "ID3", 3U) == 0)) {
			file_format = 2U;

			break;
		}

		// Check Ogg File
		if ((bin_file_buf.GetLength() >= 4U)
		&& (strncmp(reinterpret_cast<CHAR *>(bin_file_buf.Get()), "OggS", 4U) == 0)) {
			file_format = 3U;

			break;
		}
	} while (0);

	switch (file_format) {
	case 1: {// Read WAVE File
		MMIOINFO mmio_info = {};

		mmio_info.fccIOProc = FOURCC_MEM;
		mmio_info.cchBuffer = bin_file_buf.GetLength();
		mmio_info.pchBuffer = reinterpret_cast<HPSTR>(bin_file_buf.Get());

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

		buf.SetSize(dat_mmck_info.cksize);
		buf.AddWriteIndex(buf.GetSize());

		if (mmioRead(mmio_handle, reinterpret_cast<HPSTR>(buf.Get()), buf.GetLength()) != buf.GetLength()) {
			mmioClose(mmio_handle, 0U);

			return (-1);
		}

		mmioClose(mmio_handle, 0U);

		if (wav_format.nChannels == 1) {
			buf_format = AL_FORMAT_MONO16;
		} else if (wav_format.nChannels == 2) {
			buf_format = AL_FORMAT_STEREO16;
		} else {
			return (-1);
		}

		buf_sampling_rate = wav_format.nSamplesPerSec;

		break;
	}
	case 2: {// Read MP3 File
		if ((bin_file_buf.GetLength() >= 128U)
		&& (strncmp(reinterpret_cast<CHAR *>(&bin_file_buf.Get()[bin_file_buf.GetLength() - 128U]), "TAG", 3U) == 0)) {
			bin_file_buf.SetLength(bin_file_buf.GetLength() - 128U);
		}

		size_t bin_file_buf_index = 0U;

		std::array<BYTE, 10U> mp3_tag_header;

		if (bin_file_buf.GetLength() < (bin_file_buf_index + mp3_tag_header.size())) {
			return (-1);
		}

		tml::Copy(mp3_tag_header.data(), &bin_file_buf.Get()[bin_file_buf_index], mp3_tag_header.size());

		size_t mp3_tag_size = ((mp3_tag_header[6] << 21) | (mp3_tag_header[7] << 14) | (mp3_tag_header[8] << 7) | mp3_tag_header[9]) + mp3_tag_header.size();

		if (bin_file_buf.GetLength() < (bin_file_buf_index + mp3_tag_size)) {
			return (-1);
		}

		bin_file_buf_index += mp3_tag_size;

		std::array<BYTE, 4U> mp3_frame_header;

		if (bin_file_buf.GetLength() < (bin_file_buf_index + mp3_frame_header.size())) {
			return (-1);
		}

		tml::Copy(mp3_frame_header.data(), &bin_file_buf.Get()[bin_file_buf_index], mp3_frame_header.size());

		if (!((mp3_frame_header[0] == 0xFF) && ((mp3_frame_header[1] & 0xE0) == 0xE0))) {
			return (-1);
		}

		BYTE mp3_version_code = (mp3_frame_header[1] >> 3) & 0x03;
		BYTE mp3_version = 0;

		if (mp3_version_code == 3) {
			mp3_version = 1;
		} else if (mp3_version_code == 2) {
			mp3_version = 2;
		} else {
			return (-1);
		}

		BYTE mp3_layer_code = (mp3_frame_header[1] >> 1) & 0x03;
		BYTE mp3_layer = 0;

		if (mp3_layer_code == 1) {
			mp3_layer = 3;
		} else {
			return (-1);
		}

		const DWORD mp3_bit_rate_tbl[][16] = {
			{0, 32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, static_cast<DWORD>(-1)}, // MPEG1 Layer3
			{0, 8, 16, 24, 32, 40, 48, 56, 64, 80, 96, 112, 128, 144, 160, static_cast<DWORD>(-1)} // MPEG2 Layer3
		};
		BYTE mp3_bit_rate_code = (mp3_frame_header[2] >> 4) & 0x0F;
		DWORD mp3_bit_rate = mp3_bit_rate_tbl[mp3_version - 1][mp3_bit_rate_code];

		const DWORD mp3_sampling_rate_tbl[][4] = {
			{44100, 48000, 32000, static_cast<DWORD>(-1)}, // MPEG1
			{22050, 24000, 16000, static_cast<DWORD>(-1)} // MPEG2
		};
		BYTE mp3_sampling_rate_code = (mp3_frame_header[2] >> 2) & 0x03;
		DWORD mp3_sampling_rate = mp3_sampling_rate_tbl[mp3_version - 1][mp3_sampling_rate_code];

		BYTE mp3_padding = (mp3_frame_header[2] >> 1) & 0x01;
		BYTE mp3_channel = (mp3_frame_header[3] >> 6) & 0x03;

		MPEGLAYER3WAVEFORMAT mp3_format = {};

		mp3_format.wfx.wFormatTag = WAVE_FORMAT_MPEGLAYER3;
		mp3_format.wfx.nChannels = (mp3_channel == 3) ? 1 : 2;
		mp3_format.wfx.nSamplesPerSec = mp3_sampling_rate;
		mp3_format.wfx.nAvgBytesPerSec = (mp3_bit_rate * 1000) / 8;
		mp3_format.wfx.nBlockAlign = 1;
		mp3_format.wfx.wBitsPerSample = 0;
		mp3_format.wfx.cbSize = MPEGLAYER3_WFX_EXTRA_BYTES;
		mp3_format.wID = MPEGLAYER3_ID_MPEG;
		mp3_format.fdwFlags = (mp3_padding) ? MPEGLAYER3_FLAG_PADDING_ON : MPEGLAYER3_FLAG_PADDING_OFF;
		mp3_format.nBlockSize = static_cast<WORD>((144 * mp3_bit_rate * 1000) / mp3_sampling_rate) + mp3_padding;
		mp3_format.nFramesPerBlock = 1;
		mp3_format.nCodecDelay = 1393;

		WAVEFORMATEX wav_format = {};

		wav_format.wFormatTag = WAVE_FORMAT_PCM;

		if (acmFormatSuggest(nullptr, &mp3_format.wfx, &wav_format, sizeof(WAVEFORMATEX), ACM_FORMATSUGGESTF_WFORMATTAG) != 0) {
			return (-1);
		}

		HACMSTREAM acm_stream_handle = nullptr;

		if (acmStreamOpen(&acm_stream_handle, nullptr, &mp3_format.wfx, &wav_format, nullptr, 0, 0, ACM_STREAMOPENF_NONREALTIME) != 0) {
			return (-1);
		}

		DWORD mp3_buf_size = bin_file_buf.GetLength() - bin_file_buf_index;
		DWORD wav_buf_size = 0UL;

		if (acmStreamSize(acm_stream_handle, mp3_buf_size, &wav_buf_size, ACM_STREAMSIZEF_SOURCE) != 0) {
			acmStreamClose(acm_stream_handle, 0UL);

			return (-1);
		}

		buf.SetSize(wav_buf_size);
		buf.AddWriteIndex(buf.GetSize());

		ACMSTREAMHEADER acm_stream_header = {};

		acm_stream_header.cbStruct = sizeof(ACMSTREAMHEADER);
		acm_stream_header.pbSrc = &bin_file_buf.Get()[bin_file_buf_index];
		acm_stream_header.cbSrcLength = mp3_buf_size;
		acm_stream_header.pbDst = &buf.Get()[0];
		acm_stream_header.cbDstLength = wav_buf_size;

		if (acmStreamPrepareHeader(acm_stream_handle, &acm_stream_header, 0UL) != 0) {
			acmStreamClose(acm_stream_handle, 0UL);

			return (-1);
		}

		if (acmStreamConvert(acm_stream_handle, &acm_stream_header, ACM_STREAMCONVERTF_BLOCKALIGN) != 0) {
			acmStreamUnprepareHeader(acm_stream_handle, &acm_stream_header, 0UL);
			acmStreamClose(acm_stream_handle, 0UL);

			return (-1);
		}

		buf.SetLength(acm_stream_header.cbDstLengthUsed);

		acmStreamUnprepareHeader(acm_stream_handle, &acm_stream_header, 0UL);
		acmStreamClose(acm_stream_handle, 0UL);

		if (wav_format.nChannels == 1) {
			buf_format = AL_FORMAT_MONO16;
		} else if (wav_format.nChannels == 2) {
			buf_format = AL_FORMAT_STEREO16;
		} else {
			return (-1);
		}

		buf_sampling_rate = wav_format.nSamplesPerSec;

		break;
	}
	case 3: {// Read Ogg File
		this->ogg_file_buf_ = bin_file_buf.Get();
		this->ogg_file_buf_size_ = bin_file_buf.GetLength();
		this->ogg_file_buf_index_ = 0L;

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

		buf.SetSize(static_cast<size_t>(ov_pcm_total(&ogg_file, -1) * ogg_info->channels * 2));
		buf.AddWriteIndex(buf.GetSize());

		LONG read_size = 0L;
		INT read_result = 0;
		INT read_bitstream = 0;
 
		while (read_size < static_cast<LONG>(buf.GetLength())) {
			LONG tmp_read_size = ov_read(&ogg_file, reinterpret_cast<CHAR *>(&buf.Get()[read_size]), static_cast<LONG>(buf.GetLength()) - read_size, 0, 2, 1, &read_bitstream);
 
			if (tmp_read_size < 0L) {
				read_result = -1;

				break;
			} else if (tmp_read_size == 0L) {
				break;
			}
 
			read_size += tmp_read_size;
		}

		if (read_result < 0) {
			ov_clear(&ogg_file);

			return (-1);
		}

		ov_clear(&ogg_file);

		if (wav_format.nChannels == 1) {
			buf_format = AL_FORMAT_MONO16;
		} else if (wav_format.nChannels == 2) {
			buf_format = AL_FORMAT_STEREO16;
		} else {
			return (-1);
		}

		buf_sampling_rate = wav_format.nSamplesPerSec;

		break;
	}
	default: {
		return (-1);
	}
	}

	alGenBuffers(1, &this->buf_);
	alBufferData(this->buf_, buf_format, buf.Get(), buf.GetLength(), buf_sampling_rate);

	if (alGetError() != AL_NO_ERROR) {
		return (-1);
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

	size_t read_cnt = (sound->ogg_file_buf_size_ - sound->ogg_file_buf_index_) / size;

	if (read_cnt > cnt) {
		read_cnt = cnt;
	}

	memcpy(buf, &sound->ogg_file_buf_[sound->ogg_file_buf_index_], size * read_cnt);

	sound->ogg_file_buf_index_ += size * read_cnt;

	return (read_cnt);
}


/**
 * @brief SeekOggFile関数
 * @param src (source)
 * @param offset (offset)
 * @param flg (flag)
 * @return result (result)<br>
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
		sound->ogg_file_buf_index_ = static_cast<LONG>(offset);

		break;
	}
	case SEEK_CUR: {
		sound->ogg_file_buf_index_ += static_cast<LONG>(offset);

		break;
	}
	case SEEK_END: {
		sound->ogg_file_buf_index_ = sound->ogg_file_buf_size_ + static_cast<LONG>(offset);

		break;
	}
	default: {
		return (-1);
	}
	}

	if (sound->ogg_file_buf_index_ < 0L) {
		sound->ogg_file_buf_index_ = 0L;

		return (-1);
	} else if (sound->ogg_file_buf_index_ > sound->ogg_file_buf_size_) {
		sound->ogg_file_buf_index_ = sound->ogg_file_buf_size_;

		return (-1);
	}

	return (0);
}


/**
 * @brief CloseOggFile関数
 * @param src (source)
 * @return result (result)<br>
 * -1=失敗
 */
int tml::sound::Sound::CloseOggFile(void *src)
{
	return (0);
}


/**
 * @brief TellOggFile関数
 * @param src (source)
 * @return result (result)<br>
 * -1=失敗
 */
long tml::sound::Sound::TellOggFile(void *src)
{
	auto sound = reinterpret_cast<tml::sound::Sound *>(src);

	if (sound == nullptr) {
		return (-1L);
	}

	return (sound->ogg_file_buf_index_);
}
