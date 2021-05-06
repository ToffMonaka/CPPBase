/**
 * @file
 * @brief ManagerResourceヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "../manager/ManagerResource.h"


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
class Object2DModelShaderStructuredBuffer;
class Object2DModelLayerShaderStructuredBuffer;
class Camera;
class Light;
class Fog;
class Mesh;
class Texture;
class Sampler;
class Model;
class ScreenModel;
class Object2DModel;
class Font;
}
}


namespace tml {
namespace graphic {
/**
 * @brief ManagerResourceDescクラス
 */
class ManagerResourceDesc : public tml::ManagerResourceDesc
{
public:
	tml::graphic::Manager *manager;

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	ManagerResourceDesc();
	virtual ~ManagerResourceDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::ManagerResourceDesc::Release(void)
{
	tml::ManagerResourceDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief ManagerResourceクラス
 *
 * インターフェースパターン
 */
class ManagerResource : public tml::ManagerResource
{
public: ManagerResource(const tml::graphic::ManagerResource &) = delete;
public: tml::graphic::ManagerResource &operator =(const tml::graphic::ManagerResource &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::graphic::Manager *mgr_;
	tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE res_type_;

protected:
	void Release(void);
	INT Create(const tml::graphic::ManagerResourceDesc &, const tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE, const UINT);

public:
	ManagerResource();
	virtual ~ManagerResource();

	virtual void Init(void);

	tml::graphic::Manager *GetManager(void);
	tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE GetResourceType(void) const;
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::ManagerResource::Release(void)
{
	tml::ManagerResource::Release();

	return;
}


/**
 * @brief GetManager関数
 * @return mgr (manager)
 */
inline tml::graphic::Manager *tml::graphic::ManagerResource::GetManager(void)
{
	return (this->mgr_);
}


/**
 * @brief GetResourceType関数
 * @return res_type (resource_type)
 */
inline tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE tml::graphic::ManagerResource::GetResourceType(void) const
{
	return (this->res_type_);
}
