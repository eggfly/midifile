#include "MidiFile.h"
#include "Options.h"
#include <iostream>
#include <iomanip>

using namespace std;
using namespace smf;

int main(int argc, char **argv)
{
	Options options;
	options.process(argc, argv);
	MidiFile midifile;
	if (options.getArgCount() == 0)
		midifile.read(cin);
	else
		midifile.read(options.getArg(1));
	midifile.doTimeAnalysis();
	midifile.linkNotePairs();

	int tracks = midifile.getTrackCount();
	cout << "TPQ: " << midifile.getTicksPerQuarterNote() << endl;
	if (tracks > 1)
		cout << "TRACKS: " << tracks << endl;
	for (int track = 0; track < tracks; track++)
	{
		if (tracks > 1)
			cout << "\nTrack " << track << endl;
		cout << "Tick\tSeconds\tDur\tMessage" << endl;
		for (int event = 0; event < midifile[track].size(); event++)
		{
			// Save midifile[track][event] as a variable
			// to avoid multiple dereferencing
			MidiEvent &midiEvent = midifile[track][event];
			std::string messageType = midiEvent.getMessageTypeString();
			cout << "messageType=" << messageType << ", ";
			bool isText = midiEvent.isText();
			if (isText)
			{
				string content = midiEvent.getMetaContent();
				cout << content << endl;
				continue;
			}

			cout << dec << midiEvent.tick;
			cout << '\t' << dec << midiEvent.seconds;
			cout << '\t';
			if (midiEvent.isNote())
			{
				cout << "isNote, ";
			}
			if (midiEvent.isNoteOn())
			{
				cout << "NoteOn: duration=" << midiEvent.getDurationInSeconds();
			}
			else if (midiEvent.isNoteOff())
			{
				cout << "NoteOff: duration=" << midiEvent.getDurationInSeconds();
			}
			cout << '\t' << "hex=" << hex;
			for (int i = 0; i < midiEvent.size(); i++)
			{
				cout << (int)midiEvent[i] << ' ';
			}
			cout << "size=" << midiEvent.size();
			cout << endl;
		}
	}

	return 0;
}
