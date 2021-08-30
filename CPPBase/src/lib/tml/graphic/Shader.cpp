/**
 * @file
 * @brief Shaderコードファイル
 */


#include "Shader.h"
#include "../string/StringUtil.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::ShaderInclude::ShaderInclude()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ShaderInclude::~ShaderInclude()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ShaderInclude::Init(void)
{
	this->Release();

	this->dir_path_.clear();

	return;
}


/**
 * @brief Create関数
 * @param dir_path (directory_path)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::ShaderInclude::Create(const WCHAR *dir_path)
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
 * @return result (result)<br>
 * 0未満=失敗
 */
HRESULT __stdcall tml::graphic::ShaderInclude::Open(D3D_INCLUDE_TYPE inc_type, LPCSTR file_name, LPCVOID parent_dat, LPCVOID *dst_dat, UINT *dst_dat_len)
{
	tml::BinaryFile bin_file;
	std::wstring bin_file_name;

	bin_file.read_desc.data.file_path = this->dir_path_;
	bin_file.read_desc.data.file_path += L"/";
	bin_file.read_desc.data.file_path += tml::StringUtil::GetString(bin_file_name, file_name);

	if (bin_file.Read() < 0) {
		return (E_FAIL);
	}

	auto &bin_file_buf = bin_file.data.buffer;

	if (bin_file_buf.GetLength() <= 0U) {
		return (E_FAIL);
	}

	(*dst_dat) = bin_file_buf.Get();
	(*dst_dat_len) = bin_file_buf.GetLength();

	bin_file_buf.Clear();

	return (S_OK);
}


/**
 * @brief Close関数
 * @param dat (data)
 * @return result (result)<br>
 * 0未満=失敗
 */
HRESULT __stdcall tml::graphic::ShaderInclude::Close(LPCVOID dat)
{
	auto bin_file_buf = reinterpret_cast<BYTE *>(const_cast<LPVOID>(dat));

	tml::MemoryUtil::Release(&bin_file_buf);

	return (S_OK);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::ShaderDesc::ShaderDesc() :
	vertex_shader_input_element_desc_count(0U),
	vertex_shader_input_element_desc_array(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ShaderDesc::~ShaderDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ShaderDesc::Init(void)
{
	this->Release();

	this->file_read_desc.Init();
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

	tml::graphic::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::ShaderDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::graphic::ManagerResourceDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Shader Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"SHADER");

		if (val_name_cont != nullptr) {
			val = ini_file.data.GetValue((*val_name_cont), L"FILE_PATH");

			if (val != nullptr) {
				this->file_read_desc.data.file_path = (*val);
			}

			val = ini_file.data.GetValue((*val_name_cont), L"INC_DIR_PATH");

			if (val != nullptr) {
				this->include_directory_path = (*val);
			}

			val = ini_file.data.GetValue((*val_name_cont), L"VS_FUNC_NAME");

			if (val != nullptr) {
				this->vertex_shader_function_name = (*val);
			}

			val = ini_file.data.GetValue((*val_name_cont), L"VS_MODEL_NAME");

			if (val != nullptr) {
				this->vertex_shader_model_name = (*val);
			}

			val = ini_file.data.GetValue((*val_name_cont), L"HS_FUNC_NAME");

			if (val != nullptr) {
				this->hull_shader_function_name = (*val);
			}

			val = ini_file.data.GetValue((*val_name_cont), L"HS_MODEL_NAME");

			if (val != nullptr) {
				this->hull_shader_model_name = (*val);
			}

			val = ini_file.data.GetValue((*val_name_cont), L"DS_FUNC_NAME");

			if (val != nullptr) {
				this->domain_shader_function_name = (*val);
			}

			val = ini_file.data.GetValue((*val_name_cont), L"DS_MODEL_NAME");

			if (val != nullptr) {
				this->domain_shader_model_name = (*val);
			}

			val = ini_file.data.GetValue((*val_name_cont), L"GS_FUNC_NAME");

			if (val != nullptr) {
				this->geometry_shader_function_name = (*val);
			}

			val = ini_file.data.GetValue((*val_name_cont), L"GS_MODEL_NAME");

			if (val != nullptr) {
				this->geometry_shader_model_name = (*val);
			}

			val = ini_file.data.GetValue((*val_name_cont), L"PS_FUNC_NAME");

			if (val != nullptr) {
				this->pixel_shader_function_name = (*val);
			}

			val = ini_file.data.GetValue((*val_name_cont), L"PS_MODEL_NAME");

			if (val != nullptr) {
				this->pixel_shader_model_name = (*val);
			}

			val = ini_file.data.GetValue((*val_name_cont), L"CS_FUNC_NAME");

			if (val != nullptr) {
				this->compute_shader_function_name = (*val);
			}

			val = ini_file.data.GetValue((*val_name_cont), L"CS_MODEL_NAME");

			if (val != nullptr) {
				this->compute_shader_model_name = (*val);
			}
		}
	}

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Shader::Shader() :
	vs_(nullptr),
	vs_input_layout_(nullptr),
	hs_(nullptr),
	ds_(nullptr),
	gs_(nullptr),
	ps_(nullptr),
	cs_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Shader::~Shader()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::Shader::Release(void)
{
	if (this->cs_ != nullptr) {
		this->cs_->Release();

		this->cs_ = nullptr;
	}

	if (this->ps_ != nullptr) {
		this->ps_->Release();

		this->ps_ = nullptr;
	}

	if (this->gs_ != nullptr) {
		this->gs_->Release();

		this->gs_ = nullptr;
	}

	if (this->ds_ != nullptr) {
		this->ds_->Release();

		this->ds_ = nullptr;
	}

	if (this->hs_ != nullptr) {
		this->hs_->Release();

		this->hs_ = nullptr;
	}

	if (this->vs_input_layout_ != nullptr) {
		this->vs_input_layout_->Release();

		this->vs_input_layout_ = nullptr;
	}

	if (this->vs_ != nullptr) {
		this->vs_->Release();

		this->vs_ = nullptr;
	}

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Shader::Init(void)
{
	this->Release();

	tml::graphic::ManagerResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Shader::Create(const tml::graphic::ShaderDesc &desc)
{
	this->Init();

	if (tml::graphic::ManagerResource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	auto file_read_desc_dat = desc.file_read_desc.GetDataByParent();

	tml::BinaryFile bin_file;

	bin_file.read_desc.parent_data = file_read_desc_dat;

	if (bin_file.Read() < 0) {
		this->Init();

		return (-1);
	}

	auto &bin_file_buf = bin_file.data.buffer;

	if (bin_file_buf.GetLength() <= 0U) {
		this->Init();

		return (-1);
	}

	std::vector<D3D10_SHADER_MACRO> macro_ary;
	std::vector<std::string> macro_name_ary;
	std::vector<std::string> macro_val_ary;

	if (!desc.macro_container.empty()) {
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
		auto blob = this->GetBlob(bin_file_buf, desc.include_directory_path.c_str(), desc.vertex_shader_function_name.c_str(), desc.vertex_shader_model_name.c_str(), macro_ary.data());

		if (blob == nullptr) {
			this->Init();

			return (-1);
		}

		if (FAILED(this->GetManager()->GetDevice()->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &this->vs_))) {
			this->ReleaseBlob(&blob);

			this->Init();

			return (-1);
		}

		if (FAILED(this->GetManager()->GetDevice()->CreateInputLayout(desc.vertex_shader_input_element_desc_array, desc.vertex_shader_input_element_desc_count, blob->GetBufferPointer(), blob->GetBufferSize(), &this->vs_input_layout_))) {
			this->ReleaseBlob(&blob);

			this->Init();

			return (-1);
		}

		this->ReleaseBlob(&blob);
	}

	if (!desc.hull_shader_function_name.empty()) {
		auto blob = this->GetBlob(bin_file_buf, desc.include_directory_path.c_str(), desc.hull_shader_function_name.c_str(), desc.hull_shader_model_name.c_str(), macro_ary.data());

		if (blob == nullptr) {
			this->Init();

			return (-1);
		}

		if (FAILED(this->GetManager()->GetDevice()->CreateHullShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &this->hs_))) {
			this->ReleaseBlob(&blob);

			this->Init();

			return (-1);
		}

		this->ReleaseBlob(&blob);
	}

	if (!desc.domain_shader_function_name.empty()) {
		auto blob = this->GetBlob(bin_file_buf, desc.include_directory_path.c_str(), desc.domain_shader_function_name.c_str(), desc.domain_shader_model_name.c_str(), macro_ary.data());

		if (blob == nullptr) {
			this->Init();

			return (-1);
		}

		if (FAILED(this->GetManager()->GetDevice()->CreateDomainShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &this->ds_))) {
			this->ReleaseBlob(&blob);

			this->Init();

			return (-1);
		}

		this->ReleaseBlob(&blob);
	}

	if (!desc.geometry_shader_function_name.empty()) {
		auto blob = this->GetBlob(bin_file_buf, desc.include_directory_path.c_str(), desc.geometry_shader_function_name.c_str(), desc.geometry_shader_model_name.c_str(), macro_ary.data());

		if (blob == nullptr) {
			this->Init();

			return (-1);
		}

		if (FAILED(this->GetManager()->GetDevice()->CreateGeometryShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &this->gs_))) {
			this->ReleaseBlob(&blob);

			this->Init();

			return (-1);
		}

		this->ReleaseBlob(&blob);
	}

	if (!desc.pixel_shader_function_name.empty()) {
		auto blob = this->GetBlob(bin_file_buf, desc.include_directory_path.c_str(), desc.pixel_shader_function_name.c_str(), desc.pixel_shader_model_name.c_str(), macro_ary.data());

		if (blob == nullptr) {
			this->Init();

			return (-1);
		}

		if (FAILED(this->GetManager()->GetDevice()->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &this->ps_))) {
			this->ReleaseBlob(&blob);

			this->Init();

			return (-1);
		}

		this->ReleaseBlob(&blob);
	}

	if (!desc.compute_shader_function_name.empty()) {
		auto blob = this->GetBlob(bin_file_buf, desc.include_directory_path.c_str(), desc.compute_shader_function_name.c_str(), desc.compute_shader_model_name.c_str(), macro_ary.data());

		if (blob == nullptr) {
			this->Init();

			return (-1);
		}

		if (FAILED(this->GetManager()->GetDevice()->CreateComputeShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &this->cs_))) {
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
 * @param buf (buf)
 * @param inc_dir_path (include_directory_path)
 * @param func_name (function_name)
 * @param model_name (model_name)
 * @param macro_ary (macro_array)<br>
 * nullptr=指定無し
 * @return blob (blob)<br>
 * nullptr=失敗
 */
ID3DBlob *tml::graphic::Shader::GetBlob(const tml::DynamicBuffer &buf, const WCHAR *inc_dir_path, const WCHAR *func_name, const WCHAR *model_name, const D3D10_SHADER_MACRO *macro_ary)
{
	tml::graphic::ShaderInclude inc;

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

	if (FAILED(D3DX11CompileFromMemory(reinterpret_cast<LPCSTR>(buf.Get()), buf.GetLength(), nullptr, macro_ary, &inc, tmp_func_name.c_str(), tmp_model_name.c_str(), compile_flg, 0U, nullptr, &blob, &err_blob, nullptr))) {
		if ((tml::ConstantUtil::LIBRARY::DEBUG_FLAG)
		&& (err_blob != nullptr)) {
			OutputDebugStringA(reinterpret_cast<CHAR *>(err_blob->GetBufferPointer()));
		}

		this->ReleaseBlob(&err_blob);

		return (nullptr);
	}

	if ((tml::ConstantUtil::LIBRARY::DEBUG_FLAG)
	&& (err_blob != nullptr)) {
		OutputDebugStringA(reinterpret_cast<CHAR *>(err_blob->GetBufferPointer()));
	}

	this->ReleaseBlob(&err_blob);

	return (blob);
}


/**
 * @brief ReleaseBlob関数
 * @param blob (blob)
 */
void tml::graphic::Shader::ReleaseBlob(ID3DBlob **blob)
{
	if ((*blob) == nullptr) {
		return;
	}

	(*blob)->Release();

	(*blob) = nullptr;

	return;
}
