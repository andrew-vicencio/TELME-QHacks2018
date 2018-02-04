from aiohttp import web
import socketio
#import websocket


CHUNK = 1024
CHANNELS = 1
RATE = 44100

#wsURI = 'wss://stream.watsonplatform.net/speech-to-text/api/v1/recognize' + '?watson-token'
#session = aiohttp.ClientSession.ws_connect(wsURI)



sio = socketio.AsyncServer(async_mode='aiohttp')
app = web.Application()
sio.attach(app)


async def handle(request):
    return web.Response(text="Hello World")




#microcontroller emits event called dataFromMicro
#@sio.on('dataFomMicro')
#async def getDataFromMicro(request):




@sio.on('data')
def print_data(request):

    print(request.data)

app.router.add_get('/',handle)

if __name__ =='__main__':
    web.run_app(app)

