/**
 * @file
 * @brief Mapヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../file/XMLFile.h"
#include "ManagerResource.h"


namespace tml {
namespace graphic {
/**
 * @brief MapDescクラス
 */
class MapDesc : public tml::graphic::ManagerResourceDesc
{
public:
	tml::XMLFileReadDesc map_file_read_desc;
	std::wstring map_directory_path;
	bool texture_flag;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	MapDesc();
	virtual ~MapDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::MapDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Mapクラス
 */
class Map : public tml::graphic::ManagerResource
{
public: Map(const tml::graphic::Map &) = delete;
public: tml::graphic::Map &operator =(const tml::graphic::Map &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT RESOURCE_MAIN_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::MAP);
	static const UINT RESOURCE_SUB_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::MAP_TYPE::BASE);

private:
	tml::shared_ptr<tml::graphic::Texture> tex_;

private:
	void Release(void);

public:
	Map();
	virtual ~Map();

	virtual void Init(void);
	INT Create(const tml::graphic::MapDesc &);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Map::Release(void)
{
	return;
}
