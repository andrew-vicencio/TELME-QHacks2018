from __future__ import print_function
from aiohttp import web
import socketio
from pymongo import MongoClient
import json
from bson.json_util import loads,dumps
import aiohttp_jinja2

from os.path import join, dirname
from watson_developer_cloud import SpeechToTextV1

import requests



URI = 'mongodb://admin:qhacks2018@ds225078.mlab.com:25078/convodb'
client = MongoClient(URI)
#import websocket
db = client['convodb']

CHUNK = 1024
CHANNELS = 1
RATE = 44100

#wsURI = 'wss://stream.watsonplatform.net/speech-to-text/api/v1/recognize' + '?watson-token'
#session = aiohttp.ClientSession.ws_connect(wsURI)




sio = socketio.AsyncServer(async_mode='aiohttp')
app = web.Application()
sio.attach(app)


async def handle(request):
    await insert_to_database()
    result = await read_from_database()
    result = dumps(result)
    #await delete_from_database()
    return web.Response(text=result)
    #return web.Response(text=json.dumps(result))



#microcontroller emits event called dataFromMicro
#@sio.on('dataFomMicro')
#async def getDataFromMicro(request):

async def insert_to_database():
    textCollection = db['Text']
    sampleText = {"Brendan":"Is Sick"}
    textCollection.insert_one(sampleText)

async def read_from_database():
    textCollection = db['Text']
    result = textCollection.find_one()
    print(result)
    return result

async def delete_from_database():
    db['Text'].delete_many({})


def speech_to_text(path):
    speech_to_text = SpeechToTextV1(
    username = "4c20aefe-d09b-448d-a30a-f4fed6ef1bb8",
    password = "tvZZ6pF6ASrj",
    x_watson_learning_opt_out=False
	)
    with open(join(dirname(__file__), path),
	          'rb') as audio_file:
        json_text=((speech_to_text.recognize(
	        audio_file, content_type='audio/wav', timestamps=True,
	        word_confidence=False)))
        sec=int(json_text['results'][0]['alternatives'][0]['timestamps'][-1][2])
    json_analysis=analyze(json_text['results'][0]['alternatives'][0]['transcript'],sec )
    print(json_analysis)
    #Send to server
def analyze_tone(text):
    usern = '66f34122-cf4e-408f-ac88-743a2e60f699'
    passw = 'Cw2kWm8Cfku7'
    #watsonUrl = 'https://gateway.watsonplatform.net/tone-analyzer-beta/api/v3/tone?version=2016-05-18'
    watsonUrl='https://gateway.watsonplatform.net/tone-analyzer/api/v3/tone?version=2016-05-19'
    headers = {"content-type": "text/plain"}
    # print(text)
    data = text
    try:
        r = requests.post(watsonUrl, auth=(usern,passw),headers = headers,
         data=data)
        return r.text
    except:
        return False
 
def display_results(data, syl_sec):
    array=[]
    data = json.loads(str(data))
    #print(data)
    array.append(syl_sec)
    for i in data['document_tone']['tone_categories']:

        for j in i['tones']:
            array.append({"tone_name":j['tone_name'],"score":(str(round(j['score'] * 100,1)))})
    return array
def analyze(data, sec):
    
    if len(data) >= 1:
        if data == 'q'.lower():
            exit
        num_syl=0
        test=data.split()
        for word in test:
            num_syl+=syllables(word)
        syl_sec=(num_syl*60)/sec

        results = analyze_tone(data)
        if results != False:
            
            #display_results(results)
            return display_results(results, syl_sec)
            #exit
        else:
            print("Something went wrong")
    else: print("No data was recieved")
    #return
#main()
def syllables(word):
    count = 0
    vowels = 'aeiouy'
    word = word.lower().strip(".:;?!")
    if word[0] in vowels:
        count +=1
    for index in range(1,len(word)):
        if word[index] in vowels and word[index-1] not in vowels:
            count +=1
    if word.endswith('e'):
        count -= 1
    if word.endswith('le'):
        count+=1
    if count == 0:
        count +=1
    return count


async def get_dataText(request):
    print("we here bois")
    textCollection = db['Text']
    result = await textCollection.find_one()
    result = dumps(result)
    print(result)
    return web.Response(text=result)


async def get_dataAnal(request):
    print("we here bois")
    analysisCollection = db['Analysis']
    result = await analysisCollection.find_one()
    result = dumps(result)
    print(result)
    return web.Response(text=result)

async def home(request):
    context ={}
    response = aiohttp_jinja2.render_template("/website/home.html",request,context)
    response.headers['Content-Language']='en'
    return response



@sio.on('dataStream')
def print_data(request):

    print(request.data)

app.router.add_get('/',home)
app.router.add_get('/getDataText',get_dataText)
app.router.add_get('/getDataAnalysis',get_dataAnal)

if __name__ =='__main__':
    web.run_app(app)

