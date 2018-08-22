#
# Rakefile for EFI Hello world
#
require 'rake/clean'
require 'rake/packagetask'

ARCH  = ENV['EFI_ARCH'] || case `uname -m`
when /i[3456789]86/
  :i386
when /x86.64/
  :x64
when /aarch64/
  :aa64
else
  :unknown
end

PATH_BIN        = "bin/"
PATH_SRC        = "src/"
PATH_OBJ        = "obj/"
PATH_MNT        = "mnt/"
PATH_EFI_BOOT   = "#{PATH_MNT}EFI/BOOT/"
PATH_INC        = "#{PATH_SRC}include/"
case ARCH.to_sym
when :x64
  PATH_OVMF       = "var/bios64.bin"
  QEMU            = "qemu-system-x86_64"
when :i386
  PATH_OVMF       = "var/bios32.bin"
  QEMU            = "qemu-system-x86_64"
else
  PATH_OVMF       = "var/OVMF.fd"
  QEMU            = "qemu"
end

if RUBY_PLATFORM =~ /darwin/ then
  LLVM_PREFIX     = `brew --prefix llvm`.gsub(/\n/, '')
  CC      = ENV['CC'] || "#{LLVM_PREFIX}/bin/clang"
  LD      = ENV['LD'] || "#{LLVM_PREFIX}/bin/lld-link"
else
  CC      = ENV['CC'] || "clang"
  LD      = ENV['LD'] || "lld-link-6.0"
end
CFLAGS  = "-Os -std=c99 -fno-stack-protector -fshort-wchar -mno-red-zone -nostdlibinc -I #{PATH_INC} -Wall -Wpedantic"
AS      = ENV['AS'] || "nasm"
AFLAGS  = "-s -I #{ PATH_SRC }"
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
  (efi_arch, efi_suffix) = convert_arch(ARCH)
  FileUtils.cp("#{PATH_BIN}boot#{efi_suffix}.efi", "#{PATH_EFI_BOOT}boot#{efi_suffix}.efi")
  sh "#{QEMU} -bios #{PATH_OVMF} -monitor stdio -drive file=fat:ro:mnt"
end


def convert_arch(s)
  case s.to_sym
  when :x64
    ['x86_64', 'x64']
  when :i386
    ['i386', 'ia32']
  when :aa64
    ['aarch64', 'aa64']
  else
    [s.to_s, s.to_s]
  end
end

def make_efi(cputype, target, src_tokens, options = {})

  (efi_arch, efi_suffix) = convert_arch(cputype)

  cf_target = "-target #{efi_arch}-pc-win32-coff"

  case cputype.to_sym
  when :x64
    af_target = "-f win64"
  when :i386
    af_target = "-f win32"
  end

  path_obj      = "#{PATH_OBJ}#{efi_suffix}/"
  directory path_obj

  if options[:base]
    path_src_p    = "#{PATH_SRC}#{options[:base]}/"
  else
    path_src_p    = "#{PATH_SRC}"
  end

  if options[:no_suffix]
    efi_output    = "#{PATH_BIN}#{target}.efi"
  else
    efi_output    = "#{PATH_BIN}#{target}#{efi_suffix}.efi"
  end

  srcs = src_tokens.map do |s|
    if s !~ /\.\w+/
      s += '.c'
    end
    base = File.basename(s, '.*')
    ext = File.extname(s)
    if s !~ /\//
      s = [
        "#{path_src_p}#{s}",
        "#{path_src_p}#{base}-#{efi_suffix}#{ext}",
        "#{PATH_SRC}#{s}",
        "#{PATH_SRC}#{base}-#{efi_suffix}#{ext}",
      ].find do |p|
        if File.exist?(p)
          p
        end
      end
    end
    s
  end

  objs = srcs.map do |src|
    mod_name = File.basename(src, '.*')
    obj = "#{path_obj}#{mod_name}.o"

    case File.extname(src)
    when '.c'
      file obj => [ src, INCS, path_obj ].flatten do |t|
        sh "#{ CC } #{ cf_target } #{ CFLAGS} -c -o #{ t.name } #{ src }"
      end
    when '.asm'
      file obj => [ src, path_obj ] do | t |
        sh "#{ AS } #{ af_target } #{ AFLAGS } -o #{ t.name } #{ src }"
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

  [ARCH].each do |arch|
    dependencies = make_efi(arch, 'boot', %w( hello ))
    desc "Build Main"
    task :build => dependencies
  end

end
