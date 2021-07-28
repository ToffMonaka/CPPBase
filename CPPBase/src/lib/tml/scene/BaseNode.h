/**
 * @file
 * @brief BaseNodeヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Node.h"


namespace tml {
namespace scene {
/**
 * @brief BaseNodeDescクラス
 */
class BaseNodeDesc : public tml::scene::NodeDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	BaseNodeDesc();
	virtual ~BaseNodeDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::scene::BaseNodeDesc::Release(void)
{
	tml::scene::NodeDesc::Release();

	return;
}


namespace tml {
namespace scene {
/**
 * @brief BaseNodeクラス
 */
class BaseNode : public tml::scene::Node
{
public: BaseNode(const tml::scene::BaseNode &) = delete;
public: tml::scene::BaseNode &operator =(const tml::scene::BaseNode &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT RESOURCE_SUB_INDEX = static_cast<UINT>(tml::ConstantUtil::SCENE::NODE_TYPE::BASE);

private:

protected:
	void Release(void);

public:
	BaseNode();
	virtual ~BaseNode();

	virtual void Init(void);
	INT Create(const tml::scene::BaseNodeDesc &);

	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);
};
}
}
