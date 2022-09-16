#!/usr/bin/env python
# -*- coding: utf-8 -*-


"""!
@file hand.py
@brief Нода руки-хват. Читает сообщение из топика 
/hand_angle и передает ШИМ-сигнал на пин.
"""


import rospy
from std_msgs.msg import Int16
from RPi import GPIO
import pigpio


GPIO.setmode(GPIO.BCM)
pi = pigpio.pi()


def callback(power):
    """!коллбэк на прочитанное сообщение из топика
    @param power сообщение std_msgs/Int16
    """
    pi.set_servo_pulsewidth(12, power.data)
    # print("callback", power.data)


if __name__ == "__main__":
    rospy.init_node("hand")
    subscriber = rospy.Subscriber("hand_angle", Int16, callback)
    rospy.spin()
    GPIO.cleanup()
