﻿/*
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

#include "gui/wx_widgets_include.h"

#include "main_window.h"

#include <iostream>
#include <string>
#include <locale>


// Reason for use of raw pointers instead of smart_pointers:
// https://wiki.wxwidgets.org/Avoiding_Memory_Leaks 


class App : 
    public wxApp
{
public:

    App() :
        main_window(nullptr)
    {}

    bool OnInit() override;

private:

    MainWindow* main_window;

    std::unique_ptr<wxLocale> locale;
};