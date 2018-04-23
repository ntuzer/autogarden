require 'serialport'

ser = SerialPort.new("/dev/tty.usbmodem1421", 9600, 8, 1, SerialPort::NONE)


while true do
   while (i = ser.gets.chomp) do       # see note 2
      puts i
      #puts i.class #String
    end
end



# tty.usbmodem1421
