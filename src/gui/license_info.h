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

#include "Resource.h"

#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/listbox.h>
#include <wx/textctrl.h>

#include <string>
#include <vector>
#include <utility>
#include <algorithm>


class LicenseInformationDialog : public wxDialog
{
public:

	LicenseInformationDialog();

private:

	void CollectLicenses();

	void SlotSelectLicense(wxCommandEvent& event);
	void SelectLicense(const std::string& map_key);

	wxListBox* license_select_list_box;
	wxTextCtrl* text_view_ctrl;

	typedef std::pair<std::string, std::string> string_pair;

	std::vector< std::pair<std::string, std::string> > collected_licenses;
};