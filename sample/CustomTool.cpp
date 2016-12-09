#include "CustomTool.h"

CustomTool* CustomTool::ms_tool = NULL;

CustomTool* CustomTool::getInstance()
{
	if(!ms_tool)
	{
		ms_tool = new CustomTool();
	}

	return ms_tool;
}


MenuItemImage* CustomTool::createMenuItemImage(const char* normal, const char* selected, ccMenuCallback callback)
{
	auto item = MenuItemImage::create();
	auto nsf = SpriteFrameCache::getInstance()->getSpriteFrameByName(normal);
	auto ssf = SpriteFrameCache::getInstance()->getSpriteFrameByName(selected);
	item->setNormalSpriteFrame(nsf);
	item->setSelectedSpriteFrame(ssf);
	item->setCallback(callback);
	return item;
}