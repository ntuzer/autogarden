require "serialport"
require "json"

FILENAME = "test1.txt"
device = Dir["/dev/tty.usb*"][0]  #may be different for you
baud_rate = 9600

portal = SerialPort.new(device, baud_rate, 8, 1, SerialPort::NONE)
File.exist?(FILENAME) ? nil : File.open(FILENAME, "w")
data_logs = File.open(FILENAME, "a")

while true do
   while (i = portal.gets.chomp) do       # see note 2
      begin
        hsh = JSON.parse(i)
      rescue
        next
      end

      hsh.each do |k, v|
        hsh[k] = v.to_f
      end

      data_logs.puts hsh
      puts "temp: #{hsh["temperature"]}"
      puts "humidity: #{hsh["humidity"]}"
      puts "ds18: #{hsh["ds18b20"]}"
      puts "soil: #{hsh["soil"]}"
      puts "---------------"
    end
end


portal.close
