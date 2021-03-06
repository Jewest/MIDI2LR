/*
  ==============================================================================

	VersionChecker.h
	Created: 19 Aug 2015 1:21:14pm
	Author:  Parth, Jaffe

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
  ==============================================================================
*/
#ifndef VERSIONCHECKER_H_INCLUDED
#define VERSIONCHECKER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

// checks to see if we are running the latest version or not
class VersionChecker : public Thread,
	public AsyncUpdater
{
public:
	VersionChecker();

	// Thread interface
	virtual void run() override;

	// AsyncUpdater interface
	virtual void handleAsyncUpdate() override;

private:
	int _newVersion;
	ScopedPointer<DialogWindow> _dialog;
};



#endif  // VERSIONCHECKER_H_INCLUDED
