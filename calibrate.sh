. /home/pi/drone_ros/devel/setup.bash
systemctl stop oceanika.service
echo "oceanika.service stop"
echo "SENSOR CALIBRATION"
sleep 2
rosrun drone calibration.py
sleep 2
echo "SENSOR CALIBRATION DONE"
sleep 2
echo "JOYSTICK CALIBRATION"
sleep 2
roslaunch drone calibration.launch
sleep 2 
"JOYSTICK CALIBRATION DONE"
echo "resuming oceanica.service"
systemctl restart oceanika.service

