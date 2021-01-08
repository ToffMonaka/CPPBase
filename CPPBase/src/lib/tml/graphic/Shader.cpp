/**
 * @file
 * @brief Shaderコードファイル
 */


#include "Shader.h"
#include "../string/StringUtil.h"
#include "GraphicManager.h"


/**
 * @brief コンストラクタ
 */
tml::ShaderInclude::ShaderInclude()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::ShaderInclude::~ShaderInclude()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::ShaderInclude::Init(void)
{
	this->dir_path_.clear();

	return;
}


/**
 * @brief Create関数
 * @param dir_path (directory_path)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::ShaderInclude::Create(const WCHAR *dir_path)
{
	this->Init();

	this->dir_path_ = dir_path;

	return (0);
}


/**
 * @brief Open関数
 * @param inc_type (include_type)
 * @param file_name (file_name)
 * @param parent_dat (parent_data)
 * @param dst_dat (dst_data)
 * @param dst_dat_len (dst_data_length)
 * @return res (result)<br>
 * 0未満=失敗
 */
HRESULT __stdcall tml::ShaderInclude::Open(D3D_INCLUDE_TYPE inc_type, LPCSTR file_name, LPCVOID parent_dat, LPCVOID *dst_dat, UINT *dst_dat_len)
{
	tml::BinaryFile bin_file;
	std::wstring bin_file_name;

	bin_file.read_plan.file_path = this->dir_path_;
	bin_file.read_plan.file_path += L"/";
	bin_file.read_plan.file_path += tml::StringUtil::GetString(bin_file_name, file_name);

	if (bin_file.Read()) {
		return (E_FAIL);
	}

	(*dst_dat) = bin_file.data.file_buffer.Get();
	(*dst_dat_len) = bin_file.data.file_buffer.GetLength();

	bin_file.data.file_buffer.Clear();

	return (S_OK);
}


/**
 * @brief Close関数
 * @param dat (data)
 * @return res (result)<br>
 * 0未満=失敗
 */
HRESULT __stdcall tml::ShaderInclude::Close(LPCVOID dat)
{
	auto file_buf = reinterpret_cast<BYTE *>(const_cast<LPVOID>(dat));

	tml::MemoryUtil::Release(&file_buf);

	return (S_OK);
}


/**
 * @brief コンストラクタ
 */
tml::ShaderDesc::ShaderDesc() :
	file_parent_read_plan(nullptr),
	vertex_shader_input_element_desc_count(0U),
	vertex_shader_input_element_desc_array(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::ShaderDesc::~ShaderDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::ShaderDesc::Init(void)
{
	this->file_read_plan.Init();
	this->file_parent_read_plan = nullptr;
	this->include_directory_path.clear();
	this->vertex_shader_function_name.clear();
	this->vertex_shader_model_name.clear();
	this->vertex_shader_input_element_desc_count = 0U;
	this->vertex_shader_input_element_desc_array = nullptr;
	this->hull_shader_function_name.clear();
	this->hull_shader_model_name.clear();
	this->domain_shader_function_name.clear();
	this->domain_shader_model_name.clear();
	this->geometry_shader_function_name.clear();
	this->geometry_shader_model_name.clear();
	this->pixel_shader_function_name.clear();
	this->pixel_shader_model_name.clear();
	this->compute_shader_function_name.clear();
	this->compute_shader_model_name.clear();
	this->macro_container.clear();

	tml::GraphicResourceDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::Shader::Shader() :
	vsh_(nullptr),
	vsh_input_layout_(nullptr),
	hsh_(nullptr),
	dsh_(nullptr),
	gsh_(nullptr),
	psh_(nullptr),
	csh_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::Shader::~Shader()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::Shader::Release(void)
{
	if (this->csh_ != nullptr) {
		this->csh_->Release();

		this->csh_ = nullptr;
	}

	if (this->psh_ != nullptr) {
		this->psh_->Release();

		this->psh_ = nullptr;
	}

	if (this->gsh_ != nullptr) {
		this->gsh_->Release();

		this->gsh_ = nullptr;
	}

	if (this->dsh_ != nullptr) {
		this->dsh_->Release();

		this->dsh_ = nullptr;
	}

	if (this->hsh_ != nullptr) {
		this->hsh_->Release();

		this->hsh_ = nullptr;
	}

	if (this->vsh_input_layout_ != nullptr) {
		this->vsh_input_layout_->Release();

		this->vsh_input_layout_ = nullptr;
	}

	if (this->vsh_ != nullptr) {
		this->vsh_->Release();

		this->vsh_ = nullptr;
	}

	tml::GraphicResource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::Shader::Init(void)
{
	this->Release();

	tml::GraphicResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::Shader::Create(tml::ShaderDesc &desc)
{
	this->Init();

	if (tml::GraphicResource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	auto file_read_plan = (desc.file_parent_read_plan != nullptr) ? desc.file_parent_read_plan : &desc.file_read_plan;

	tml::BinaryFile bin_file;

	bin_file.parent_read_plan = file_read_plan;

	if (bin_file.Read()) {
		this->Init();

		return (-1);
	}

	if (bin_file.data.file_buffer.GetSize() <= 0U) {
		this->Init();

		return (-1);
	}

	std::vector<D3D10_SHADER_MACRO> macro_ary;
	std::vector<std::string> macro_name_ary;
	std::vector<std::string> macro_val_ary;

	if (desc.macro_container.size() > 0U) {
		macro_ary.resize(desc.macro_container.size() + 1U);
		macro_name_ary.resize(desc.macro_container.size());
		macro_val_ary.resize(desc.macro_container.size());

		UINT macro_i = 0U;

		for (auto &macro : desc.macro_container) {
			tml::StringUtil::GetString(macro_name_ary[macro_i], macro.first.c_str());
			tml::StringUtil::GetString(macro_val_ary[macro_i], macro.second.c_str());

			macro_ary[macro_i].Name = macro_name_ary[macro_i].c_str();
			macro_ary[macro_i].Definition = macro_val_ary[macro_i].c_str();

			++macro_i;
		}

		macro_ary[macro_i].Name = nullptr;
		macro_ary[macro_i].Definition = nullptr;
	}

	if (!desc.vertex_shader_function_name.empty()) {
		auto blob = this->GetBlob(bin_file.data.file_buffer, desc.include_directory_path.c_str(), desc.vertex_shader_function_name.c_str(), desc.vertex_shader_model_name.c_str(), macro_ary.data());

		if (blob == nullptr) {
			this->Init();

			return (-1);
		}

		if (FAILED(this->GetManager()->GetDevice()->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &this->vsh_))) {
			this->ReleaseBlob(&blob);

			this->Init();

			return (-1);
		}

		if (FAILED(this->GetManager()->GetDevice()->CreateInputLayout(desc.vertex_shader_input_element_desc_array, desc.vertex_shader_input_element_desc_count, blob->GetBufferPointer(), blob->GetBufferSize(), &this->vsh_input_layout_))) {
			this->ReleaseBlob(&blob);

			this->Init();

			return (-1);
		}

		this->ReleaseBlob(&blob);
	}

	if (!desc.hull_shader_function_name.empty()) {
		auto blob = this->GetBlob(bin_file.data.file_buffer, desc.include_directory_path.c_str(), desc.hull_shader_function_name.c_str(), desc.hull_shader_model_name.c_str(), macro_ary.data());

		if (blob == nullptr) {
			this->Init();

			return (-1);
		}

		if (FAILED(this->GetManager()->GetDevice()->CreateHullShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &this->hsh_))) {
			this->ReleaseBlob(&blob);

			this->Init();

			return (-1);
		}

		this->ReleaseBlob(&blob);
	}

	if (!desc.domain_shader_function_name.empty()) {
		auto blob = this->GetBlob(bin_file.data.file_buffer, desc.include_directory_path.c_str(), desc.domain_shader_function_name.c_str(), desc.domain_shader_model_name.c_str(), macro_ary.data());

		if (blob == nullptr) {
			this->Init();

			return (-1);
		}

		if (FAILED(this->GetManager()->GetDevice()->CreateDomainShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &this->dsh_))) {
			this->ReleaseBlob(&blob);

			this->Init();

			return (-1);
		}

		this->ReleaseBlob(&blob);
	}

	if (!desc.geometry_shader_function_name.empty()) {
		auto blob = this->GetBlob(bin_file.data.file_buffer, desc.include_directory_path.c_str(), desc.geometry_shader_function_name.c_str(), desc.geometry_shader_model_name.c_str(), macro_ary.data());

		if (blob == nullptr) {
			this->Init();

			return (-1);
		}

		if (FAILED(this->GetManager()->GetDevice()->CreateGeometryShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &this->gsh_))) {
			this->ReleaseBlob(&blob);

			this->Init();

			return (-1);
		}

		this->ReleaseBlob(&blob);
	}

	if (!desc.pixel_shader_function_name.empty()) {
		auto blob = this->GetBlob(bin_file.data.file_buffer, desc.include_directory_path.c_str(), desc.pixel_shader_function_name.c_str(), desc.pixel_shader_model_name.c_str(), macro_ary.data());

		if (blob == nullptr) {
			this->Init();

			return (-1);
		}

		if (FAILED(this->GetManager()->GetDevice()->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &this->psh_))) {
			this->ReleaseBlob(&blob);

			this->Init();

			return (-1);
		}

		this->ReleaseBlob(&blob);
	}

	if (!desc.compute_shader_function_name.empty()) {
		auto blob = this->GetBlob(bin_file.data.file_buffer, desc.include_directory_path.c_str(), desc.compute_shader_function_name.c_str(), desc.compute_shader_model_name.c_str(), macro_ary.data());

		if (blob == nullptr) {
			this->Init();

			return (-1);
		}

		if (FAILED(this->GetManager()->GetDevice()->CreateComputeShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &this->csh_))) {
			this->ReleaseBlob(&blob);

			this->Init();

			return (-1);
		}

		this->ReleaseBlob(&blob);
	}

	return (0);
}


/**
 * @brief GetBlob関数
 * @param file_buf (file_buf)
 * @param inc_dir_path (include_directory_path)
 * @param func_name (function_name)
 * @param model_name (model_name)
 * @param macro_ary (macro_array)<br>
 * nullptr=指定無し
 * @return blob (blob)<br>
 * nullptr=失敗
 */
ID3DBlob *tml::Shader::GetBlob(tml::DynamicBuffer &file_buf, const WCHAR *inc_dir_path, const WCHAR *func_name, const WCHAR *model_name, const D3D10_SHADER_MACRO *macro_ary)
{
	tml::ShaderInclude inc;

	if (inc.Create(inc_dir_path) < 0) {
		return (nullptr);
	}

	std::string tmp_func_name;
	std::string tmp_model_name;

	tml::StringUtil::GetString(tmp_func_name, func_name);
	tml::StringUtil::GetString(tmp_model_name, model_name);

	UINT compile_flg = 0U;

	if (tml::ConstantUtil::LIBRARY::DEBUG_FLAG) {
		compile_flg = D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR | D3D10_SHADER_OPTIMIZATION_LEVEL0 | D3D10_SHADER_DEBUG;
	} else {
		compile_flg = D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR | D3D10_SHADER_OPTIMIZATION_LEVEL3;
	}

	ID3DBlob *blob = nullptr;
	ID3DBlob *err_blob = nullptr;

	if (FAILED(D3DX11CompileFromMemory(reinterpret_cast<LPCSTR>(file_buf.Get()), file_buf.GetLength(), nullptr, macro_ary, &inc, tmp_func_name.c_str(), tmp_model_name.c_str(), compile_flg, 0U, nullptr, &blob, &err_blob, nullptr))) {
		this->ReleaseBlob(&err_blob);

		return (nullptr);
	}

	this->ReleaseBlob(&err_blob);

	return (blob);
}


/**
 * @brief ReleaseBlob関数
 * @param blob (blob)
 */
void tml::Shader::ReleaseBlob(ID3DBlob **blob)
{
	if ((*blob) == nullptr) {
		return;
	}

	(*blob)->Release();

	(*blob) = nullptr;

	return;
}
