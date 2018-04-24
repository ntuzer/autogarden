require 'serialport'

FILENAME = "test1.txt"
device = Dir["/dev/tty.usb*"][0]
portal = SerialPort.new(device, 9600, 8, 1, SerialPort::NONE)
data_log = File.exist?(FILENAME) ? File.open(FILENAME, "a") : File.open(FILENAME, "w")
