/**
 * @file
 * @brief Shaderヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ManagerResource.h"


namespace tml {
namespace graphic {
/**
 * @brief ShaderIncludeクラス
 */
class ShaderInclude : public ID3DInclude
{
public: ShaderInclude(const tml::graphic::ShaderInclude &) = delete;
public: tml::graphic::ShaderInclude &operator =(const tml::graphic::ShaderInclude &) = delete;

private:
	std::wstring dir_path_;

private:
	void Release(void);

public:
	ShaderInclude();
	virtual ~ShaderInclude();

	virtual void Init(void);
	INT Create(const WCHAR *);

	HRESULT __stdcall Open(D3D_INCLUDE_TYPE, LPCSTR, LPCVOID, LPCVOID *, UINT *);
	HRESULT __stdcall Close(LPCVOID);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::ShaderInclude::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief ShaderDescクラス
 */
class ShaderDesc : public tml::graphic::ManagerResourceDesc
{
public:
	tml::BinaryFileReadDesc shader_file_read_desc;
	std::wstring shader_directory_path;
	std::wstring vertex_shader_function_name;
	std::wstring vertex_shader_model_name;
	UINT vertex_shader_input_element_desc_count;
	const D3D11_INPUT_ELEMENT_DESC *vertex_shader_input_element_desc_array;
	std::wstring hull_shader_function_name;
	std::wstring hull_shader_model_name;
	std::wstring domain_shader_function_name;
	std::wstring domain_shader_model_name;
	std::wstring geometry_shader_function_name;
	std::wstring geometry_shader_model_name;
	std::wstring pixel_shader_function_name;
	std::wstring pixel_shader_model_name;
	std::wstring compute_shader_function_name;
	std::wstring compute_shader_model_name;
	std::list<std::pair<std::wstring, std::wstring>> macro_container;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	ShaderDesc();
	virtual ~ShaderDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::ShaderDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Shaderクラス
 */
class Shader : public tml::graphic::ManagerResource
{
public: Shader(const tml::graphic::Shader &) = delete;
public: tml::graphic::Shader &operator =(const tml::graphic::Shader &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT RESOURCE_TYPE = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::SHADER);

private:
	const tml::graphic::ShaderDesc *desc_;
	ID3D11VertexShader *vs_;
	ID3D11InputLayout *vs_input_layout_;
	ID3D11HullShader *hs_;
	ID3D11DomainShader *ds_;
	ID3D11GeometryShader *gs_;
	ID3D11PixelShader *ps_;
	ID3D11ComputeShader *cs_;

private:
	void Release(void);

	ID3DBlob *GetBlob(const tml::DynamicBuffer &, const WCHAR *, const WCHAR *, const WCHAR *, const D3D10_SHADER_MACRO *);
	void ReleaseBlob(ID3DBlob **);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);

public:
	Shader();
	virtual ~Shader();

	virtual void Init(void);

	const tml::graphic::ShaderDesc *GetDesc(void) const;
	ID3D11VertexShader *GetVertexShader(void);
	ID3D11InputLayout *GetVertexShaderInputLayout(void);
	ID3D11HullShader *GetHullShader(void);
	ID3D11DomainShader *GetDomainShader(void);
	ID3D11GeometryShader *GetGeometryShader(void);
	ID3D11PixelShader *GetPixelShader(void);
	ID3D11ComputeShader *GetComputeShader(void);
};
}
}


/**
 * @brief GetDesc関数
 * @return desc (desc)
 */
inline const tml::graphic::ShaderDesc *tml::graphic::Shader::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief GetVertexShader関数
 * @return vs (vertex_shader)
 */
inline ID3D11VertexShader *tml::graphic::Shader::GetVertexShader(void)
{
	return (this->vs_);
}


/**
 * @brief GetVertexShaderInputLayout関数
 * @return vs_input_layout (vertex_shader_input_layout)
 */
inline ID3D11InputLayout *tml::graphic::Shader::GetVertexShaderInputLayout(void)
{
	return (this->vs_input_layout_);
}


/**
 * @brief GetHullShader関数
 * @return hs (hull_shader)
 */
inline ID3D11HullShader *tml::graphic::Shader::GetHullShader(void)
{
	return (this->hs_);
}


/**
 * @brief GetDomainShader関数
 * @return ds (domain_shader)
 */
inline ID3D11DomainShader *tml::graphic::Shader::GetDomainShader(void)
{
	return (this->ds_);
}


/**
 * @brief GetGeometryShader関数
 * @return gs (geometry_shader)
 */
inline ID3D11GeometryShader *tml::graphic::Shader::GetGeometryShader(void)
{
	return (this->gs_);
}


/**
 * @brief GetPixelShader関数
 * @return ps (pixel_shader)
 */
inline ID3D11PixelShader *tml::graphic::Shader::GetPixelShader(void)
{
	return (this->ps_);
}


/**
 * @brief GetComputeShader関数
 * @return cs (compute_shader)
 */
inline ID3D11ComputeShader *tml::graphic::Shader::GetComputeShader(void)
{
	return (this->cs_);
}
