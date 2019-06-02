import RPi.GPIO as GPIO
import time


GPIO.setmode(GPIO.BCM)
GPIO.setup(25, GPIO.OUT) ## GPIO 25 output
GPIO.output(25, True) ## On 25
#GPIO.output(25, False) ## On 25
time.sleep(1) ## Wait one second
GPIO.output(25, False) ## Off 25
#GPIO.output(25, True) ## Off 25
time.sleep(1) ## Wait one second