/**
 * @file
 * @brief Shaderヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <list>
#include "../file/BinaryFile.h"
#include "GraphicResource.h"


namespace tml {
/**
 * @brief ShaderIncludeクラス
 */
class ShaderInclude : public ID3DInclude
{
public: ShaderInclude(const tml::ShaderInclude &) = delete;
public: tml::ShaderInclude &operator =(const tml::ShaderInclude &) = delete;

private:
	std::wstring dir_path_;

public:
	ShaderInclude();
	virtual ~ShaderInclude();

	virtual void Init(void);
	INT Create(const WCHAR *);

	HRESULT __stdcall Open(D3D_INCLUDE_TYPE, LPCSTR, LPCVOID, LPCVOID *, UINT *);
	HRESULT __stdcall Close(LPCVOID);
};
}


namespace tml {
/**
 * @brief ShaderDescクラス
 */
class ShaderDesc : public tml::GraphicResourceDesc
{
public:
	tml::BinaryFileReadPlan file_read_plan;
	tml::BinaryFileReadPlan *parent_file_read_plan;
	std::wstring include_directory_path;
	std::wstring vertex_function_name;
	std::wstring vertex_model_name;
	UINT vertex_input_element_desc_count;
	const D3D11_INPUT_ELEMENT_DESC *vertex_input_element_desc_array;
	std::wstring hull_function_name;
	std::wstring hull_model_name;
	std::wstring domain_function_name;
	std::wstring domain_model_name;
	std::wstring geometry_function_name;
	std::wstring geometry_model_name;
	std::wstring pixel_function_name;
	std::wstring pixel_model_name;
	std::wstring compute_function_name;
	std::wstring compute_model_name;
	std::list<std::pair<std::wstring, std::wstring>> macro_container;

public:
	ShaderDesc();
	virtual ~ShaderDesc();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief Shaderクラス
 */
class Shader : public tml::GraphicResource
{
public: Shader(const tml::Shader &) = delete;
public: tml::Shader &operator =(const tml::Shader &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	ID3D11VertexShader *vsh_;
	ID3D11InputLayout *vsh_input_layout_;
	ID3D11HullShader *hsh_;
	ID3D11DomainShader *dsh_;
	ID3D11GeometryShader *gsh_;
	ID3D11PixelShader *psh_;
	ID3D11ComputeShader *csh_;

private:
	void Release(void);

	ID3DBlob *GetBlob(tml::DynamicBuffer &, const WCHAR *, const WCHAR *, const WCHAR *, const D3D10_SHADER_MACRO *);
	void ReleaseBlob(ID3DBlob **);

public:
	Shader();
	virtual ~Shader();

	virtual void Init(void);
	INT Create(tml::ShaderDesc &);

	ID3D11VertexShader *GetVertex(void) const;
	ID3D11InputLayout *GetVertexInputLayout(void) const;
	ID3D11HullShader *GetHull(void) const;
	ID3D11DomainShader *GetDomain(void) const;
	ID3D11GeometryShader *GetGeometry(void) const;
	ID3D11PixelShader *GetPixel(void) const;
	ID3D11ComputeShader *GetCompute(void) const;
};
}


/**
 * @brief GetVertex関数
 * @return vsh (vertex_shader)
 */
inline ID3D11VertexShader *tml::Shader::GetVertex(void) const
{
	return (this->vsh_);
}


/**
 * @brief GetVertexInputLayout関数
 * @return vsh_input_layout (vertex_shader_input_layout)
 */
inline ID3D11InputLayout *tml::Shader::GetVertexInputLayout(void) const
{
	return (this->vsh_input_layout_);
}


/**
 * @brief GetHull関数
 * @return hsh (hull_shader)
 */
inline ID3D11HullShader *tml::Shader::GetHull(void) const
{
	return (this->hsh_);
}


/**
 * @brief GetDomain関数
 * @return dsh (domain_shader)
 */
inline ID3D11DomainShader *tml::Shader::GetDomain(void) const
{
	return (this->dsh_);
}


/**
 * @brief GetGeometry関数
 * @return gsh (geometry_shader)
 */
inline ID3D11GeometryShader *tml::Shader::GetGeometry(void) const
{
	return (this->gsh_);
}


/**
 * @brief GetPixel関数
 * @return psh (pixel_shader)
 */
inline ID3D11PixelShader *tml::Shader::GetPixel(void) const
{
	return (this->psh_);
}


/**
 * @brief GetCompute関数
 * @return csh (compute_shader)
 */
inline ID3D11ComputeShader *tml::Shader::GetCompute(void) const
{
	return (this->csh_);
}
