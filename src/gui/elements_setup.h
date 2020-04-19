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

#include "../shape_config.h"


#ifdef WX_PRECOMP
#include <wx/wxprec.h>
#else 
#include <wx/wx.h>
#endif

#include <wx/panel.h>
#include <wx/window.h>
#include <wx/sizer.h>
#include <wx/listbox.h>
#include <wx/checkbox.h>
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/clrpicker.h>
#include <wx/slider.h>

#include <array>
#include <vector>
#include <algorithm>
#include <string>

#include <memory>
#include <functional>
#include <boost/signals2.hpp>

#include <pugixml.hpp>


class ElementsSetupsPanel : public wxPanel
{
public:
	
	ElementsSetupsPanel(wxWindow* parent);

	template<typename T, typename U>
	void ConnectSignalRectangleShapeConfig(T memfunptr, U objectptr);

	void SendDefaultValues();

	void SaveToXML(pugi::xml_node* node);
	void LoadFromXML(const pugi::xml_node& node);

private:

	void UpdateWidgets(size_t config_index);

	void SlotSelectListBook(wxCommandEvent& event);
	void SlotOutlineVisible(wxCommandEvent& event);
	void SlotFillVisible(wxCommandEvent& event);
	void SlotLineWidth(wxSpinDoubleEvent& event);
	void SlotLineColor(wxColourPickerEvent& event);
	void SlotFillColor(wxColourPickerEvent& event);
	void SlotLineColorAlpha(wxCommandEvent& event);
	void SlotFillColorAlpha(wxCommandEvent& event);

	wxListBox* elements_list_box;
	wxCheckBox* outline_visible;
	wxCheckBox* fill_visible;
	wxSpinCtrlDouble* linewidth_ctrl;
	wxColourPickerCtrl* line_color_picker;
	wxColourPickerCtrl* fill_color_picker;
	wxSlider* line_color_alpha_slider;
	wxSlider* fill_color_alpha_slider;

	std::vector<RectangleShapeConfig> element_configurations;

	const int ID_OUTLINE_VISIBLE;
	const int ID_FILLING_VISIBLE;
	const int ID_LINE_COLOR_PICKER;
	const int ID_FILL_COLOR_PICKER;
	const int ID_LINE_ALPHA_SLIDER;
	const int ID_FILL_ALPHA_SLIDER;

	boost::signals2::signal<void(const std::vector<RectangleShapeConfig>&)> signal_rectangle_shape_config;
};

template<typename T, typename U>
inline void ElementsSetupsPanel::ConnectSignalRectangleShapeConfig(T memfunptr, U objectptr)
{
	signal_rectangle_shape_config.connect(std::bind(memfunptr, objectptr, std::placeholders::_1));
}