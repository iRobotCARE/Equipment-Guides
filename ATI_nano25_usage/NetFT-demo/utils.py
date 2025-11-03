import NetFT

class NetFTWrapper:
    def __init__(self, ip, calibrate_data=[0, 0, 0, 0, 0, 0], scale=1e6, decimals=5):
        """Get sensor's data and apply calibration and scaling.

        Args:
            ip (str): The IP address of the NetFT sensor. Usually the IP is 192.168.1.1.
            calibrate_data (list): Calibration data for the sensor.
            scale (float): Scaling factor for the sensor data.
            decimals (int): Number of decimal places to round the sensor data.

        """
        self.sensor = NetFT.Sensor(ip=ip)
        self.calibrate_data = calibrate_data
        self.scale = scale
        self.decimals = decimals

    def get_scaled_measurement(self):
        """data's unit is N and Nm after scaling.
        Returns:
            list: Scaled and calibrated measurement data from the sensor.    
        """
        data = self.sensor.getMeasurement()
        for i in range(6):
            data[i] /= self.scale
            data[i] += self.calibrate_data[i]
            data[i] = round(data[i], self.decimals)
        return data
