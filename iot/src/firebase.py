import pyrebase
firebaseConfig = {
    "apiKey": "AIzaSyA89kvBNFAz8wgvS297EDB_K_eSsJBXF4I",
    "authDomain": "fir-realtime-91e53.firebaseapp.com",
    "databaseURL": "https://fir-realtime-91e53-default-rtdb.firebaseio.com",
    "projectId": "fir-realtime-91e53",
    "storageBucket": "fir-realtime-91e53.appspot.com",
    "messagingSenderId": "540756156225",
    "appId" : "1:540756156225:web:e45d9d4fe770267b820bc0",
    "measurementId" : "G-GB8BKV9R3W"
  };
firebase = pyrebase.initialize_app(firebaseConfig)

storage = firebase.storage()
database = firebase.database()
#database.child("Baggage_Status_Transit").update({"Luggage_A":"Ready To Move"})
#data = {"Luggage_A":"Ready To Move","Luggage_B":"In Motion","Unidentified": "Needs Attention"}#,"Motor":"Working As Expected","LIdar":"Working As Expected"}
#database.set(data)

## database.child("Baggage_Status_Transit").update({"Luggage_A":"Read To Move"}) to update into a single property of a child
##key_a = (database.child("Baggage_Status_Transit").child("Luggage_A").get()).val() --an example to get the value by naming the key--
