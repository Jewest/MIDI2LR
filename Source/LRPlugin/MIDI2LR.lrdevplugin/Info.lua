--[[----------------------------------------------------------------------------

Info.lua

MIDI2LR Plugin properties
 
This file is part of MIDI2LR. Copyright 2015 by Rory Jaffe, derived from code
by Parth.

MIDI2LR is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later version.

MIDI2LR is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
MIDI2LR.  If not, see <http://www.gnu.org/licenses/>. 
------------------------------------------------------------------------------]]

return {
    LrSdkVersion = 6.0,
    LrToolkitIdentifier = 'com.rsjaffe.midi2lr',
    LrPluginName = 'MIDI2LR',
    LrInitPlugin = 'MIDI2LR_Client.lua', -- Main client logic
    LrForceInitPlugin = true,
    LrExportMenuItems = { -- Needs to provide at least a menu item
        {
            title = "About",
            file = "About.lua",
        },
        {
            title = "Start MIDI2LR",
            file = "LaunchAppFromMenu.lua"
        },
    },
    VERSION = { major=0, minor=5, revision=0}
}
