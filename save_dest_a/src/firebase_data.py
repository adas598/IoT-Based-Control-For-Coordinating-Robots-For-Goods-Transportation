#!/usr/bin/env python
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
