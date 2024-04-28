project('systemd-boot-efi', 'c',
        version : '255',
        license : 'GPLv2',
        default_options: [
                'c_std=gnu11',
                'warning_level=2',
        ],
        meson_version : '>= 0.60.0',
       )

conf = configuration_data()
conf.set_quoted('PROJECT_URL', 'https://systemd.io/')
conf.set('PROJECT_VERSION', meson.project_version(),
         description : 'Numerical project version (used where a simple number is expected)')

# Our own paths
bootlibdir = get_option('prefix')

cc = meson.get_compiler('c')
sh = find_program('sh')

############################################################

efi_arch = {
        'aarch64'     : 'aa64',
        'arm'         : 'arm',
        'loongarch32' : 'loongarch32',
        'loongarch64' : 'loongarch64',
        'riscv32'     : 'riscv32',
        'riscv64'     : 'riscv64',
        'x86_64'      : 'x64',
        'x86'         : 'ia32',
}.get(host_machine.cpu_family(), '')

pymod = import('python')
pyelftools = pymod.find_installation('python3',
                                     required : true,
                                     modules : ['elftools'])

conf.set_quoted('EFI_MACHINE_TYPE_NAME', efi_arch)

efi_arch_alt = ''
efi_cpu_family_alt = ''
if efi_arch == 'x64' and cc.links('''
                #include <limits.h>
                int main(int argc, char *argv[]) {
                        return __builtin_popcount(argc - CHAR_MAX);
                }''', args : ['-m32', '-march=i686'], name : '32bit build possible')
        efi_arch_alt = 'ia32'
        efi_cpu_family_alt = 'x86'
endif

############################################################

elf2efi_py = find_program('tools/elf2efi.py')

version_h = configure_file(
        input : 'version.h.in',
        output : 'version.h',
        configuration: conf)

# A list of boot stubs. Required for testing of ukify.
boot_stubs = []

build_dir_include = include_directories('.')

subdir('fundamental')
subdir('efi')