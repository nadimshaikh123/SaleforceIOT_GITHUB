import serial
import http.client
import json

conn = http.client.HTTPSConnection("na35.salesforce.com") 

port ='COM4'
baud = 9600
 
ser = serial.Serial(port, baud, timeout=1);
    # open the serial port

if ser.isOpen():
    print(ser.name + ' is open…')
        
    while True:
        if ser.inWaiting() >0: 
            print('Receiving From Arduino.....')
            outputInBytes = ser.readline()
            outputInString = bytes.decode(outputInBytes)       
            print('outputInString  ='+ outputInString)

            SensorNameARD ,SensorValueARD =  outputInString.split(':')

            print('Connecting to Salesforce.....')
            headers = {
            'cache-control': "no-cache",
            'postman-token': "3cd0cf91-13de-b32b-e785-20849723d690",
            'content-type': "application/x-www-form-urlencoded"
            }

            conn.request("POST", "/services/oauth2/token?client_id=3MVG9szVa2RxsqBaIr5CuHZSQWUf393XKBQb8e8oiW4Mi10b.J434YiYMapCHtdjUVRHeUocB3bFm6lpSmCH_%20&client_secret=3266259452801814335&grant_type=password&username=nadim.shaikhn%40tcs.com.learning.WAVE&password=Salesforce%4018OuEiOTdZVF76gHRhJC1P1zz2", headers=headers)

            res = conn.getresponse()
            data = res.read()
            TokenResponse = json.loads(data)

            
            print( TokenResponse  )       
            Token = TokenResponse['access_token']
            print('Access Token =' + Token)

            headers = {
            'content-type': "application/json",
            'authorization': "Bearer " + Token ,
             'cache-control': "no-cache",
            'postman-token': "8c273e2d-38fb-1640-e9b4-6018b19309ca"
            }
            payload = "{\"SensorName\" : \""+SensorNameARD+"\",\"SensorValue\": "+SensorValueARD+"}"
            

            print('Payload Sent to Salesforce ... ' +payload)
            conn.request("POST", "//services/apexrest/Nad_Salesforce_Arduino_IOT", payload, headers)

            res = conn.getresponse()
            data = res.read()

            print('Response Received From Salesforce After Entry...' + data.decode("utf-8"))









