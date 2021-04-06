/**
 * @file
 * @brief Soundヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantInclude_LibOggBase.h"
#include "Resource.h"


namespace tml {
namespace sound {
/**
 * @brief SoundDescクラス
 */
class SoundDesc : public tml::sound::ResourceDesc
{
public:
	tml::BinaryFileReadDesc file_read_desc;

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	SoundDesc();
	virtual ~SoundDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::sound::SoundDesc::Release(void)
{
	tml::sound::ResourceDesc::Release();

	return;
}


namespace tml {
namespace sound {
/**
 * @brief Soundクラス
 *
 * インターフェースパターン
 */
class Sound : public tml::sound::Resource
{
public: Sound(const tml::sound::Sound &) = delete;
public: tml::sound::Sound &operator =(const tml::sound::Sound &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::ConstantUtil::SOUND::SOUND_TYPE type_;
	ALuint buf_;
	ALuint src_;

	BYTE *ogg_file_buf_;
	LONG ogg_file_buf_size_;
	LONG ogg_file_buf_index_;

private:
	static size_t ReadOggFile(void *, size_t, size_t, void *);
	static int SeekOggFile(void *, ogg_int64_t, int);
	static int CloseOggFile(void *);
	static long TellOggFile(void *);

protected:
	void Release(void);
	INT Create(const tml::sound::SoundDesc &, const tml::ConstantUtil::SOUND::SOUND_TYPE);

public:
	Sound();
	virtual ~Sound();

	virtual void Init(void);

	tml::ConstantUtil::SOUND::SOUND_TYPE GetType(void) const;
	ALuint GetBuffer(void) const;
	ALuint GetSource(void) const;
};
}
}


/**
 * @brief GetType関数
 * @return type (type)
 */
inline tml::ConstantUtil::SOUND::SOUND_TYPE tml::sound::Sound::GetType(void) const
{
	return (this->type_);
}


/**
 * @brief GetBuffer関数
 * @return buf (buffer)
 */
inline ALuint tml::sound::Sound::GetBuffer(void) const
{
	return (this->buf_);
}


/**
 * @brief GetSource関数
 * @return src (source)
 */
inline ALuint tml::sound::Sound::GetSource(void) const
{
	return (this->src_);
}
