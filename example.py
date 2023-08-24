"""
Demonstration of the GazeTracking library.
Check the README.md for complete documentation.
"""

import cv2
from gaze_tracking import GazeTracking
import serial

# Ardunio Serial Connection
# Set port accordingly
arduino = serial.Serial(port='COM8', baudrate=9600, timeout=.1)

gaze = GazeTracking()
webcam = cv2.VideoCapture(0)

while True:
    # We get a new frame from the webcam
    _, frame = webcam.read()

    # We send this frame to GazeTracking to analyze it
    gaze.refresh(frame)

    frame = gaze.annotated_frame()
    text = ""

   # if gaze.is_blinking():
   #     text = "Blinking"
    if gaze.is_left():
        value=-1
        text = "Looking left" + str(value)
        arduino.write(str.encode('LEFT\n'))
    elif gaze.is_right():
        value=1
        text = "Looking right" + str(value)
        arduino.write(str.encode('RIGHT\n'))
    elif gaze.is_down():
        value=-2
        text = "Looking down" + str(value)
        arduino.write(str.encode('BACKWARD\n'))
    elif gaze.is_up():
        value=2
        text = "Looking up" + str(value)
        arduino.write(str.encode('FORWARD\n'))
    elif gaze.is_center():
        value=0
        text = "Looking center" + str(value)
        arduino.write(str.encode('CENTER\n'))
    else:
        text = "Undefined condition: "
        arduino.write(str.encode('STOP\n'))

    cv2.putText(frame, text, (90, 60), cv2.FONT_HERSHEY_DUPLEX, 1.6, (147, 58, 31), 2)

    left_pupil = gaze.pupil_left_coords()
    right_pupil = gaze.pupil_right_coords()
    cv2.putText(frame, "Left pupil:  " + str(left_pupil), (90, 130), cv2.FONT_HERSHEY_DUPLEX, 0.9, (147, 58, 31), 1)
    cv2.putText(frame, "Right pupil: " + str(right_pupil), (90, 165), cv2.FONT_HERSHEY_DUPLEX, 0.9, (147, 58, 31), 1)

    cv2.imshow("Demo", frame)

    if cv2.waitKey(1) == 27:
        break
   
webcam.release()
cv2.destroyAllWindows()
