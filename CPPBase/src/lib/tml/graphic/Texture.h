/**
 * @file
 * @brief Texture�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "GraphicResource.h"


namespace tml {
/**
 * @brief TextureDesc�N���X
 */
class TextureDesc : public tml::GraphicResourceDesc
{
public:

public:
	TextureDesc();
	virtual ~TextureDesc();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief Texture�N���X
 */
class Texture : public tml::GraphicResource
{
public: Texture(const tml::Texture &) = delete;
public: tml::Texture &operator =(const tml::Texture &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

private:
	void Release(void);

public:
	Texture();
	virtual ~Texture();

	virtual void Init(void);
	INT Create(const tml::TextureDesc &);
};
}
