```
    ssh ubuntu@192.168.88.1 (password: ubuntu)
    Расширить Gparted(Linux). Выбрать раздел sdc2 -> Resize/Move the selected partition 
    -> Передвинуть ползунок вправо до конца -> Apply all operations

    web server 192.168.88.1:8080
    настройка моторов - /home/ubuntu/drone_ros/src/drone/config/oceanic.yaml
    настройка пид - /home/ubuntu/drone_ros/src/drone/config/pid.yaml

    Калибровка - /home/ubuntu/drone_ros/calibrate.sh

    mkdir -p {PROJECT}/src
    cd ~{PROJECT}/src
    roscreate_pkg drone roscpp rospy std_msgs geometry_msgs message_generation
    roscreate_pkg drone_description rospy rviz sensor_msgs tf urdf xacro
    cd ~/{PROJECT}
    git pull
```