#pragma once

#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"
#include "version.h"

constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);

class Boost: public BakkesMod::Plugin::BakkesModPlugin
{
	std::shared_ptr<bool> boost_plugin_enabled;
	std::shared_ptr<bool> boost_text_enabled;
	std::shared_ptr<bool> boost_shadow;
	std::shared_ptr<bool> boost_color;
	std::shared_ptr<float> boost_scale;
	std::shared_ptr<int> boost_xpos;
	std::shared_ptr<int> boost_ypos;
	std::shared_ptr<int> boost_alpha;
	std::shared_ptr<int> boostbg_alpha;

	std::shared_ptr<bool> boostbar_enabled;
	std::shared_ptr<bool> boostbar_color;
	std::shared_ptr<float> boostbar_scale;
	std::shared_ptr<int> boostbar_xpos;
	std::shared_ptr<int> boostbar_ypos;
	std::shared_ptr<int> boostbar_alpha;

	Vector2 canvasSize;

	virtual void onLoad();
	virtual void onUnload();
	void Render(CanvasWrapper canvas);
	void RenderText(CanvasWrapper canvas);
	void RenderBar(CanvasWrapper canvas);
	int getBoostAmount();
	Vector2 GetCanvasCenter(CanvasWrapper canvas);
	std::vector<int> GetColor(int boostAmount);
};

