#######################################################
# TV Lights
# by Bithead942
#
# For a Raspberry Pi 3 running Python 2.7.x
# Requires Raspberry Pi camera connected to CSI port
# Requires Xbee USB Dongle with Xbee Radio
#######################################################

import picamera
import serial
from PIL import Image

bFirstBlack = 0
ser = serial.Serial('/dev/ttyUSB0', 9600)
        
while True:
    with picamera.PiCamera() as camera:
        camera.resolution = (32,32)
        camera.capture('/home/pi/Desktop/image.jpg')

    im = Image.open("/home/pi/Desktop/image.jpg")
    pix = im.load()

    iRedSum = 0
    iGreenSum = 0
    iBlueSum = 0

    [iRed,iGreen,iBlue] = pix[15,15]
    iRedSum = iRedSum + iRed
    iGreenSum = iGreenSum + iGreen
    iBlueSum = iBlueSum + iBlue

    [iRed,iGreen,iBlue] = pix[15,16]
    iRedSum = iRedSum + iRed
    iGreenSum = iGreenSum + iGreen
    iBlueSum = iBlueSum + iBlue

    [iRed,iGreen,iBlue] = pix[15,17]
    iRedSum = iRedSum + iRed
    iGreenSum = iGreenSum + iGreen
    iBlueSum = iBlueSum + iBlue

    [iRed,iGreen,iBlue] = pix[16,15]
    iRedSum = iRedSum + iRed
    iGreenSum = iGreenSum + iGreen
    iBlueSum = iBlueSum + iBlue

    [iRed,iGreen,iBlue] = pix[16,16]
    iRedSum = iRedSum + iRed
    iGreenSum = iGreenSum + iGreen
    iBlueSum = iBlueSum + iBlue

    [iRed,iGreen,iBlue] = pix[16,17]
    iRedSum = iRedSum + iRed
    iGreenSum = iGreenSum + iGreen
    iBlueSum = iBlueSum + iBlue

    [iRed,iGreen,iBlue] = pix[17,15]
    iRedSum = iRedSum + iRed
    iGreenSum = iGreenSum + iGreen
    iBlueSum = iBlueSum + iBlue

    [iRed,iGreen,iBlue] = pix[17,16]
    iRedSum = iRedSum + iRed
    iGreenSum = iGreenSum + iGreen
    iBlueSum = iBlueSum + iBlue

    [iRed,iGreen,iBlue] = pix[17,17]
    iRedSum = iRedSum + iRed
    iGreenSum = iGreenSum + iGreen
    iBlueSum = iBlueSum + iBlue

    iRedAvg = iRedSum / 9
    iGreenAvg = iGreenSum / 9
    iBlueAvg = iBlueSum / 9

    iGreenAvg = iGreenAvg /3  #Account for green wall

    if iRedAvg >= 3 and iGreenAvg >= 3 and iBlueAvg >= 3:
        MyString = 'r=%i,g=%i,b=%i' % (iRedAvg, iGreenAvg, iBlueAvg)
        print "Sending %s" % MyString
        ser.write('%s\n' % MyString)
        bFirstBlack = 0
    else:
        if bFirstBlack == 0:
           MyString = 'r=0,g=0,b=0'
           print "Sending %s" % MyString
           ser.write('%s\n' % MyString)
           bFirstBlack = 1
        else:
           print "Not sent"

    #break;
