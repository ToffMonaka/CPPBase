/**
 * @file
 * @brief ProcessUtilEngine�w�b�_�[�t�@�C��
 */
#pragma once


#include "../ConstantUtil.h"
#include "Process.h"
#include "../thread/SpinThreadLock.h"


namespace tml {
/**
 * @brief ProcessUtilEngine�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class ProcessUtilEngine
{
public: ProcessUtilEngine(const ProcessUtilEngine &) = delete;
public: ProcessUtilEngine &operator =(const ProcessUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

public:
	/**
	 * @brief STATE�\����
	 */
	typedef struct STATE_
	{
		BOOL end_flg;

		/**
		 * @brief �R���X�g���N�^
		 */
		STATE_() :
			end_flg(FALSE)
		{
			return;
		}
	} STATE;

private:
	std::unique_ptr<tml::Process> proc_;
	tml::ProcessUtilEngine::STATE stat_;
	tml::SpinThreadLock stat_th_lock_;

protected:
	void Release(void);
	INT Create(void);

public:
	ProcessUtilEngine();
	virtual ~ProcessUtilEngine();

	virtual void Init(void);

	tml::Process *Get(void);
	INT Start(std::unique_ptr<tml::Process> &);
	void End(void);
	tml::ProcessUtilEngine::STATE GetState(void);
	INT GetExitCode(void);
};


/**
 * @brief Get�֐�
 * @return proc (process)<br>
 * NULLP=���s
 */
inline tml::Process *tml::ProcessUtilEngine::Get(void)
{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
	return (this->proc_.get());
}


/**
 * @brief GetState�֐�
 * @return stat (state)
 */
inline tml::ProcessUtilEngine::STATE tml::ProcessUtilEngine::GetState(void)
{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
	return (this->stat_);
}
}
