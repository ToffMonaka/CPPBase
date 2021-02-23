/**
 * @file
 * @brief Resourceヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "../file/INIFile.h"


namespace tml {
namespace graphic {
class Manager;
class RasterizerState;
class BlendState;
class DepthState;
class Shader;
class ShaderConstantBuffer;
class ConfigShaderConstantBuffer;
class HeaderShaderConstantBuffer;
class ShaderStructuredBuffer;
class CameraShaderStructuredBuffer;
class LightShaderStructuredBuffer;
class FogShaderStructuredBuffer;
class SpriteModelShaderStructuredBuffer;
class SpriteModelLayerShaderStructuredBuffer;
class Camera;
class Light;
class Fog;
class Mesh;
class Material;
class Texture;
class Sampler;
class Model;
class ScreenModel;
class SpriteModel;
class Font;
}
}


namespace tml {
namespace graphic {
/**
 * @brief ResourceDescクラス
 */
class ResourceDesc
{
public:
	tml::graphic::Manager *manager;
	std::wstring name;

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	ResourceDesc();
	virtual ~ResourceDesc();

	virtual void Init(void);

	INT Read(const tml::INIFileReadDesc &);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::ResourceDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Resourceクラス
 *
 * インターフェースパターン
 */
class Resource
{
public: Resource(const tml::graphic::Resource &) = delete;
public: tml::graphic::Resource &operator =(const tml::graphic::Resource &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE res_type_;
	tml::graphic::Manager *mgr_;
	std::wstring name_;

protected:
	void Release(void);
	INT Create(const tml::graphic::ResourceDesc &, const tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE);

public:
	Resource();
	virtual ~Resource();

	virtual void Init(void);

	tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE GetResourceType(void) const;
	tml::graphic::Manager *GetManager(void);
	const std::wstring &GetName(void) const;
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Resource::Release(void)
{
	return;
}


/**
 * @brief GetResourceType関数
 * @return res_type (resource_type)
 */
inline tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE tml::graphic::Resource::GetResourceType(void) const
{
	return (this->res_type_);
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::graphic::Manager *tml::graphic::Resource::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetName関数
 * @return name (name)
 */
inline const std::wstring &tml::graphic::Resource::GetName(void) const
{
	return (this->name_);
}
