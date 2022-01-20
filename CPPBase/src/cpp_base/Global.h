/**
 * @file
 * @brief Globalヘッダーファイル
 */
#pragma once


#include "constant/ConstantUtil.h"
#include "data/UtilConfigFile.h"
#include "data/SystemConfigFile.h"


namespace cpp_base {
/**
 * @brief Globalクラス
 */
class Global
{
public: Global() = delete;
public: Global(const cpp_base::Global &) = delete;
public: cpp_base::Global &operator =(const cpp_base::Global &) = delete;

public:
	static cpp_base::UtilConfigFile util_config_file;
	static cpp_base::SystemConfigFile system_config_file;
};
}
