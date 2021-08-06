/**
 * @file
 * @brief StageSceneMainNodeコードファイル
 */


#include "StageSceneMainNode.h"
#include "../../lib/tml/math/MathUtil.h"
#include "../../lib/tml/graphic/Canvas2D.h"
#include "../constant/ConstantUtil_FILE_PATH.h"
#include "../graphic/Manager.h"
#include "Manager.h"
#include "Test2DStageNode.h"


/**
 * @brief コンストラクタ
 */
cpp_base::scene::StageSceneMainNodeDesc::StageSceneMainNodeDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::StageSceneMainNodeDesc::~StageSceneMainNodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::StageSceneMainNodeDesc::Init(void)
{
	this->Release();

	cpp_base::scene::NodeDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::StageSceneMainNodeDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (cpp_base::scene::NodeDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// StageSceneMainNode Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"STAGE_SCENE_MAIN_NODE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
cpp_base::scene::StageSceneMainNode::StageSceneMainNode() :
	progress_type_(0U)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::StageSceneMainNode::~StageSceneMainNode()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::scene::StageSceneMainNode::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::StageSceneMainNode::Init(void)
{
	this->Release();

	this->progress_type_ = 0U;

	this->canvas_2d.reset();

	cpp_base::scene::Node::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::StageSceneMainNode::Create(const cpp_base::scene::StageSceneMainNodeDesc &desc)
{
	this->Init();

	if (cpp_base::scene::Node::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	{// StageNode Create
		tml::shared_ptr<tml::scene::Node> node;

		if (this->GetManager()->factory.node_by_xml_file.Get(node, tml::ConstantUtil::SCENE::CLASS_NAME::NODE, tml::XMLFileReadDesc(cpp_base::ConstantUtil::FILE_PATH::TEST_2D_STAGE_NODE)) == nullptr) {
			this->Init();

			return (-1);
		}

		this->AddChildNode(node);
	}

	return (0);
}


/**
 * @brief OnStart関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::StageSceneMainNode::OnStart(void)
{
	auto graphic_mgr = this->GetManager()->GetGraphicManager();

	this->progress_type_ = 1U;

	{// Canvas2D Create
		if (graphic_mgr->GetResource<tml::graphic::Canvas2D>(this->canvas_2d, L"Canvas2D") == nullptr) {
			return (-1);
		}
	}

	return (0);
}


/**
 * @brief OnEnd関数
 */
void cpp_base::scene::StageSceneMainNode::OnEnd(void)
{
	return;
}


/**
 * @brief OnUpdate関数
 */
void cpp_base::scene::StageSceneMainNode::OnUpdate(void)
{
	auto graphic_mgr = this->GetManager()->GetGraphicManager();

	switch (this->progress_type_) {
	case 1U: {
		break;
	}
	}

	return;
}
