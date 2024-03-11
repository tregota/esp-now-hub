import serial
import time
from datetime import datetime
import requests
import json
import glob

PORTS = "/dev/ttyAMA*"
BAUDRATE = 115200

def wait_for_serial_port() -> serial.Serial:
    ports = glob.glob(PORTS)
    while True:
        for port in ports:
            try:
                ser = serial.Serial(port, BAUDRATE, timeout=1)
                print(f"Connected to {port} at {BAUDRATE} baud", flush=True)
                return ser
            except serial.SerialException:
                pass
            time.sleep(1)

def listen_to_serial_port(ser: serial.Serial):
    while True:
        line: str = ser.readline().decode('utf-8').strip()
        timestamp = datetime.now().isoformat()
        if line.startswith("ESP-NOW:"):
            ser.write(1)
            _, id, payload, battery = line.split(':')
            print(f"{timestamp} - Publishing '{payload}' to espnow/{id}", flush=True)
            requests.post(f"http://localhost/espnow/{id}", data=json.dumps({
                "timestamp": timestamp,
                "payload": payload,
                "batterylevel": int(battery)
            }))
        elif line != "":
            print(f"{timestamp} - Ignoring malformed message: {line}", flush=True)

if __name__ == "__main__":
    print(f'ESP-NOW receiver starting..', flush=True)
            
    while True:
        print("Waiting for serial connection..", flush=True)
        try:
            ser = wait_for_serial_port()
            listen_to_serial_port(ser)
        except Exception as e:
            print(e, flush=True)