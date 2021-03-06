/*
  ==============================================================================

    MIDISender.cpp
    Created: 22 Aug 2015 9:44:21pm
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
#include "MIDISender.h"

MIDISender::MIDISender()
{
    initDevices();
}

void MIDISender::initDevices()
{
    for (auto idx = 0; idx < MidiOutput::getDevices().size(); idx++)
    {
        auto dev = MidiOutput::openDevice(idx);
        if (dev != nullptr)
            _outputDevices.set(idx, dev);
    }
}

void MIDISender::rescanDevices()
{
    _outputDevices.clear(true);
    initDevices();
}

MIDISender& MIDISender::getInstance()
{
    static MIDISender instance;
    return instance;
}

MIDISender::~MIDISender()
{

}

void MIDISender::sendCC(int midi_channel, int controller, int value)
{
    for (auto dev : _outputDevices)
        dev->sendMessageNow(MidiMessage::controllerEvent(midi_channel, controller, value));
}