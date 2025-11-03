from utils import NetFTWrapper
import time

def main():
    netft = NetFTWrapper(ip="192.168.1.1", calibrate_data=[0, 0, 0, 0, 0, 0], decimals=4)
    while True:
        data = netft.get_scaled_measurement()
        force = data[:3]
        torque = data[3:]
        print("Force (N):", force)
        print("Torque (Nm):", torque)
        time.sleep(1)


if __name__ == "__main__":
    main()