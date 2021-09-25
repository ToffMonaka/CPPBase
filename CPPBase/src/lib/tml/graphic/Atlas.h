/**
 * @file
 * @brief Atlasヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../file/XMLFile.h"
#include "ManagerResource.h"


namespace tml {
namespace graphic {
/**
 * @brief AtlasDescクラス
 */
class AtlasDesc : public tml::graphic::ManagerResourceDesc
{
public:
	tml::XMLFileReadDesc atlas_file_read_desc;
	std::wstring atlas_directory_path;
	bool texture_flag;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	AtlasDesc();
	virtual ~AtlasDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::AtlasDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Atlasクラス
 */
class Atlas : public tml::graphic::ManagerResource
{
public: Atlas(const tml::graphic::Atlas &) = delete;
public: tml::graphic::Atlas &operator =(const tml::graphic::Atlas &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT RESOURCE_MAIN_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::ATLAS);
	static const UINT RESOURCE_SUB_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::ATLAS_TYPE::BASE);

private:
	tml::shared_ptr<tml::graphic::Texture> tex_;

private:
	void Release(void);

public:
	Atlas();
	virtual ~Atlas();

	virtual void Init(void);
	INT Create(const tml::graphic::AtlasDesc &);

	const tml::shared_ptr<tml::graphic::Texture> &GetTexture(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Atlas::Release(void)
{
	return;
}


/**
 * @brief GetTexture関数
 * @return tex (texture)
 */
inline const tml::shared_ptr<tml::graphic::Texture> &tml::graphic::Atlas::GetTexture(void)
{
	return (this->tex_);
}
