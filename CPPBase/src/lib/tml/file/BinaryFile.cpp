/**
 * @file
 * @brief BinaryFileコードファイル
 */


#include "BinaryFile.h"
#include <fstream>
#include "FileUtil.h"


/**
 * @brief コンストラクタ
 */
tml::BinaryFileData::BinaryFileData()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::BinaryFileData::~BinaryFileData()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::BinaryFileData::Init(void)
{
	this->file_buffer.Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::BinaryFileReadPlanData::BinaryFileReadPlanData() :
	one_buffer_size(1024U)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::BinaryFileReadPlanData::~BinaryFileReadPlanData()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::BinaryFileReadPlanData::Init(void)
{
	this->file_path.clear();
	this->file_buffer.Init();
	this->one_buffer_size = 1024U;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::BinaryFileReadPlan::BinaryFileReadPlan() :
	parent_data(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::BinaryFileReadPlan::~BinaryFileReadPlan()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::BinaryFileReadPlan::Init(void)
{
	this->data.Init();
	this->parent_data = nullptr;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::BinaryFileWritePlanData::BinaryFileWritePlanData() :
	one_buffer_size(1024U),
	add_flag(false)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::BinaryFileWritePlanData::~BinaryFileWritePlanData()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::BinaryFileWritePlanData::Init(void)
{
	this->file_path.clear();
	this->one_buffer_size = 1024U;
	this->add_flag = false;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::BinaryFileWritePlan::BinaryFileWritePlan() :
	parent_data(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::BinaryFileWritePlan::~BinaryFileWritePlan()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::BinaryFileWritePlan::Init(void)
{
	this->data.Init();
	this->parent_data = nullptr;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::BinaryFile::BinaryFile()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::BinaryFile::~BinaryFile()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::BinaryFile::Release(void)
{
	tml::File::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::BinaryFile::Init(void)
{
	this->Release();

	this->data.Init();
	this->read_plan.Init();
	this->write_plan.Init();

	tml::File::Init();

	return;
}


/**
 * @brief Read関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::BinaryFile::Read(void)
{
	auto read_plan_dat = this->read_plan.GetDataByParent();

	tml::DynamicBuffer file_buf;

	if (read_plan_dat->file_path.empty()) {
		file_buf = std::move(read_plan_dat->file_buffer);
	} else {
		CHAR *read_buf = nullptr;
		size_t read_buf_size = 0U;
		size_t read_size = 0U;

		{tml::ThreadLockBlock th_lock_block(tml::FileUtil::GetFileThreadLock());
			std::ifstream ifs;

			ifs.open(read_plan_dat->file_path.c_str(), std::ios_base::in | std::ios_base::binary);

			if (!ifs) {
				return (-1);
			}

			read_buf_size = std::max(read_plan_dat->one_buffer_size, sizeof(size_t));
			read_buf = tml::MemoryUtil::Get<CHAR>(read_buf_size);

			while (1) {
				ifs.read(read_buf, read_buf_size);

				read_size = static_cast<size_t>(ifs.gcount());

				if (read_size > 0U) {
					file_buf.Set(file_buf.GetSize() + read_size, true);
					file_buf.WriteArray(reinterpret_cast<BYTE *>(read_buf), read_size, read_size);
				}

				if (ifs.eof()) {
					break;
				}
			}

			ifs.close();
		}

		tml::MemoryUtil::Release(&read_buf);
		read_buf_size = 0U;
	}

	this->data.Init();

	this->data.file_buffer = std::move(file_buf);

	return (0);
}


/**
 * @brief Write関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::BinaryFile::Write(void)
{
	auto write_plan_dat = this->write_plan.GetDataByParent();

	if (write_plan_dat->file_path.empty()) {
		return (-1);
	}

	size_t file_buf_index = 0U;
	CHAR *write_buf = nullptr;
	size_t write_buf_size = 0U;
	size_t write_size = 0U;

	{tml::ThreadLockBlock th_lock_block(tml::FileUtil::GetFileThreadLock());
		std::ofstream ofs;

		if (write_plan_dat->add_flag) {
			ofs.open(write_plan_dat->file_path.c_str(), std::ios_base::out | std::ios_base::binary | std::ios_base::app);
		} else {
			ofs.open(write_plan_dat->file_path.c_str(), std::ios_base::out | std::ios_base::binary);
		}

		if (!ofs) {
			return (-1);
		}

		if (this->data.file_buffer.GetLength() <= 0U) {
			ofs.close();

			return (0);
		}

		write_buf_size = std::max(write_plan_dat->one_buffer_size, sizeof(size_t));
		write_buf = tml::MemoryUtil::Get<CHAR>(write_buf_size);

		while (1) {
			write_size = std::min(this->data.file_buffer.GetLength() - file_buf_index, write_buf_size);

			tml::MemoryUtil::Copy(write_buf, reinterpret_cast<CHAR *>(&this->data.file_buffer.Get()[file_buf_index]), write_size);

			ofs.write(write_buf, write_size);

			file_buf_index += write_size;

			if (file_buf_index >= this->data.file_buffer.GetLength()) {
				break;
			}
		}

		ofs.close();
	}

	tml::MemoryUtil::Release(&write_buf);
	write_buf_size = 0U;

	return (0);
}
