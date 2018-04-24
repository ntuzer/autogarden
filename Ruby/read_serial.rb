require 'serialport'
require "json"

FILENAME = "test1.txt"
device = Dir["/dev/tty.usb*"][0]
baud_rate = 9600

portal = SerialPort.new(device, 9600, 8, 1, SerialPort::NONE)
File.exist?(FILENAME) ? nil : File.open(FILENAME, "w")
data_logs = File.open(FILENAME, "a")
hsh = {};
semaphore = Mutex.new

thr = Thread.new {
  while true do
    while (i = portal.gets.chomp) do       # see note 2
      semaphore.synchronize {

        begin
          hsh = JSON.parse(i)
        rescue
          next
        end

        hsh.each do |k, v|
          hsh[k] = v.to_f
        end

        data_logs.puts hsh
      }
    end
  end
}

thr2 = Thread.new {
  while true do
    puts "Enter: "
    input = gets.chomp
    puts "You entered " + input
    puts " "
    semaphore.synchronize {
      puts "---------------"
      puts "temp: #{hsh["temperature"]}"
      puts "humidity: #{hsh["humidity"]}"
      puts "ds18: #{hsh["ds18b20"]}"
      puts "soil: #{hsh["soil"]}"
      puts "---------------"
    }

  end
}

[thr,thr2].each { |t| t.join }
