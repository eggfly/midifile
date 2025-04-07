import serial  
import mido  
import argparse
import time

time.sleep(1)


parser = argparse.ArgumentParser(description='发送MIDI文件到串口设备')  
parser.add_argument('port', type=str, help='串口设备路径，例如 /dev/cu.usbserial-69526606B6')  
parser.add_argument('midi_file', type=str, help='MIDI文件路径，例如 /path/to/file.mid')  
args = parser.parse_args()
 
mid = mido.MidiFile(args.midi_file, clip=True, debug=True)  
 
port = None

if args.port == 'pseudo':  
    print("使用虚拟串口")
else:
    port = serial.Serial(args.port, 115200) 

# print midi info 
# mid.ticks_per_beat
# mid.length
print("ticks_per_beat: ", mid.ticks_per_beat)
print("length: ", mid.length)

print(mid.print_tracks())


merged = mid.merged_track

for msg in mid.play():
    b = msg.bin()  
    # print("len=", len(b), b, msg)
    print("len={0}, {1} {2}".format(len(b), msg, b))
    if port:
        port.write(b) 
