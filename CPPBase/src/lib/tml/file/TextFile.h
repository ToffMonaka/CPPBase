/**
 * @file
 * @brief TextFile�w�b�_�[�t�@�C��
 */
#pragma once


#include "../ConstantUtil.h"
#include <list>
#include "File.h"


namespace tml {
/**
 * @brief TextFileReadPlan�N���X
 */
class TextFileReadPlan
{
public:
	std::wstring file_path;

public:
	TextFileReadPlan();
	virtual ~TextFileReadPlan();

	void Init(void);
};
}


namespace tml {
/**
 * @brief TextFileWritePlan�N���X
 */
class TextFileWritePlan
{
public:
	std::wstring file_path;

public:
	TextFileWritePlan();
	virtual ~TextFileWritePlan();

	void Init(void);
};
}


namespace tml {
/**
 * @brief TextFile�N���X
 */
class TextFile : public tml::File
{
public: TextFile(const TextFile &) = delete;
public: TextFile &operator =(const TextFile &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	std::list<std::wstring> str_cont_;

public:
	tml::TextFileReadPlan read_plan;
	tml::TextFileWritePlan write_plan;

private:
	void Release(void);

public:
	TextFile();
	virtual ~TextFile();

	virtual void Init(void);

	virtual INT Read(void);
	virtual INT Write(void);
	const std::list<std::wstring> &GetStringContainer(void) const;
};
}


/**
 * @brief GetStringContainer�֐�
 * @return str_cont (string_container)
 */
inline const std::list<std::wstring> &tml::TextFile::GetStringContainer(void) const
{
	return (this->str_cont_);
}
