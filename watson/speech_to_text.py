from __future__ import print_function
import json
from os.path import join, dirname
from watson_developer_cloud import SpeechToTextV1
import credentials
from analyze_tone import analyze

speech_to_text = SpeechToTextV1(
    username = "4c20aefe-d09b-448d-a30a-f4fed6ef1bb8",
    password = "tvZZ6pF6ASrj",
    x_watson_learning_opt_out=False
)

#print(json.dumps(speech_to_text.models(), indent=2))

#print(json.dumps(speech_to_text.get_model('en-US_BroadbandModel'), indent=2))

with open(join(dirname(__file__), 'recordings/0002.wav'),
          'rb') as audio_file:
    json_text=((speech_to_text.recognize(
        audio_file, content_type='audio/wav', timestamps=True,
        word_confidence=False)))
    sec=int(json_text['results'][0]['alternatives'][0]['timestamps'][-1][2])
    #print(json_text['results'][0]['alternatives'][0]['transcript'])
    
  	#Provide json to mongo database
#json_analysis=analyze(json_text)
json_analysis=analyze(json_text['results'][0]['alternatives'][0]['transcript'],sec )
print(json_analysis)


#Analyze Tone and provide to mongo database