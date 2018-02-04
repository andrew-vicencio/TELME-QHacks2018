import wave, struct
from transcribe import main
waveFile = wave.open('recordings/0001.wav', 'r')
main(waveFile)