/**
 * @file
 * @brief Shader�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <list>
#include "../file/BinaryFile.h"
#include "GraphicResource.h"


namespace tml {
/**
 * @brief ShaderInclude�N���X
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
 * @brief ShaderDesc�N���X
 */
class ShaderDesc : public tml::GraphicResourceDesc
{
public:
	tml::BinaryFileReadPlan file_read_plan;
	std::wstring include_directory_path;
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

public:
	ShaderDesc();
	virtual ~ShaderDesc();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief Shader�N���X
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

	ID3D11VertexShader *GetVertexShader(void) const;
	ID3D11InputLayout *GetVertexShaderInputLayout(void) const;
	ID3D11HullShader *GetHullShader(void) const;
	ID3D11DomainShader *GetDomainShader(void) const;
	ID3D11GeometryShader *GetGeometryShader(void) const;
	ID3D11PixelShader *GetPixelShader(void) const;
	ID3D11ComputeShader *GetComputeShader(void) const;
};
}


/**
 * @brief GetVertexShader�֐�
 * @return vsh (vertex_shader)
 */
inline ID3D11VertexShader *tml::Shader::GetVertexShader(void) const
{
	return (this->vsh_);
}


/**
 * @brief GetVertexShaderInputLayout�֐�
 * @return vsh_input_layout (vertex_shader_input_layout)
 */
inline ID3D11InputLayout *tml::Shader::GetVertexShaderInputLayout(void) const
{
	return (this->vsh_input_layout_);
}


/**
 * @brief GetHullShader�֐�
 * @return hsh (hull_shader)
 */
inline ID3D11HullShader *tml::Shader::GetHullShader(void) const
{
	return (this->hsh_);
}


/**
 * @brief GetDomainShader�֐�
 * @return dsh (domain_shader)
 */
inline ID3D11DomainShader *tml::Shader::GetDomainShader(void) const
{
	return (this->dsh_);
}


/**
 * @brief GetGeometryShader�֐�
 * @return gsh (geometry_shader)
 */
inline ID3D11GeometryShader *tml::Shader::GetGeometryShader(void) const
{
	return (this->gsh_);
}


/**
 * @brief GetPixelShader�֐�
 * @return psh (pixel_shader)
 */
inline ID3D11PixelShader *tml::Shader::GetPixelShader(void) const
{
	return (this->psh_);
}


/**
 * @brief GetComputeShader�֐�
 * @return csh (compute_shader)
 */
inline ID3D11ComputeShader *tml::Shader::GetComputeShader(void) const
{
	return (this->csh_);
}
