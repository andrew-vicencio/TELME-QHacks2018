from __future__ import print_function
import json
from os.path import join, dirname
from watson_developer_cloud import SpeechToTextV1
import credentials

speech_to_text = SpeechToTextV1(
    username = credentials.login['username-speech'],
    password = credentials.login['password-speech'],
    x_watson_learning_opt_out=False
)

print(json.dumps(speech_to_text.models(), indent=2))

print(json.dumps(speech_to_text.get_model('en-US_BroadbandModel'), indent=2))

with open(join(dirname(__file__), 'recordings/0001.wav'),
          'rb') as audio_file:
    print(json.dumps(speech_to_text.recognize(
        audio_file, content_type='audio/wav', timestamps=False,
        word_confidence=False),
                     indent=2))