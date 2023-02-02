#include "pch.h"
#include "Boost.h"


BAKKESMOD_PLUGIN(Boost, "Boost text/bar", plugin_version, 0)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void Boost::onLoad()
{
	_globalCvarManager = cvarManager;

	boost_plugin_enabled = std::make_shared<bool>(false);
	boost_text_enabled = std::make_shared<bool>(true);
	boost_shadow = std::make_shared<bool>(true);
	boost_color = std::make_shared<bool>(true);
	boost_scale = std::make_shared<float>(1);
	boost_xpos = std::make_shared<int>(0);
	boost_ypos = std::make_shared<int>(-400);
	boost_alpha = std::make_shared<int>(255);
	boostbg_alpha = std::make_shared<int>(175);

	boostbar_enabled = std::make_shared<bool>(true);
	boostbar_color = std::make_shared<bool>(true);
	boostbar_scale = std::make_shared<float>(1);
	boostbar_xpos = std::make_shared<int>(0);
	boostbar_ypos = std::make_shared<int>(-600);
	boostbar_alpha = std::make_shared<int>(255);

	cvarManager->registerCvar("boost_plugin_enabled", std::to_string(*boost_plugin_enabled), "Enable plugin", true, true, 0, true, 1).bindTo(boost_plugin_enabled);
	cvarManager->registerCvar("boost_text_enabled", std::to_string(*boost_text_enabled), "Enable text", true, true, 0, true, 1).bindTo(boost_text_enabled);
	cvarManager->registerCvar("boost_shadow", std::to_string(*boost_shadow), "Shadow", true, true, 0, true, 1).bindTo(boost_shadow);
	cvarManager->registerCvar("boost_color", std::to_string(*boost_color), "Color", true, true, 0, true, 1).bindTo(boost_color);
	cvarManager->registerCvar("boost_scale", std::to_string(*boost_scale), "Scale", true, true, 0.1, true, 10).bindTo(boost_scale);
	cvarManager->registerCvar("boost_xpos", std::to_string(*boost_xpos), "X position", true, true, -9999, true, 9999).bindTo(boost_xpos);
	cvarManager->registerCvar("boost_ypos", std::to_string(*boost_ypos), "Y position", true, true, -9999, true, 9999).bindTo(boost_ypos);
	cvarManager->registerCvar("boost_alpha", std::to_string(*boost_alpha), "Opacity/alpha", true, true, 0, true, 255).bindTo(boost_alpha);
	cvarManager->registerCvar("boostbg_alpha", std::to_string(*boostbg_alpha), "Background Opacity/alpha", true, true, 0, true, 255).bindTo(boostbg_alpha);
	cvarManager->registerCvar("boostbar_enabled", std::to_string(*boostbar_enabled), "Enable bar", true, true, 0, true, 1).bindTo(boostbar_enabled);
	cvarManager->registerCvar("boostbar_color", std::to_string(*boostbar_color), "Boost bar color", true, true, 0, true, 1).bindTo(boostbar_color);
	cvarManager->registerCvar("boostbar_scale", std::to_string(*boostbar_scale), "Boost bar scale", true, true, 0.1, true, 10).bindTo(boostbar_scale);
	cvarManager->registerCvar("boostbar_xpos", std::to_string(*boostbar_xpos), "Boost bar X position", true, true, -9999, true, 9999).bindTo(boostbar_xpos);
	cvarManager->registerCvar("boostbar_ypos", std::to_string(*boostbar_ypos), "Boost bar Y position", true, true, -9999, true, 9999).bindTo(boostbar_ypos);
	cvarManager->registerCvar("boostbar_alpha", std::to_string(*boostbar_alpha), "Boost bar Opacity/alpha", true, true, 0, true, 255).bindTo(boostbar_alpha);
	
	if (boost_plugin_enabled) gameWrapper->RegisterDrawable(bind(&Boost::Render, this, std::placeholders::_1));

	cvarManager->log("Boost plugin loaded!");
}

void Boost::onUnload()
{
	gameWrapper->UnregisterDrawables();
}

void Boost::Render(CanvasWrapper canvas)
{
	bool freeplay = gameWrapper->IsInFreeplay();
	bool training = gameWrapper->IsInCustomTraining();
	bool online = gameWrapper->IsInOnlineGame();
	bool replay = gameWrapper->IsInReplay();

	if (!freeplay && !training && !online && !replay) return;

	CVarWrapper enableCvar = cvarManager->getCvar("boost_plugin_enabled");
	bool enabled = enableCvar.getBoolValue();
	if (!enabled) return;

	Boost::RenderBar(canvas);
	Boost::RenderText(canvas);
}

int Boost::getBoostAmount()
{
	CarWrapper localCar = gameWrapper->GetLocalCar();
	if (localCar.IsNull())
		return 0;

	BoostWrapper boostComponent = localCar.GetBoostComponent();
	if (boostComponent.IsNull())
		return 0;

	return std::clamp(static_cast<int>(boostComponent.GetCurrentBoostAmount() * 100), 0, 100);
}

void Boost::RenderText(CanvasWrapper canvas)
{
	//Text
	CVarWrapper enableCvar = cvarManager->getCvar("boost_text_enabled");
	bool enabled = enableCvar.getBoolValue();
	if (!enabled) return;

	int boostAmount = Boost::getBoostAmount();
	int r = 255, g = 255, b = 255;
	auto color = Boost::GetColor(boostAmount);
	int textScale = 10 * *boost_scale;
	auto canvasCenter = Boost::GetCanvasCenter(canvas);
	Vector2 textPosition = { canvasCenter.X + *boost_xpos - textScale * 12, canvasCenter.Y + *boost_ypos };
	int textWidth = 12 * *boost_scale;
	int textHeight = 6 * *boost_scale;

	//Background
	canvas.SetPosition(textPosition);
	canvas.SetColor(150, 150, 150, *boostbg_alpha);
	canvas.FillBox(Vector2({ textWidth * 23, textHeight * 28 }));

	CVarWrapper colorCvar = cvarManager->getCvar("boost_color");
	bool color_enabled = colorCvar.getBoolValue();
	if (color_enabled) canvas.SetColor(color[0], color[1], color[2], *boost_alpha);
	else canvas.SetColor(255, 255, 255, *boost_alpha);

	canvas.SetPosition(textPosition);
	canvas.DrawString(std::to_string(boostAmount), textScale, textScale, *boost_shadow);
}

void Boost::RenderBar(CanvasWrapper canvas)
{

	CVarWrapper enableCvar = cvarManager->getCvar("boostbar_enabled");
	bool enabled = enableCvar.getBoolValue();
	if (!enabled) return;

	//Boost Bar
	int boostAmount = Boost::getBoostAmount();
	int barLength = 500 * *boostbar_scale;
	int boostBarWidth = (boostAmount * 5) * *boostbar_scale;
	int boostBarHeight = barLength / 10;
	Vector2 boostBarSize = Vector2({ boostBarWidth, boostBarHeight });
	auto canvasCenter = Boost::GetCanvasCenter(canvas);
	Vector2 barPosition = { canvasCenter.X + *boostbar_xpos - barLength / 2, canvasCenter.Y + *boostbar_ypos };


	auto color = Boost::GetColor(boostAmount);
	CVarWrapper colorCvar = cvarManager->getCvar("boostbar_color");
	bool color_enabled = colorCvar.getBoolValue();
	if (color_enabled) canvas.SetColor(color[0], color[1], color[2], *boost_alpha);//shouldn't this be boostbar_alpha?
	else canvas.SetColor(255, 255, 255, *boost_alpha);//shouldn't this be boostbar_alpha?

	canvas.SetPosition(barPosition);
	canvas.FillBox(boostBarSize);

	//Border
	int segmentSize = barLength / 4;
	Vector2 boostBarBorderSize = Vector2({ segmentSize + 2, boostBarHeight });
	canvas.SetColor(0, 0, 0, *boostbar_alpha);

	canvas.SetPosition(barPosition);
	canvas.DrawBox(boostBarBorderSize);

	barPosition.X += segmentSize;
	canvas.SetPosition(barPosition);
	canvas.DrawBox(boostBarBorderSize);

	barPosition.X += segmentSize;
	canvas.SetPosition(barPosition);
	canvas.DrawBox(boostBarBorderSize);

	barPosition.X += segmentSize;
	canvas.SetPosition(barPosition);
	canvas.DrawBox(boostBarBorderSize);
}

Vector2 Boost::GetCanvasCenter(CanvasWrapper canvas)
{
	Vector2 canvasSize = canvas.GetSize();
	return { canvasSize.X / 2, canvasSize.Y / 2 };
}


std::vector<int> Boost::GetColor(int boostAmount)
{
	int r, g, b;
	if (boostAmount >= 75)
	{
		r = 0;
		g = 255;
		b = 0;
	}
	else if (boostAmount >= 50)
	{
		r = 255;
		g = 255;
		b = 0;
	}
	else if (boostAmount >= 25)
	{
		r = 255;
		g = 128;
		b = 0;
	}
	else
	{
		r = 255;
		g = 0;
		b = 0;
	}
	return std::vector({r,g,b});
}
