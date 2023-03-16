#flasssssk

import cv2
from flask import Flask
from flask import request
import base64
import json
import face_recognition

app = Flask(__name__)

@app.route("/")
def hello_world():
    return "<p>Hello, World!</p>"

@app.route("/api1")
def apii1():
    return "this is api1, World:" + request.args.get("username")


@app.route("/api2", methods=['GET','POST'])
def email():
    return "inseert image: " + request.form.get("email")

#cv2.imshow("show",img)

@app.route('/api3', methods=['POST'])
def upload_file():
     img1 = data_uri_to_cv2_img(request.form.get("file1"))
     img2 = data_uri_to_cv2_img(request.form.get("file2"))
     img3 = data_uri_to_cv2_img(request.form.get("file3"))
     img4 = data_uri_to_cv2_img(request.form.get("file4"))
     
     first_person_encoding=face_recognition.face_encodings(img1)[0]
     second_person_encoding=face_recognition.face_encodings(img2)[0]
     third_person_encoding=face_recognition.face_encodings(img3)[0]
     known_face_encodings=[first_person_encoding, second_person_encoding,third_person_encoding]
     known_face_names=["dep", "rohani","beckam"]

     unknown_person_image_encoding=face_recognition.face_encodings(img4)[0]

     face_distances=face_recognition.face_distance(known_face_encodings,unknown_person_image_encoding)
#search known persons to identify unknown image 
     #i=0 is first person...
     retData = {}
     for i,face_distance in enumerate(face_distances):
         retData[known_face_names[i]]=(1-face_distance)*100
         print('the unknown person is {:.3}%" similar to {}'.format((1-face_distance)*100,known_face_names[i]))
     
    #  retData["status"]="ok"
     return json.dumps(retData)
 


import numpy as np

def data_uri_to_cv2_img(uri):
    encoded_data = uri.split(',')[1]
    nparr = np.fromstring(base64.b64decode(encoded_data), np.uint8)
    img = cv2.imdecode(nparr, cv2.IMREAD_COLOR)
    return img




app.run(host='0.0.0.0')
