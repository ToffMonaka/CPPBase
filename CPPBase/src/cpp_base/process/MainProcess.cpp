/**
 * @file
 * @brief MainProcessコードファイル
 */


#include "MainProcess.h"
#include "../../lib/tml/memory/MemoryUtil.h"
#include "../../lib/tml/random/RandomUtil.h"
#include "../../lib/tml/process/ProcessUtil.h"
#include "../../lib/tml/thread/ThreadUtil.h"
#include "../thread/MainThread.h"


/**
 * @brief コンストラクタ
 */
cpp_base::MainProcess::MainProcess()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::MainProcess::~MainProcess()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::MainProcess::Release(void)
{
	tml::Process::Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::MainProcess::Init(void)
{
	this->Release();

	tml::Process::Init();

	return;
}


/**
 * @brief Create関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::MainProcess::Create(void)
{
	this->Release();

	if (tml::Process::Create() < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief Start関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::MainProcess::Start(void)
{
	{// MainThread Start
		std::unique_ptr<tml::Thread> th(new cpp_base::MainThread());

		if (dynamic_cast<cpp_base::MainThread *>(th.get())->Create() < 0) {
			return (-1);
		}

		if (tml::ThreadUtil::Start(th, true) < 0) {
			return (-1);
		}
	}

	{// Test
		{// MemoryUtil Test
			auto allocator_info1 = tml::MemoryUtil::GetAllocatorInfo();

			auto p = tml::MemoryUtil::Get<INT>(10U);

			auto allocator_info2 = tml::MemoryUtil::GetAllocatorInfo();

			tml::MemoryUtil::Release<INT>(&p);

			auto allocator_info3 = tml::MemoryUtil::GetAllocatorInfo();

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

	return (0);
}


/**
 * @brief End関数
 */
void cpp_base::MainProcess::End(void)
{
	return;
}


/**
 * @brief Update関数
 */
void cpp_base::MainProcess::Update(void)
{
	tml::ProcessUtil::End();

	return;
}
