#
# Rakefile for EFI Hello world
#
require 'rake/clean'
require 'rake/packagetask'

# case `uname -m`
# when /i[3456789]86/
#   ARCH = :x86
# when /x86.64/
#   ARCH = :x64
# when /aarch64/
#   ARCH = :aa64
# else
#   ARCH = :unknown
# end

PATH_BIN        = "bin/"
PATH_SRC        = "src/"
PATH_OBJ        = "obj/"
PATH_MNT        = "mnt/"
PATH_EFI_BOOT   = "#{PATH_MNT}EFI/BOOT/"
PATH_INC        = "#{PATH_SRC}include/"
PATH_OVMF       = "var/OVMF.fd"

if RUBY_PLATFORM =~ /darwin/ then
  LLVM_PREFIX     = `brew --prefix llvm`.gsub(/\n/, '')
  CC      = ENV['CC'] || "#{LLVM_PREFIX}/bin/clang"
  LD      = ENV['LD'] || "#{LLVM_PREFIX}/bin/lld-link"
else
  CC      = ENV['CC'] || "clang"
  LD      = ENV['LD'] || "lld-link-4.0"
end
CFLAGS  = "-Os -target x86_64-pc-win32-coff -std=c99 -fno-stack-protector -fshort-wchar -mno-red-zone -nostdlibinc -I #{PATH_INC} -Wall -Wpedantic"
AS      = ENV['AS'] || "nasm"
AFLAGS  = "-s -I #{ PATH_SRC } -f win64"
LFLAGS  = "-subsystem:efi_application -nodefaultlib -entry:efi_main"

INCS  = [FileList["#{PATH_SRC}*.h"], FileList["#{PATH_INC}*.h"]]

CLEAN.include(FileList["#{PATH_BIN}**/*"])
CLEAN.include(FileList["#{PATH_OBJ}**/*"])

directory PATH_OBJ
directory PATH_BIN
directory PATH_EFI_BOOT

TASKS = [ :main ]

TASKS.each do |t|
  task t => [t.to_s + ":build"]
end

desc "Defaults"
task :default => [PATH_OBJ, PATH_BIN, TASKS].flatten

desc "Run with QEMU"
task :run => [:default, PATH_EFI_BOOT, PATH_OVMF] do
  FileUtils.cp("#{PATH_BIN}bootx64.efi", "#{PATH_EFI_BOOT}BOOTX64.EFI")
  sh "qemu-system-x86_64 -bios #{ PATH_OVMF } -monitor stdio -drive file=fat:ro:mnt"
end


def make_efi(cputype, target, src_tokens, options = {})
  case cputype.to_sym
  when :x64
    efi_arch = 'x86_64'
    efi_suffix = 'x64'
  when :x86
    efi_arch = 'ia32'
    efi_suffix = 'ia32'
  else
    efi_arch = cputype.to_s
    efi_suffix = efi_arch
  end

  path_obj      = "#{PATH_OBJ}#{efi_suffix}/"
  directory path_obj

  efi_obj_so    = "#{path_obj}#{target}.so"
  if options[:no_suffix]
    efi_output    = "#{PATH_BIN}#{target}.efi"
  else
    efi_output    = "#{PATH_BIN}#{target}#{efi_suffix}.efi"
  end

  srcs = src_tokens.map do |s|
    if s !~ /\.\w+/
      s += '.c'
    end
    if s !~ /\//
      s = "#{PATH_SRC}#{s}"
    end
    s
  end

  objs = srcs.map do |src|
    mod_name = File.basename(src, '.*')
    obj = "#{path_obj}#{mod_name}.o"

    case File.extname(src)
    when '.c'
      file obj => [ src, INCS, path_obj ].flatten do |t|
        sh "#{ CC } #{ CFLAGS} -c -o #{ t.name } #{ src }"
      end
    when '.asm'
      file obj => [ src, path_obj ] do | t |
        sh "#{ AS } #{ AFLAGS } -o #{ t.name } #{ src }"
      end
    end

    obj
  end

  file efi_output => objs do |t|
    sh "#{LD} #{ LFLAGS} #{ t.prerequisites.join(' ') } -out:#{ t.name }"
  end

  efi_output
end


namespace :main do

    %w(x64).each do |arch|
    dependencies = make_efi(arch, 'boot', %w( hello ))
    desc "Build Main"
    task :build => dependencies
  end

end
