/**
 * @file
 * @brief Mainコードファイル
 */


#include "Main.h"
#include "../lib/tml/memory/MemoryUtil.h"
#include "../lib/tml/memory/DefaultMemoryUtilEngine.h"
#include "../lib/tml/random/RandomUtil.h"
#include "../lib/tml/random/DefaultRandomUtilEngine.h"
#include "../lib/tml/process/ProcessUtil.h"
#include "../lib/tml/process/DefaultProcessUtilEngine.h"
#include "../lib/tml/thread/ThreadUtil.h"
#include "../lib/tml/thread/DefaultThreadUtilEngine.h"


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
	tml::RandomUtil::Init();
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
INT cpp_base::CreateMain(HINSTANCE instance_handle, HINSTANCE prev_instance_handle, WCHAR *cmd_line_str, INT wnd_show_type)
{
	cpp_base::InitMain();

	{// MemoryUtil Create
		std::unique_ptr<tml::MemoryUtilEngine> engine(new tml::DefaultMemoryUtilEngine());

		if (dynamic_cast<tml::DefaultMemoryUtilEngine *>(engine.get())->Create(tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::DLMALLOC, 1048576U) < 0) {
			cpp_base::InitMain();

			return (0);
		}

		if (tml::MemoryUtil::Create(engine) < 0) {
			cpp_base::InitMain();

			return (0);
		}
	}

	{// RandomUtil Create
		std::unique_ptr<tml::RandomUtilEngine> engine(new tml::DefaultRandomUtilEngine());

		if (dynamic_cast<tml::DefaultRandomUtilEngine *>(engine.get())->Create() < 0) {
			cpp_base::InitMain();

			return (0);
		}

		if (tml::RandomUtil::Create(engine) < 0) {
			cpp_base::InitMain();

			return (0);
		}
	}

	{// ProcessUtil Create
		std::unique_ptr<tml::ProcessUtilEngine> engine(new tml::DefaultProcessUtilEngine());

		if (dynamic_cast<tml::DefaultProcessUtilEngine *>(engine.get())->Create() < 0) {
			cpp_base::InitMain();

			return (0);
		}

		if (tml::ProcessUtil::Create(engine) < 0) {
			cpp_base::InitMain();

			return (0);
		}
	}

	{// ThreadUtil Create
		std::unique_ptr<tml::ThreadUtilEngine> engine(new tml::DefaultThreadUtilEngine());

		if (dynamic_cast<tml::DefaultThreadUtilEngine *>(engine.get())->Create() < 0) {
			cpp_base::InitMain();

			return (0);
		}

		if (tml::ThreadUtil::Create(engine) < 0) {
			cpp_base::InitMain();

			return (0);
		}
	}

	{// Test
		{// MemoryUtil Test
			auto p = tml::MemoryUtil::Get<INT>(10U);

			auto allocator_info1 = tml::MemoryUtil::GetAllocatorInfo();

			tml::MemoryUtil::Release<INT>(&p);

			auto allocator_info2 = tml::MemoryUtil::GetAllocatorInfo();

			int a = 0;
		}

		{// RandomUtil Test
			std::array<INT, 100U> val_ary;

			for (auto &val : val_ary) {
				val = tml::RandomUtil::GetINT(0, 100);
			}

			int a = 0;
		}

		int a = 0;
	}

	MSG msg = {};

	INT exit_code = static_cast<INT>(msg.wParam);

	cpp_base::InitMain();

	return (exit_code);
}
