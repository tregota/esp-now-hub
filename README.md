### ESP-NOW Receiver installation on Raspberry Pi 4

### Dependencies

> sudo apt install git docker docker-compose

### Hardware installation

With the ESP32 connected to UART3, the python script can pass ESP-NOW messages to NTFY  

**Connect ESP32 RX to GPIO4 (UART3 TX), and TX to GPIO5 (UART3 RX)**  

**Add the following line to the end of config.txt**

> dtoverlay=uart3

run build.sh to create an esp-now-receiver docker image  

### NTFY installation  

create cache directory for data retention
> sudo mkdir /var/cache/ntfy  
sudo chown 1000:1000 /var/cache/ntfy  

create config folder in /etc and download default config
> sudo mkdir /etc/ntfy/  
sudo chown 1000:1000 /etc/ntfy/  
wget https://raw.githubusercontent.com/binwiederhier/ntfy/main/server/server.yml -O /etc/ntfy/server.yml

in **/etc/ntfy/server.yml** uncomment and set **base-url** to **http://{server-ip}**  
uncomment `upstream-base-url: "https://ntfy.sh"` to support ios app push notificaions  
  
add your user to docker group  
> sudo gpasswd -a $USER docker  
newgrp docker  

prevent anonymous access example: https://docs.ntfy.sh/config/#example-private-instance

### Run Docker Compose

>  docker-compose up -d  

check logs with
> docker-compose logs -f -t
