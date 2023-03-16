from flask import Flask
from flask import request
from flask import send_from_directory
from werkzeug.utils import secure_filename
import json
import os
#
import numpy as np
import cv2
import face_recognition

tempFiles = {}
targetFile = None

app = Flask(__name__)


@app.route("/")
def root_path():
    return send_from_directory("static_pages", "web1.html")


@app.route('/<path:filename>')
def serve_file(filename):
    root_dir = os.path.abspath(os.path.dirname(__file__))
    file_path = os.path.join(root_dir, 'static_pages', filename)
    return send_from_directory(os.path.dirname(file_path), os.path.basename(file_path))


@app.route("/setsample", methods=['POST'])
def set_sample():
    file = request.files['file']
    filename = secure_filename(file.filename)
    tempFiles[filename]=file
    return "done"

@app.route("/settarget", methods=['POST'])
def set_target():
    targetFile = request.files['file']
    return "done"

@app.route("/clear", methods=['POST'])
def clear():
    tempFiles = {}
    targetFile = None
    return "done"


@app.route("/calc", methods=['POST'])
def calc():
    known_face_encodings = []
    known_face_names = []
    for key, value in tempFiles.items():
        img_data = np.frombuffer(value.read(), np.uint8)
        img = cv2.imdecode(img_data, cv2.IMREAD_COLOR)        
        known_face_encodings.append( face_recognition.face_encodings(img)[0] )
        known_face_names.append( key )
    
    unknown_person_image_encoding=face_recognition.face_encodings(targetFile)[0]


    face_distances=face_recognition.face_distance(known_face_encodings,unknown_person_image_encoding)

    retData = {}
    for i,face_distance in enumerate(face_distances):
        retData[known_face_names[i]]=(1-face_distance)*100
     
    return json.dumps(retData)


app.run(host='0.0.0.0')
