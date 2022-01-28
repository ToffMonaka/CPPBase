/**
 * @file
 * @brief Mainコードファイル
 */


#include "Main.h"
#include "../lib/tml/memory/MemoryUtil.h"
#include "../lib/tml/memory/DefaultMemoryUtilEngine.h"
#include "../lib/tml/string/StringUtil.h"
#include "../lib/tml/string/DefaultStringUtilEngine.h"
#include "../lib/tml/time/TimeUtil.h"
#include "../lib/tml/time/DefaultTimeUtilEngine.h"
#include "../lib/tml/math/MathUtil.h"
#include "../lib/tml/math/DefaultMathUtilEngine.h"
#include "../lib/tml/random/RandomUtil.h"
#include "../lib/tml/random/DefaultRandomUtilEngine.h"
#include "../lib/tml/file/FileUtil.h"
#include "../lib/tml/file/DefaultFileUtilEngine.h"
#include "../lib/tml/thread/ThreadUtil.h"
#include "../lib/tml/thread/DefaultThreadUtilEngine.h"
#include "constant/ConstantUtil_FILE_PATH.h"
#include "constant/ConstantUtil_WINDOW.h"
#include "thread/MainThread.h"
#include "Global.h"


/**
 * @brief wWinMain関数
 *
 * 最初に呼ばれる関数
 *
 * @param instance_handle (instance_handle)
 * @param prev_instance_handle (prev_instance_handle)
 * @param cmd_line_str (command_line_string)
 * @param wnd_show_type (window_show_type)
 * @return exit_code (exit_code)<br>
 * 0以外=失敗
 */
INT APIENTRY wWinMain(_In_ HINSTANCE instance_handle, _In_opt_ HINSTANCE prev_instance_handle, _In_ WCHAR *cmd_line_str, _In_ INT wnd_show_type)
{
	cpp_base::CreateMain(instance_handle, prev_instance_handle, cmd_line_str, wnd_show_type);

	return (cpp_base::InitMain());
}


/**
 * @brief InitMain関数
 * @return exit_code (exit_code)<br>
 * 0以外=失敗
 */
INT cpp_base::InitMain(void)
{
	auto exit_code = tml::ThreadUtil::GetExitCode();

	tml::ThreadUtil::Init();
	tml::FileUtil::Init();
	tml::RandomUtil::Init();
	tml::MathUtil::Init();
	tml::TimeUtil::Init();
	tml::StringUtil::Init();
	tml::MemoryUtil::Init();

	return (exit_code);
}


/**
 * @brief CreateMain関数
 * @param instance_handle (instance_handle)
 * @param prev_instance_handle (prev_instance_handle)
 * @param cmd_line_str (command_line_string)
 * @param wnd_show_type (window_show_type)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::CreateMain(const HINSTANCE instance_handle, const HINSTANCE prev_instance_handle, const WCHAR *cmd_line_str, const INT wnd_show_type)
{
	cpp_base::InitMain();

	{// UtilConfigFile Read
		cpp_base::Global::util_config_file.read_desc.data.file_path = cpp_base::ConstantUtil::FILE_PATH::UTIL_CONFIG;

		if (cpp_base::Global::util_config_file.Read() < 0) {
			cpp_base::InitMain();

			return (-1);
		}
	}

	{// SystemConfigFile Read
		cpp_base::Global::system_config_file.read_desc.data.file_path = cpp_base::ConstantUtil::FILE_PATH::SYSTEM_CONFIG;

		if (cpp_base::Global::system_config_file.Read() < 0) {
			cpp_base::InitMain();

			return (-1);
		}
	}

	{// MemoryUtil Create
		std::unique_ptr<tml::MemoryUtilEngine> engine = std::make_unique<tml::DefaultMemoryUtilEngine>();
		tml::DefaultMemoryUtilEngineDesc engine_desc;

		engine_desc.allocator_type = tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE::DLMALLOC;
		engine_desc.allocator_size = cpp_base::Global::util_config_file.data.util_memory_allocator_size;

		if (reinterpret_cast<tml::DefaultMemoryUtilEngine *>(engine.get())->Create(engine_desc) < 0) {
			cpp_base::InitMain();

			return (-1);
		}

		if (tml::MemoryUtil::Create(engine) < 0) {
			cpp_base::InitMain();

			return (-1);
		}
	}

	{// StringUtil Create
		std::unique_ptr<tml::StringUtilEngine> engine = std::make_unique<tml::DefaultStringUtilEngine>();
		tml::DefaultStringUtilEngineDesc engine_desc;

		engine_desc.locale_name = cpp_base::Global::util_config_file.data.util_locale_name;

		if (reinterpret_cast<tml::DefaultStringUtilEngine *>(engine.get())->Create(engine_desc) < 0) {
			cpp_base::InitMain();

			return (-1);
		}

		if (tml::StringUtil::Create(engine) < 0) {
			cpp_base::InitMain();

			return (-1);
		}
	}

	{// TimeUtil Create
		std::unique_ptr<tml::TimeUtilEngine> engine = std::make_unique<tml::DefaultTimeUtilEngine>();
		tml::DefaultTimeUtilEngineDesc engine_desc;

		if (reinterpret_cast<tml::DefaultTimeUtilEngine *>(engine.get())->Create(engine_desc) < 0) {
			cpp_base::InitMain();

			return (-1);
		}

		if (tml::TimeUtil::Create(engine) < 0) {
			cpp_base::InitMain();

			return (-1);
		}
	}

	{// MathUtil Create
		std::unique_ptr<tml::MathUtilEngine> engine = std::make_unique<tml::DefaultMathUtilEngine>();
		tml::DefaultMathUtilEngineDesc engine_desc;

		if (reinterpret_cast<tml::DefaultMathUtilEngine *>(engine.get())->Create(engine_desc) < 0) {
			cpp_base::InitMain();

			return (-1);
		}

		if (tml::MathUtil::Create(engine) < 0) {
			cpp_base::InitMain();

			return (-1);
		}
	}

	{// RandomUtil Create
		std::unique_ptr<tml::RandomUtilEngine> engine = std::make_unique<tml::DefaultRandomUtilEngine>();
		tml::DefaultRandomUtilEngineDesc engine_desc;

		if (reinterpret_cast<tml::DefaultRandomUtilEngine *>(engine.get())->Create(engine_desc) < 0) {
			cpp_base::InitMain();

			return (-1);
		}

		if (tml::RandomUtil::Create(engine) < 0) {
			cpp_base::InitMain();

			return (-1);
		}
	}

	{// FileUtil Create
		std::unique_ptr<tml::FileUtilEngine> engine = std::make_unique<tml::DefaultFileUtilEngine>();
		tml::DefaultFileUtilEngineDesc engine_desc;

		if (reinterpret_cast<tml::DefaultFileUtilEngine *>(engine.get())->Create(engine_desc) < 0) {
			cpp_base::InitMain();

			return (-1);
		}

		if (tml::FileUtil::Create(engine) < 0) {
			cpp_base::InitMain();

			return (-1);
		}
	}

	{// ThreadUtil Create
		std::unique_ptr<tml::ThreadUtilEngine> engine = std::make_unique<tml::DefaultThreadUtilEngine>();
		tml::DefaultThreadUtilEngineDesc engine_desc;

		if (reinterpret_cast<tml::DefaultThreadUtilEngine *>(engine.get())->Create(engine_desc) < 0) {
			cpp_base::InitMain();

			return (-1);
		}

		if (tml::ThreadUtil::Create(engine) < 0) {
			cpp_base::InitMain();

			return (-1);
		}
	}

	{// MainThread Start
		std::unique_ptr<tml::MainThread> th = std::make_unique<cpp_base::MainThread>();

		if (reinterpret_cast<cpp_base::MainThread *>(th.get())->Create(instance_handle, cpp_base::ConstantUtil::WINDOW::NAME, wnd_show_type) < 0) {
			if (cpp_base::ConstantUtil::APPLICATION::DEBUG_FLAG) {
				tml::Log(L"Error: MainThread Create\n");
			}

			cpp_base::InitMain();

			return (-1);
		}

		if (tml::ThreadUtil::Start(th) < 0) {
			if (cpp_base::ConstantUtil::APPLICATION::DEBUG_FLAG) {
				tml::Log(L"Error: MainThread Start\n");
			}

			cpp_base::InitMain();

			return (-1);
		}
	}

	return (0);
}
