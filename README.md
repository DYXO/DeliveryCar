# Delivery Car

## Get start
### Step 1 install pigpio
go to this page and follow it
https://abyz.me.uk/rpi/pigpio/download.html
### Step 2 clone this Project
```
git clone https://github.com/DYXO/DeliveryCar.git
```
### Step 3 cd to the directory
```
cd Delivery_Car
```
```
mkdir build
```
### Step 4 build
```
cmake ../
```
```
make
```
### Step 5 run the project
```
sudo ./DeliveryRobot
```

## If pcm erro
<details>
  <summary>expand</summary>


1.Modify ALSA Configuration Files: Edit the ALSA configuration files to allow root access to audio devices. These files are usually located at /etc/asound.conf or ~/.asoundrc. Add or modify the following content:
```
pcm.!default {
    type hw
    card 0
}

ctl.!default {
    type hw
    card 0
}
```
2.Adjust Device Permissions: Ensure that the audio device permissions allow root access. You can change the permissions with:
```
sudo chmod 666 /dev/snd/*
```
3.Use setuid: Set your program to run with root privileges using setuid. First, make sure your program is executable, then use the following commands:
```
sudo chown root:root your_program
```
```
sudo chmod u+s your_program
```
Then try again
## if still not work, just give up the sound 
go to the branch IfAudioNotWork or you can just comment out this following lines in main
line12:
```
//soundplayer warning("Sound.wav");
```
line12:
```
//std::thread warning_sound(&soundplayer::play,&warning);
```

</details>

## If gpio can't init
<details>
  <summary>expand</summary>
  
1.Find the process using the port
  
```
sudo lsof -i :8888
```

2.Terminate the process using the port: Once you have identified the process using the port, you can terminate it with the following command:

```
sudo kill -9 <PID>
```

Replace <PID> with the actual Process ID.

  
3.Confirm the process has been terminated: Run the following command again to ensure no process is using port 8888:

```
sudo lsof -i :8888
```

run it again

</details>

## Diagram of the hardware connection
![image](https://github.com/DYXO/Delivery_Car/blob/main/figure/Connection.png)

## Diagram of the physical connection
### ultrasonic
![image](https://github.com/DYXO/Delivery_Car/blob/main/figure/ultrasonic.jpg)
### infrared
![image](https://github.com/DYXO/Delivery_Car/blob/main/figure/infrared.jpg)
### motor driver
![image](https://github.com/DYXO/Delivery_Car/blob/main/figure/motordriver.jpg)

## Media
https://www.instagram.com/p/C-n34MBs34e/?igsh=MXh5bmt6bDdld2psMA==
![image](https://github.com/DYXO/Delivery_Car/blob/main/figure/QRcode.jpg)
