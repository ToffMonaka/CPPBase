/**
 * @file
 * @brief Soundヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantInclude_LibOggBase.h"
#include "ManagerResource.h"


namespace tml {
namespace sound {
/**
 * @brief SoundDescクラス
 */
class SoundDesc : public tml::sound::ManagerResourceDesc
{
public:
	tml::BinaryFileReadDesc file_read_desc;

private:
	void Release(void);

protected:
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
	return;
}


namespace tml {
namespace sound {
/**
 * @brief Soundクラス
 *
 * インターフェースパターン
 */
class Sound : public tml::sound::ManagerResource
{
public: Sound(const tml::sound::Sound &) = delete;
public: tml::sound::Sound &operator =(const tml::sound::Sound &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

public:
	static const UINT RESOURCE_MAIN_INDEX = static_cast<UINT>(tml::ConstantUtil::SOUND::RESOURCE_TYPE::SOUND);

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

private:
	void Release(void);
	void ReleaseDeferred(void);

protected:
	virtual INT OnCreateDeferred(void);

public:
	Sound();
	virtual ~Sound();

	virtual void Init(void);
	INT Create(const tml::sound::SoundDesc &);
	virtual void InitDeferred(void);

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
