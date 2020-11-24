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
#include "../lib/tml/process/ProcessUtil.h"
#include "../lib/tml/process/DefaultProcessUtilEngine.h"
#include "../lib/tml/thread/ThreadUtil.h"
#include "../lib/tml/thread/DefaultThreadUtilEngine.h"
#include "constant/ConstantUtil_APPLICATION.h"
#include "constant/ConstantUtil_WINDOW.h"
#include "process/MainProcess.h"


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
	return (cpp_base::CreateMain(instance_handle, prev_instance_handle, cmd_line_str, wnd_show_type));
}


/**
 * @brief InitMain関数
 */
void cpp_base::InitMain(void)
{
	tml::ThreadUtil::Init();
	tml::ProcessUtil::Init();
	tml::FileUtil::Init();
	tml::RandomUtil::Init();
	tml::MathUtil::Init();
	tml::TimeUtil::Init();
	tml::StringUtil::Init();
	tml::MemoryUtil::Init();

	return;
}


/**
 * @brief CreateMain関数
 * @param instance_handle (instance_handle)
 * @param prev_instance_handle (prev_instance_handle)
 * @param cmd_line_str (command_line_string)
 * @param wnd_show_type (window_show_type)
 * @return exit_code (exit_code)<br>
 * 0以外=失敗
 */
INT cpp_base::CreateMain(const HINSTANCE instance_handle, const HINSTANCE prev_instance_handle, const WCHAR *cmd_line_str, const INT wnd_show_type)
{
	INT exit_code = 0;

	cpp_base::InitMain();

	{// MemoryUtil Create
		std::unique_ptr<tml::MemoryUtilEngine> engine = std::make_unique<tml::DefaultMemoryUtilEngine>();

		if (dynamic_cast<tml::DefaultMemoryUtilEngine *>(engine.get())->Create(tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::DLMALLOC, cpp_base::ConstantUtil::APPLICATION::MEMORY_ALLOCATOR_SIZE) < 0) {
			cpp_base::InitMain();

			return (exit_code);
		}

		if (tml::MemoryUtil::Create(engine) < 0) {
			cpp_base::InitMain();

			return (exit_code);
		}
	}

	{// StringUtil Create
		std::unique_ptr<tml::StringUtilEngine> engine = std::make_unique<tml::DefaultStringUtilEngine>();

		if (dynamic_cast<tml::DefaultStringUtilEngine *>(engine.get())->Create(cpp_base::ConstantUtil::APPLICATION::LOCALE_NAME) < 0) {
			cpp_base::InitMain();

			return (exit_code);
		}

		if (tml::StringUtil::Create(engine) < 0) {
			cpp_base::InitMain();

			return (exit_code);
		}
	}

	{// TimeUtil Create
		std::unique_ptr<tml::TimeUtilEngine> engine = std::make_unique<tml::DefaultTimeUtilEngine>();

		if (dynamic_cast<tml::DefaultTimeUtilEngine *>(engine.get())->Create() < 0) {
			cpp_base::InitMain();

			return (exit_code);
		}

		if (tml::TimeUtil::Create(engine) < 0) {
			cpp_base::InitMain();

			return (exit_code);
		}
	}

	{// MathUtil Create
		std::unique_ptr<tml::MathUtilEngine> engine = std::make_unique<tml::DefaultMathUtilEngine>();

		if (dynamic_cast<tml::DefaultMathUtilEngine *>(engine.get())->Create() < 0) {
			cpp_base::InitMain();

			return (exit_code);
		}

		if (tml::MathUtil::Create(engine) < 0) {
			cpp_base::InitMain();

			return (exit_code);
		}
	}

	{// RandomUtil Create
		std::unique_ptr<tml::RandomUtilEngine> engine = std::make_unique<tml::DefaultRandomUtilEngine>();

		if (dynamic_cast<tml::DefaultRandomUtilEngine *>(engine.get())->Create() < 0) {
			cpp_base::InitMain();

			return (exit_code);
		}

		if (tml::RandomUtil::Create(engine) < 0) {
			cpp_base::InitMain();

			return (exit_code);
		}
	}

	{// FileUtil Create
		std::unique_ptr<tml::FileUtilEngine> engine = std::make_unique<tml::DefaultFileUtilEngine>();

		if (dynamic_cast<tml::DefaultFileUtilEngine *>(engine.get())->Create() < 0) {
			cpp_base::InitMain();

			return (exit_code);
		}

		if (tml::FileUtil::Create(engine) < 0) {
			cpp_base::InitMain();

			return (exit_code);
		}
	}

	{// ProcessUtil Create
		std::unique_ptr<tml::ProcessUtilEngine> engine = std::make_unique<tml::DefaultProcessUtilEngine>();

		if (dynamic_cast<tml::DefaultProcessUtilEngine *>(engine.get())->Create() < 0) {
			cpp_base::InitMain();

			return (exit_code);
		}

		if (tml::ProcessUtil::Create(engine) < 0) {
			cpp_base::InitMain();

			return (exit_code);
		}
	}

	{// ThreadUtil Create
		std::unique_ptr<tml::ThreadUtilEngine> engine = std::make_unique<tml::DefaultThreadUtilEngine>();

		if (dynamic_cast<tml::DefaultThreadUtilEngine *>(engine.get())->Create() < 0) {
			cpp_base::InitMain();

			return (exit_code);
		}

		if (tml::ThreadUtil::Create(engine) < 0) {
			cpp_base::InitMain();

			return (exit_code);
		}
	}

	{// MainProcess Start
		std::unique_ptr<tml::Process> proc = std::make_unique<cpp_base::MainProcess>();

		if (dynamic_cast<cpp_base::MainProcess *>(proc.get())->Create(instance_handle, cpp_base::ConstantUtil::WINDOW::NAME, wnd_show_type) < 0) {
			cpp_base::InitMain();

			return (exit_code);
		}

		if (tml::ProcessUtil::Start(proc) < 0) {
			cpp_base::InitMain();

			return (exit_code);
		}

		exit_code = tml::ProcessUtil::GetExitCode();
	}

	cpp_base::InitMain();

	return (exit_code);
}
