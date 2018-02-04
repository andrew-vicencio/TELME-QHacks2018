import requests
import json
import credentials
 
def analyze_tone(text):
    usern = '66f34122-cf4e-408f-ac88-743a2e60f699'
    passw = 'Cw2kWm8Cfku7'
    #watsonUrl = 'https://gateway.watsonplatform.net/tone-analyzer-beta/api/v3/tone?version=2016-05-18'
    watsonUrl='https://gateway.watsonplatform.net/tone-analyzer/api/v3/tone?version=2016-05-19'
    headers = {"content-type": "text/plain"}
    print(text)
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
    #welcome()
     
    #data = input("Enter some text to be analyzed for tone analysis by IBM Watson (Q to quit):\n")
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
