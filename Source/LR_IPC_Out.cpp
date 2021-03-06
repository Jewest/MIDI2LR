/*
  ==============================================================================

	LR_IPC_OUT.cpp
	Created: 2 Aug 2015 12:27:47am
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
#include "LR_IPC_OUT.h"
#include "CommandMap.h"
#include "LRCommands.h"

const int LR_IPC_OUT::LR_OUT_PORT = 58763;

LR_IPC_OUT& LR_IPC_OUT::getInstance()
{
	static LR_IPC_OUT instance;
	return instance;
}

LR_IPC_OUT::LR_IPC_OUT() : InterprocessConnection()
{
	MIDIProcessor::getInstance().addMIDICommandListener(this);
	startTimer(1000);
}

void LR_IPC_OUT::shutdown()
{
	stopTimer();
	disconnect();
}

void LR_IPC_OUT::timerCallback()
{
	if (!isConnected())
		connectToSocket("127.0.0.1", LR_OUT_PORT, 100);
}

void LR_IPC_OUT::addListener(LRConnectionListener *listener)
{
	_listeners.addIfNotAlreadyThere(listener);
}

void LR_IPC_OUT::connectionMade()
{
	for (auto listener : _listeners)
		listener->connected();
}

void LR_IPC_OUT::connectionLost()
{
	for (auto listener : _listeners)
		listener->disconnected();
}

void LR_IPC_OUT::messageReceived(const MemoryBlock& msg)
{

}

void LR_IPC_OUT::sendCommand(const String &command)
{
	if (!isConnected()) return;

	getSocket()->write(command.getCharPointer(), command.length());
}

void LR_IPC_OUT::handleAsyncUpdate()
{
	if (!isConnected()) return;

	String command = _commandToSend + String::formatted(" %d\n", _valueToSend);
	sendCommand(command);
}

void LR_IPC_OUT::handleMidiCC(int midiChannel, int controller, int value)
{
	MIDI_Message cc(midiChannel, controller, true);

	if (!CommandMap::getInstance().messageExistsInMap(cc) ||
		CommandMap::getInstance().getCommandforMessage(cc) == "Unmapped" ||
		find(LRCommandList::ProfileList.begin(),
			LRCommandList::ProfileList.end(),
			CommandMap::getInstance().getCommandforMessage(cc)) != LRCommandList::ProfileList.end())
		return;

	_commandToSend = CommandMap::getInstance().getCommandforMessage(cc);
	_valueToSend = value;
	handleAsyncUpdate();
}

void LR_IPC_OUT::handleMidiNote(int midiChannel, int note)
{
	MIDI_Message note_msg(midiChannel, note, false);

	if (!CommandMap::getInstance().messageExistsInMap(note_msg) ||
		CommandMap::getInstance().getCommandforMessage(note_msg) == "Unmapped" ||
		find(LRCommandList::ProfileList.begin(),
			LRCommandList::ProfileList.end(),
			CommandMap::getInstance().getCommandforMessage(note_msg)) != LRCommandList::ProfileList.end())
		return;

	_commandToSend = CommandMap::getInstance().getCommandforMessage(note_msg);
	_valueToSend = 127;
	handleAsyncUpdate();
}