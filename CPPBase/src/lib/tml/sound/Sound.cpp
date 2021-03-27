/**
 * @file
 * @brief Soundコードファイル
 */


#include "Sound.h"
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
        if ((bin_file.data.file_buffer.GetLength() >= 4U)
        && (strncmp(reinterpret_cast<CHAR *>(bin_file.data.file_buffer.Get()), "RIFF", 4U) == 0)) {
            file_format = 1U;

            break;
        }

        if ((bin_file.data.file_buffer.GetLength() >= 3U)
        && (strncmp(reinterpret_cast<CHAR *>(bin_file.data.file_buffer.Get()), "ID3", 3U) == 0)) {
            file_format = 2U;

            break;
        }

        if ((bin_file.data.file_buffer.GetLength() >= 4U)
        && (strncmp(reinterpret_cast<CHAR *>(bin_file.data.file_buffer.Get()), "OggS", 4U) == 0)) {
            file_format = 3U;

            break;
        }
    } while (0);

	switch (file_format) {
	case 1: {
		break;
	}
	case 2: {
		break;
	}
	case 3: {
		break;
	}
	default: {
		return (-1);
	}
	}

	alGenBuffers(1, &this->buf_);

	alGenSources(1, &this->src_);

#if 0
    {
        ALenum err, format;
        ALuint buffer;
        SNDFILE *sndfile;
        SF_INFO sfinfo;
        short *membuf;
        sf_count_t num_frames;
        ALsizei num_bytes;

        /* Open the audio file and check that it's usable. */
        sndfile = sf_open(filename, SFM_READ, &sfinfo);
        if(!sndfile)
        {
            fprintf(stderr, "Could not open audio in %s: %s\n", filename, sf_strerror(sndfile));
            return 0;
        }
        if(sfinfo.frames < 1 || sfinfo.frames > (sf_count_t)(INT_MAX/sizeof(short))/sfinfo.channels)
        {
            fprintf(stderr, "Bad sample count in %s (%" PRId64 ")\n", filename, sfinfo.frames);
            sf_close(sndfile);
            return 0;
        }

        /* Get the sound format, and figure out the OpenAL format */
        format = AL_NONE;
        if(sfinfo.channels == 1)
            format = AL_FORMAT_MONO16;
        else if(sfinfo.channels == 2)
            format = AL_FORMAT_STEREO16;
        else if(sfinfo.channels == 3)
        {
            if(sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
                format = AL_FORMAT_BFORMAT2D_16;
        }
        else if(sfinfo.channels == 4)
        {
            if(sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
                format = AL_FORMAT_BFORMAT3D_16;
        }
        if(!format)
        {
            fprintf(stderr, "Unsupported channel count: %d\n", sfinfo.channels);
            sf_close(sndfile);
            return 0;
        }

        /* Decode the whole audio file to a buffer. */
        membuf = malloc((size_t)(sfinfo.frames * sfinfo.channels) * sizeof(short));

        num_frames = sf_readf_short(sndfile, membuf, sfinfo.frames);
        if(num_frames < 1)
        {
            free(membuf);
            sf_close(sndfile);
            fprintf(stderr, "Failed to read samples in %s (%" PRId64 ")\n", filename, num_frames);
            return 0;
        }
        num_bytes = (ALsizei)(num_frames * sfinfo.channels) * (ALsizei)sizeof(short);

        /* Buffer the audio data into a new buffer object, then free the data and
         * close the file.
         */
        buffer = 0;
        alGenBuffers(1, &buffer);
        alBufferData(buffer, format, membuf, num_bytes, sfinfo.samplerate);

        free(membuf);
        sf_close(sndfile);

        /* Check if an error occured, and clean up if so. */
        err = alGetError();
        if(err != AL_NO_ERROR)
        {
            fprintf(stderr, "OpenAL Error: %s\n", alGetString(err));
            if(buffer && alIsBuffer(buffer))
                alDeleteBuffers(1, &buffer);
            return 0;
        }

        return buffer;
    }

    {
        source = 0;
        alGenSources(1, &source);
        alSourcei(source, AL_BUFFER, (ALint)buffer);
        assert(alGetError()==AL_NO_ERROR && "Failed to setup sound source");
    }
#endif

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
