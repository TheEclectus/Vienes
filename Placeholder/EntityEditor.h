#pragma once

#include <Engine.h>
#include <GameState.h>
#include <TileSurface.h>
#include <Widget.h>
#include <Window.h>

// TODO: separate declaration and definition into .h and .cpp, b-baka.

class GS_EntityEditor : public MMT::GameState
{
private:
	MMT::Button *Btn_CloseEditor;
public:
	GS_EntityEditor(MMT::Engine *Parent) :
		MMT::GameState(Parent, "Entity Editor")
	{

	}

	bool Load() override
	{
		auto WinWidth = Parent->MainWindow.GetSize().w;
		Btn_CloseEditor = new MMT::Button(Parent, "X", { static_cast<MMT::int32>(WinWidth) - 3, 0 }, [](void *Engine) 
		{
			reinterpret_cast<MMT::Engine*>(Engine)->PopState();
		}, Parent);
		Widgets.push_back(Btn_CloseEditor);

		return true;
	}

	void Init() override
	{
		
	}

	void Cleanup() override
	{
		delete Btn_CloseEditor;
	}

	void Input() override
	{
		ProcessEvents();
	}

	void Logic() override
	{

	}

	void Render(MMT::TileSurface &DrawScene) override
	{
		DrawScene.ClearSurface(MMT::Colors::Black);
		MMT::int32 WinWidth = static_cast<MMT::int32>(Parent->MainWindow.GetSize().w);
		MMT::MTileColor Color = { MMT::Colors::LightGrey, MMT::Colors::Black };
		DrawScene.DrawLine({ 0, 0 }, { WinWidth - 4, 0 }, Color, 205);
		DrawScene.DrawTile({ WinWidth - 4, 0 }, 181, Color);
		DrawScene.DrawTile({ WinWidth - 2, 0 }, 198, Color);
		DrawScene.DrawTile({ WinWidth - 1, 0 }, 205, Color);

		DrawWidgets();
	}
};