# setup script for cs410 hw1 sp15

$dry = false

def exec_err(cmd)
  puts " -> #{cmd}"
  return if $dry
  output = `#{cmd} 2> /dev/null`
  if $?.exitstatus != 0
    puts "ERROR running command: #{cmd}"
    puts "Output from command:\n#{output}"
    exit
  end
end

def exec_env(hash, cmd)
  puts " -> #{cmd}"
  return if $dry
  hash.each do |key,val|
    ENV[key] = val
  end
  output = `#{cmd} 2> /dev/null`
  if $?.exitstatus != 0
    puts "ERROR running command: #{cmd}"
    puts "Output from command:\n#{output}"
    puts "\nDid you remember to run the 'module load' commands first?\n"
    exit
  end
end

puts "Downloading files..."
exec_err("wget http://download.icu-project.org/files/icu4c/52.1/icu4c-52_1-RHEL6-x64.tgz")
exec_err("wget http://web.engr.illinois.edu/~massung1/files/meta-crf-model.tar.gz")
exec_err("wget http://web.engr.illinois.edu/~massung1/files/two-cities.txt")
exec_err("rm -rf meta")
exec_err("git clone https://github.com/meta-toolkit/meta.git")

puts "Uncompressing files..."
exec_err("tar -xzf icu4c-52_1-RHEL6-x64.tgz")
exec_err("tar -xzf meta-crf-model.tar.gz")
exec_err("rm icu4c-52_1-RHEL6-x64.tgz")
exec_err("rm meta-crf-model.tar.gz")

puts "Configuring MeTA..."
Dir.chdir("meta") {
  exec_err("git checkout profile")
  exec_err("git submodule update --init --recursive")
  exec_err("mkdir build/")
  exec_err("mv ../two-cities.txt build/")
  exec_err("mv ../meta-crf-model/ build/crf/")
  exec_err("cp config.toml build/")
  Dir.chdir("build") {
    exec_env({"CXX" => "/software/gcc-4.8.2/bin/g++",
              "CC" => "/software/gcc-4.8.2/bin/gcc"},
             "cmake ../ -DCMAKE_BUILD_TYPE=Debug -DICU_ROOT=#{Dir.pwd}/usr/local/")
  }
}
exec_err("rm readme.txt") # not useful

puts "Done! You can now run make from inside the meta/build/ directory."
