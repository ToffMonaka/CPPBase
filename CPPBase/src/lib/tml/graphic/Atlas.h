/**
 * @file
 * @brief Atlasヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <map>
#include "../math/XNAMathVector.h"
#include "../file/XMLFile.h"
#include "ManagerResource.h"


namespace tml {
namespace graphic {
class Atlas;
}
}


namespace tml {
namespace graphic {
/**
 * @brief AtlasRectクラス
 */
class AtlasRect
{
friend class tml::graphic::Atlas;

private:
	std::wstring name_;
	tml::XMUINT2EX pos_;
	tml::XMUINT2EX size_;

private:
	void Release(void);

public:
	AtlasRect();
	virtual ~AtlasRect();

	virtual void Init(void);
	INT Create(const WCHAR *, const tml::XMUINT2EX &, const tml::XMUINT2EX &);

	const std::wstring &GetName(void) const;
	const tml::XMUINT2EX &GetPosition(void) const;
	const tml::XMUINT2EX &GetSize(void) const;
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::AtlasRect::Release(void)
{
	return;
}


/**
 * @brief GetName関数
 * @return name (name)
 */
inline const std::wstring &tml::graphic::AtlasRect::GetName(void) const
{
	return (this->name_);
}


/**
 * @brief GetPosition関数
 * @return pos (position)
 */
inline const tml::XMUINT2EX &tml::graphic::AtlasRect::GetPosition(void) const
{
	return (this->pos_);
}


/**
 * @brief GetSize関数
 * @return size (size)
 */
inline const tml::XMUINT2EX &tml::graphic::AtlasRect::GetSize(void) const
{
	return (this->size_);
}


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
	static const UINT RESOURCE_TYPE = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::ATLAS);

private:
	const tml::graphic::AtlasDesc *desc_;
	std::map<std::wstring, tml::graphic::AtlasRect> rect_cont_;
	tml::shared_ptr<tml::graphic::Texture> tex_;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);

public:
	Atlas();
	virtual ~Atlas();

	virtual void Init(void);

	const tml::graphic::AtlasDesc *GetDesc(void) const;
	const tml::graphic::AtlasRect *GetRect(const WCHAR *) const;
	const tml::shared_ptr<tml::graphic::Texture> &GetTexture(void);
};
}
}


/**
 * @brief GetDesc関数
 * @return desc (desc)
 */
inline const tml::graphic::AtlasDesc *tml::graphic::Atlas::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief GetRect関数
 * @param rect_name (rect_name)
 * @return rect (rect)<br>
 * nullptr=失敗
 */
inline const tml::graphic::AtlasRect *tml::graphic::Atlas::GetRect(const WCHAR *rect_name) const
{
	auto rect_itr = this->rect_cont_.find(rect_name);

	if (rect_itr == this->rect_cont_.end()) {
		return (nullptr);
	}

	return (&rect_itr->second);
}


/**
 * @brief GetTexture関数
 * @return tex (texture)
 */
inline const tml::shared_ptr<tml::graphic::Texture> &tml::graphic::Atlas::GetTexture(void)
{
	return (this->tex_);
}
