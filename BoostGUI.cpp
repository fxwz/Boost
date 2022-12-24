#include "pch.h"
#include "Boost.h"

/*
// Plugin Settings Window code here
std::string Boost::GetPluginName() {
	cvarManager->log("BoostGUI.GetPluginName()");
	return "Boost";
}
void Boost::SetImGuiContext(uintptr_t ctx) {
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

// Render the plugin settings here
// This will show up in bakkesmod when the plugin is loaded at
//  f2 -> plugins -> Boost
void Boost::RenderSettings() {
	ImGui::TextUnformatted("Boost plugin settings");
}

/*
// Do ImGui rendering here
void Boost::Render()
{
	if (!ImGui::Begin(menuTitle_.c_str(), &isWindowOpen_, ImGuiWindowFlags_None))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}

	ImGui::End();

	if (!isWindowOpen_)
	{
		cvarManager->executeCommand("togglemenu " + GetMenuName());
	}
}

// Name of the menu that is used to toggle the window.
std::string Boost::GetMenuName()
{
	return "Boost";
}

// Title to give the menu
std::string Boost::GetMenuTitle()
{
	return menuTitle_;
}

// Don't call this yourself, BM will call this function with a pointer to the current ImGui context
void Boost::SetImGuiContext(uintptr_t ctx)
{
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

// Should events such as mouse clicks/key inputs be blocked so they won't reach the game
bool Boost::ShouldBlockInput()
{
	return ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard;
}

// Return true if window should be interactive
bool Boost::IsActiveOverlay()
{
	return true;
}

// Called when window is opened
void Boost::OnOpen()
{
	isWindowOpen_ = true;
}

// Called when window is closed
void Boost::OnClose()
{
	isWindowOpen_ = false;
}
*/
