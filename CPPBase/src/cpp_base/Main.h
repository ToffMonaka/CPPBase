/**
 * @file
 * @brief Mainヘッダーファイル
 */
#pragma once


#include "ConstantUtil.h"


namespace cpp_base {
static void InitMain(void);
static INT CreateMain(HINSTANCE instance_handle, HINSTANCE prev_instance_handle, WCHAR *cmd_line_str, INT);
}
