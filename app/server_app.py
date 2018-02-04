from aiohttp import web
import socketio
from pymongo import MongoClient
import json
from bson.json_util import loads,dumps

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
    await delete_from_database()
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


@sio.on('data')
def print_data(request):

    print(request.data)

app.router.add_get('/',handle)

if __name__ =='__main__':
    web.run_app(app)

