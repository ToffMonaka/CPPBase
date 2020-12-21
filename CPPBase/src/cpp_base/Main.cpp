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
#include "constant/ConstantUtil_WINDOW.h"
#include "constant/ConstantUtil_FILE.h"
#include "data/SystemConfigFile.h"
#include "thread/MainThread.h"


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
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::CreateMain(const HINSTANCE instance_handle, const HINSTANCE prev_instance_handle, const WCHAR *cmd_line_str, const INT wnd_show_type)
{
	cpp_base::InitMain();

	cpp_base::SystemConfigFile sys_conf_file;

	{// SystemConfigFile Read
		{// MemoryUtil Create
			std::unique_ptr<tml::MemoryUtilEngine> engine = std::make_unique<tml::DefaultMemoryUtilEngine>();

			if (dynamic_cast<tml::DefaultMemoryUtilEngine *>(engine.get())->Create(tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE::NEW, 0U) < 0) {
				cpp_base::InitMain();

				return (-1);
			}

			if (tml::MemoryUtil::Create(engine) < 0) {
				cpp_base::InitMain();

				return (-1);
			}
		}

		sys_conf_file.Init();

		sys_conf_file.read_plan.file_path = cpp_base::ConstantUtil::FILE::SYSTEM_CONFIG_FILE_PATH;

		if (sys_conf_file.Read() < 0) {
			cpp_base::InitMain();

			return (-1);
		}

		auto mem_allocator_info = tml::MemoryUtil::GetAllocatorInfo();

		if (mem_allocator_info.use_cnt > 0U) {
			cpp_base::InitMain();

			return (-1);
		}
	}

	{// MemoryUtil Create
		std::unique_ptr<tml::MemoryUtilEngine> engine = std::make_unique<tml::DefaultMemoryUtilEngine>();

		if (dynamic_cast<tml::DefaultMemoryUtilEngine *>(engine.get())->Create(tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE::DLMALLOC, sys_conf_file.data.application_memory_allocator_size) < 0) {
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

		if (dynamic_cast<tml::DefaultStringUtilEngine *>(engine.get())->Create(sys_conf_file.data.application_locale_name.c_str()) < 0) {
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

		if (dynamic_cast<tml::DefaultTimeUtilEngine *>(engine.get())->Create() < 0) {
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

		if (dynamic_cast<tml::DefaultMathUtilEngine *>(engine.get())->Create() < 0) {
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

		if (dynamic_cast<tml::DefaultRandomUtilEngine *>(engine.get())->Create() < 0) {
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

		if (dynamic_cast<tml::DefaultFileUtilEngine *>(engine.get())->Create() < 0) {
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

		if (dynamic_cast<tml::DefaultThreadUtilEngine *>(engine.get())->Create() < 0) {
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

		if (dynamic_cast<cpp_base::MainThread *>(th.get())->Create(instance_handle, cpp_base::ConstantUtil::WINDOW::NAME, wnd_show_type) < 0) {
			cpp_base::InitMain();

			return (-1);
		}

		if (tml::ThreadUtil::Start(th) < 0) {
			cpp_base::InitMain();

			return (-1);
		}
	}

	return (0);
}
