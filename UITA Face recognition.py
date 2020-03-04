#This is a face recognition script in OpenCV and python and is a
# part of FREE Course named Internet of Things - From beginner to maker
# created by Muhammad Ateeb Aslam - Team UrduITAcademy urduitacademy.com

import cv2
import argparse
import sys
import numpy as np
import os
import time
from PIL import Image
import RPi.GPIO as GPIO
#import nexmo

servoPIN = 17
GPIO.setmode(GPIO.BCM)
GPIO.setup(servoPIN, GPIO.OUT)

p = GPIO.PWM(servoPIN, 50) # GPIO 17 for PWM with 50Hz
#This Block take and Processes command line arguments using ArgumentParser
ap = argparse.ArgumentParser(description="A Face recognition based home security project")
ap.add_argument("-s", "--start",  help = "start home security camera")
ap.add_argument("-d", "--dataset", help = "dataset creator mode. Must be followed by -t or --train")
ap.add_argument("-t", "--train",help = "Train the capture images to create model")

args = ap.parse_args()


#The Detector Block starts here
if args.start:
     #We start by creating a cascadeClassifier, In our case it's haarcascade_frontalface_default already comes with OpenCV installation
    faceDetect = cv2.CascadeClassifier('haarcascade_frontalface_default.xml');
    camera = cv2.VideoCapture(0)     #VideoCapture function calls our webcam
    #We are using Local Binary patterns Histogram  (LBPH) method
    rec = cv2.face.LBPHFaceRecognizer_create();   
    #In OpenCV 3 and above 'load' is replaced by read() and save() replaced by write()
    #In previous versions we had to use load() instead of read() 
    rec.read("recognizer/traindata.yaml")  #Read the trained Model File
    id=0
    font = cv2.FONT_HERSHEY_SIMPLEX
    while(True):
         ret,im = camera.read();   #Reading Frames from Camera
         gray = cv2.cvtColor(im,cv2.COLOR_BGR2GRAY) #Convert Color to gray so that OpenCV can Process it
         faces = faceDetect.detectMultiScale(gray,scaleFactor=1.3,minNeighbors=10,minSize=(20, 20));     
         for(x,y,w,h) in faces:
              cv2.rectangle(im,(x,y),(x+w,y+h),(0,0,170),2) #Build a rectangle around the detected face
              #cv2.imwrite("/var/www/html/detected.jpg",im)
              id=rec.predict(gray[y:y+h,x:x+w]) #Predict the face if matches in dataset
              for a in id:
                  if id[1] < 500:
                    confidence = int(100*(1-(id[1])/300))
                    display_string = str(id)+str(confidence)+'% Face match'
                  cv2.imwrite("/var/www/html/"+str(a)+".jpg",im)
                  cv2.putText(im,display_string,(x,y+h),font,0.55,(0,255,0),2)
                  #if confidence > 75:
                     #Nexmo SMS sendin COde, replace secret and Key with your own
                     #client = nexmo.Client(key='8c7becee', secret='8E4M8HujqjDEznP1')
                     #client.send_message({
                     #            'from': 'Nexmo',
                     #           'to': '923046215397',   #write authenticated cell number
                     #            'text': 'Person Authenticated!',
                     #    })
##                         p.start(1) # Initialization
##                         p.ChangeDutyCycle(5)
##                         print("Duty cycle 5")
##                         time.sleep(0.5)
##                         p.ChangeDutyCycle(7.5)
##                         print("Duty cycle 7.5")
##                         time.sleep(0.5)
##                         p.ChangeDutyCycle(10)
##                         print("Duty cycle 10")
##                         time.sleep(0.5)
##                         p.ChangeDutyCycle(12.5)
##                         print("Duty cycle 12.5")
##                         time.sleep(0.5)
##                         p.ChangeDutyCycle(0)
##                         print("Duty cycle 0")
##                         time.sleep(0.5)
##                         p.stop()
##                  else:
##                    p.stop()
##                    cv2.putText(im, "UnAuthorized", (250, 450), cv2.FONT_HERSHEY_COMPLEX, 1, (0, 0, 255), 2)
         cv2.imshow("image",im);
         if cv2.waitKey(1) == ord("q"):
            break      

    camera.release()           #Release the camera
    cv2.destroyAllWindows()
#Detector block ends here
#Dataset creation block starts

if args.dataset:
    #Creating Directory to save dataset
    path = os.getcwd()  
    print ("The current working directory is %s \n" % path) 
    if (os.path.isdir("dataset")) == False:
     
        path = path+"/dataset"
        try:  
            os.mkdir(path)
        except OSError:  
            print ("Creation of the directory %s failed" % path)
        else:  
            print ("Successfully created the directory %s " % path)
    else:
        print("Directory already exists!")
    #Directory creation part ends here

    #Loading Cascade classifier ...
    faceDetect = cv2.CascadeClassifier('haarcascade_frontalface_default.xml');

    camera = cv2.VideoCapture(0)
    time.sleep(0.1)
    #raw_input was renamed to input in OpenCV3
    id = input('Enter user id')
    samplenum=0;
    while(True):
          ret,im = camera.read();
          gray = cv2.cvtColor(im,cv2.COLOR_BGR2GRAY)
          faces = faceDetect.detectMultiScale(gray,1.3,5);
          for(x,y,w,h) in faces:
             samplenum = samplenum+1;   #organizing person images
             cv2.imwrite("dataset/user."+str(id)+"."+str(samplenum)+".jpg",gray[y:y+h,x:x+w])
             cv2.rectangle(im,(x,y),(x+w,y+h),(0,0,170),2)
             cv2.waitKey(100);
          if(samplenum>100):    #Number of samples we are collecting
             break;
          cv2.imshow("image",im);
          if cv2.waitKey(1) == ord("q"):
            break        

    camera.release()
    cv2.destroyAllWindows()
#Dataset creation Block ends here

#Model Trainig Block starts here
if args.train:
    #creatin directory to save model file
    path = os.getcwd()  
    print ("The current working directory is %s" % path)  
    if (os.path.isdir("recognizer")) == False:
        path = path+"/recognizer"
        try:  
            os.mkdir(path)
        except OSError:  
            print ("Creation of the directory %s failed" % path)
        else:  
            print ("Successfully created the directory %s " % path)
    else:
        print("Directory already exists! Creating Model...")
    #directory creation ends here
    #preparing recognizer...  
    recognizer = cv2.face.LBPHFaceRecognizer_create();
    data_path = 'dataset'   #defining dataset path

    def getImandId(data_path):
        impaths = [os.path.join(data_path,f) for f in os.listdir(data_path)]
        faces = []
        ids = []
        for imagepath in impaths:
            faceim = Image.open(imagepath).convert('L');
            facenp = np.array(faceim,'uint8')
            id=int(os.path.split(imagepath)[-1].split('.')[1])
            faces.append(facenp)
            ids.append(id)
            cv2.imshow("training",facenp)
            cv2.waitKey(10)
        return np.array(ids),faces
    ids,faces = getImandId(data_path)
    recognizer.train(faces,ids)
    recognizer.write('recognizer/traindata.yaml')
    cv2.destroyAllWindows()
#Model training Block ends here
