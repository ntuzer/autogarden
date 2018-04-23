FILENAME = "test1.txt"
f = File.exist?(FILENAME) ? File.open(FILENAME, "a") : File.open(FILENAME, "w")

f.puts Time.now
