#!/usr/bin/env python3
import rospy
import yaml
from drone.msg import Teleop

lxmax, lxmin = -128, 127  
lymax, lymin = -128, 127
rxmax, rxmin = -128, 127
rymax, rymin = -128, 127
lxcenter = 0
lycenter = 0
rxcenter = 0
rycenter = 0


if __name__ == "__main__":
    rospy.init_node("joystick_calibration")
    print("CALIBRATION STARTS")
    rospy.sleep(3)
    print("KEEP STICKS IN CENTER")
    rospy.sleep(3)
    for i in range(25):
        msg = rospy.wait_for_message("joystick_state", Teleop, timeout=None)
        print(msg)
        lxcenter += msg.lx
        lycenter += msg.ly
        rxcenter += msg.rx
        rycenter += msg.ry
    lxcenter /= 25
    lycenter /= 25
    rxcenter /= 25
    rycenter /= 25

    print("MOVE STICKS TO EXTREME POSITIONS")
    rospy.sleep(3)

    for i in range(120):
        msg = rospy.wait_for_message("joystick_state", Teleop, timeout=None)
        print(msg)

        if lxmax < msg.lx:
            lxmax = msg.lx
        if lxmin > msg.lx:
            lxmin = msg.lx

        if lymax < msg.ly:
            lymax = msg.ly
        if lymin > msg.ly:
            lymin = msg.ly

        if rxmax < msg.rx:
            rxmax = msg.rx
        if rxmin > msg.rx:
            rxmin = msg.rx

        if rymax < msg.ry:
            rymax = msg.ry
        if rymin > msg.ry:
            rymin = msg.ry

    print(
    f"""
        lxmin: {lxmin}\tlxcenter: {lxcenter}\tlxmax: {lxmax}
        lymin: {lymin}\tlycenter: {lycenter}\tlymax: {lymax}
        rxmin: {rxmin}\trxcenter: {rxcenter}\trxmax: {rxmax}
        rymin: {rymin}\trycenter: {rycenter}\trymax: {rymax}
    """
    )

    lxscale = 100 / (lxcenter + 100)
    lyscale = 100 / (lycenter + 100)
    rxscale = 100 / (rxcenter + 100)
    ryscale = 100 / (rycenter + 100)

    with open("/usr/local/drone_ros/src/drone/config/calibration.yaml", 'r') as f:
        calibration = yaml.safe_load(f)
    
    calibration['lxscale'] = lxscale
    calibration['lyscale'] = lyscale
    calibration['rxscale'] = rxscale
    calibration['ryscale'] = ryscale


    with open("/usr/local/drone_ros/src/drone/config/calibration.yaml", 'w') as f:
        calibration = yaml.dump(calibration, f, default_flow_style=False)