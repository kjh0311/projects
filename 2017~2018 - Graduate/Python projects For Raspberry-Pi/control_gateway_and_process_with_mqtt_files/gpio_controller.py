import RPi.GPIO as GPIO
import time


def RST_TO_LOW():
	GPIO.setmode(GPIO.BCM)
	GPIO.setup(25, GPIO.OUT) ## GPIO 25 output
	GPIO.output(25, True) ## On 25
	time.sleep(1) ## Wait one second
	GPIO.output(25, False) ## Off 25
	time.sleep(1) ## Wait one second


def record_gpio():
	pass
