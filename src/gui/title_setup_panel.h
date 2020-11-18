/*
Decade
Copyright (c) 2019-2020 Marco Peyer

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/gpl-3.0.txt>.
*/

#pragma once

#include "wx_widgets_include.h"

#include <array>
#include <algorithm>
#include <memory>
#include <functional>
#include <string>
#include <limits>

#include <sigslot/signal.hpp>





class TitleSetupPanel : public wxPanel
{
public:

	TitleSetupPanel(wxWindow* parent) :
		wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, wxPanelNameStr),
		ID_FRAME_HEIGHT(wxNewId()),
		ID_SIZE_RATIO(wxNewId()),
		ID_TEXT(wxNewId()),
		ID_COLOR_PICKER(wxNewId()),
		ID_SLIDER(wxNewId()),
		text_color{ 0.f, 0.f, 0.f, 1.f },
		frame_height(10.f),
		font_size_ratio(.5f),
		title_text("Title Text")

	{
		wxBoxSizer* vertical_sizer = new wxBoxSizer(wxVERTICAL);
		SetSizer(vertical_sizer);

		std::array<wxBoxSizer*, 5> horizontal_sizers;

		for (auto& sizer : horizontal_sizers)
		{
			sizer = new wxBoxSizer(wxHORIZONTAL);
			vertical_sizer->Add(sizer, 0, wxEXPAND);
		}

		std::array<wxStaticText*, 5> labels;

		labels[0] = new wxStaticText(this, wxID_ANY, L"Frame Height");
		labels[0]->SetMinSize(wxSize(120, -1));
		horizontal_sizers[0]->Add(labels[0], 0, wxEXPAND | wxALL, 5);

		labels[1] = new wxStaticText(this, wxID_ANY, L"Font Size Ratio");
		labels[1]->SetMinSize(wxSize(120, -1));
		horizontal_sizers[1]->Add(labels[1], 0, wxEXPAND | wxALL, 5);
		//horizontal_sizers[1]->SetItemMinSize(0, wxSize(150, -1));

		labels[2] = new wxStaticText(this, wxID_ANY, L"Text");
		labels[2]->SetMinSize(wxSize(120, -1));
		horizontal_sizers[2]->Add(labels[2], 0, wxEXPAND | wxALL, 5);

		labels[3] = new wxStaticText(this, wxID_ANY, L"Text Color");
		labels[3]->SetMinSize(wxSize(120, -1));
		horizontal_sizers[3]->Add(labels[3], 0, wxEXPAND | wxALL, 5);
		labels[3]->Enable(false);

		labels[4] = new wxStaticText(this, wxID_ANY, L"Color Transparency");
		labels[4]->SetMinSize(wxSize(120, -1));
		horizontal_sizers[4]->Add(labels[4], 0, wxEXPAND | wxALL, 5);
		labels[4]->Enable(false);

		frame_height_ctrl = new wxSpinCtrlDouble(this, ID_FRAME_HEIGHT);
		horizontal_sizers[0]->Add(frame_height_ctrl, 1, wxEXPAND | wxALL, 5);

		size_ratio_ctrl = new wxSpinCtrlDouble(this, ID_SIZE_RATIO);
		size_ratio_ctrl->SetIncrement(0.05);
		horizontal_sizers[1]->Add(size_ratio_ctrl, 1, wxEXPAND | wxALL, 5);

		title_text_edit = new wxTextCtrl(this, ID_TEXT);
		horizontal_sizers[2]->Add(title_text_edit, 1, wxEXPAND | wxALL, 5);

		wxColourPickerCtrl* text_color_picker = new wxColourPickerCtrl(this, ID_COLOR_PICKER, *wxStockGDI::GetColour(wxStockGDI::COLOUR_BLACK),
			wxDefaultPosition, wxDefaultSize, wxCLRP_SHOW_ALPHA);
		text_color_picker->Enable(false);
		horizontal_sizers[3]->Add(text_color_picker, 1, wxEXPAND | wxALL, 5);

		wxSlider* alpha_slider = new wxSlider(this, ID_SLIDER, 255, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_LABELS);
		alpha_slider->Enable(false);
		horizontal_sizers[4]->Add(alpha_slider, 1, wxEXPAND | wxALL, 5);

		vertical_sizer->Layout();

		////////////////////////////////////////

		Bind(wxEVT_SPINCTRLDOUBLE, &TitleSetupPanel::SlotSpinControl, this);
		Bind(wxEVT_TEXT, &TitleSetupPanel::SlotTextControl, this);
		Bind(wxEVT_COLOURPICKER_CHANGED, &TitleSetupPanel::SlotColorPickerControl, this);
		Bind(wxEVT_SLIDER, &TitleSetupPanel::SlotSliderControl, this);

		////////////////////////////////////////

		UpdateWidgets();

		text_color_picker->SetColour(wxColour(0, 0, 0, 1));
	}



	void SendDefaultValues()
	{
		signal_frame_height(frame_height);
		signal_font_size_ratio(font_size_ratio);
		signal_title_text(title_text);

		signal_text_color(std::array<float, 4>{0.f, 0.f, 0.f, 1.f});
	}

	sigslot::signal<float> signal_frame_height;
	sigslot::signal<float> signal_font_size_ratio;
	sigslot::signal<const std::string&> signal_title_text;
	sigslot::signal<const std::array<float, 4>&> signal_text_color;

private:

	float frame_height;
	float font_size_ratio;
	std::string title_text;
	std::array<float, 4> text_color;

	void UpdateWidgets()
	{
		frame_height_ctrl->SetValue(frame_height);
		size_ratio_ctrl->SetValue(font_size_ratio);
		title_text_edit->SetValue(title_text);

		signal_frame_height(frame_height);
		signal_font_size_ratio(font_size_ratio);
		signal_title_text(title_text);
	}

	wxSpinCtrlDouble* frame_height_ctrl;
	wxSpinCtrlDouble* size_ratio_ctrl;
	wxTextCtrl* title_text_edit;

	void SlotSpinControl(wxSpinDoubleEvent& event)
	{
		auto float_value = static_cast<float>(event.GetValue());

		if (event.GetId() == ID_FRAME_HEIGHT)
		{
			frame_height = float_value;
			signal_frame_height(float_value);
		}
		if (event.GetId() == ID_SIZE_RATIO)
		{
			font_size_ratio = float_value;
			signal_font_size_ratio(float_value);
		}
	}
	void SlotTextControl(wxCommandEvent& event)
	{
		if (event.GetId() == ID_TEXT)
		{
			title_text = event.GetString();
			signal_title_text(event.GetString());
		}
	}
	void SlotColorPickerControl(wxColourPickerEvent& event)
	{
		if (event.GetId() == ID_COLOR_PICKER)
		{
			auto color = event.GetColour();
			text_color[0] = To_RGBA_float(color.Red());
			text_color[1] = To_RGBA_float(color.Green());
			text_color[2] = To_RGBA_float(color.Blue());
			text_color[3] = 1.0f; // To_RGBA_float(color.Alpha());
			signal_text_color(text_color);
		}
	}
	void SlotSliderControl(wxCommandEvent& event)
	{
		if (event.GetId() == ID_SLIDER)
		{
			auto char_value = static_cast<unsigned char>(event.GetInt());
			text_color[3] = To_RGBA_float(char_value);
			signal_text_color(text_color);
		}
	}

	const int ID_FRAME_HEIGHT;
	const int ID_SIZE_RATIO;
	const int ID_TEXT;
	const int ID_COLOR_PICKER;
	const int ID_SLIDER;

	float To_RGBA_float(unsigned char value)
	{
		//constexpr auto char_min_limit = std::numeric_limits<unsigned char>::min();
		constexpr auto char_max_limit = std::numeric_limits<unsigned char>::max();

		auto float_step = 1.f / static_cast<float>(char_max_limit);

		return static_cast<float>(value) * float_step;
	}
};