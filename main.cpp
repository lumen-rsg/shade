#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <random>

std::string runCommand(const std::string& cmd) {
    std::string result;
    char buffer[128];
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return "N/A";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);
    result.erase(result.find_last_not_of(" \n\r\t") + 1);
    return result;
}

void displaySystemInfo() {
    // MOTD messages
    const std::vector<std::string> motd_list = {
        "somebody touch my_spaghetti",
        "lets all love Lain!",
        "try also 'touch grass'",
        "monika, luv u <3",
        "keep coding, keep hacking",
        "you are the architect of your system",
        "nothing is impossible in C++",
        "fear the penguin!",
        "welcome to the cryonix realm",
        "x11 should go - cv2",
        "sometimes i dream about cheese",
        "nine plus ten",
        "warm hello to cv2",
        "warm hello to kirgly",
        "warm hello to dprog",
        "warm hello to Ivan Ruban",
        "men were men when they wrote their device drivers",
        "gnoo / loonix",
        "how can one patch KDE for FreeBSD?",
        "wayland.",
        "XDG (xross debugging group)",
        "athena",
        "intel e1000e kernel panic",
        "POSIX is different",
        "sudo rm -rf /",
        "yes it's running on bare metal",
        "i never touch grass",
        "nvidia stable drivers when",
        "zhest",
        "std::bitset<64> bs(arch);",
        "i am a terminal samurai",
        "ASCII madness",
        "UTF-8 madness",
        "gradient install love",
        "gradient upgrade myself",
        "gradient remove gradient",
        "tip: gradient list will show all installed packages",
        "THIS IS THE YEAR OF LINUX DESKTOP!!!11!!1",
        "why bother using a server when you have an old laptop",
        "bash? nah. stun",
        "look up",
        "if C++ is so good then where is C++2???",
        "how to exit vim?",
        "tired of writing these messages",
        "how many messages can I fit here?",
        "this is real.",
        "mita don't kill me please",
        "you should alias please as sudo",
        "u like jazz?",
        ":)",
        ":(",
        ":/",
        "gradient? yes.",
        "why bother using other distros to build your own one",
        "please compile another 14000 packages, please",
        "seriously, how many messages are here?!",
        "it's free real estate",
        "404: coffee not found",
        "use the source, luke",
        "compiling... 99%... error.",
        "just one more package...",
        "kernel panic: not syncing",
        "C? C++. C? C++. C? you thought you can replace C?",
        "segmentation fault (core dumped)",
        "undefined behavior detected",
        "one does not simply write bug-free code",
        "it worked on my machine",
        "ctrl+c? nah, alt+sysrq+b",
        "emacs vs vim? nano supremacy.",
        "arch users be like: btw...",
        "this MOTD is licensed under GPLv3",
        "real programmers use cat > a.out",
        "try `strings /dev/random`",
        "alias rm='echo no'",
        "UNIX is user-friendly, it’s just selective",
        "grep -r 'meaning of life' /",
        "vim is love, vim is life",
        "python is just pseudo-code that runs",
        "ed is the standard text editor",
        "who needs a GUI anyway?",
        "are you even root?",
        "root dance time?",
        "dude, that easy to exit - :q",
        "gradient update --force",
        "gradient upgrade --paranoid",
        "why isn't systemd a kernel module?",
        "when in doubt, `dd` it",
        "init 6 to solve all your problems",
        "bash: command not found",
        "is this an emacs moment?",
        "writing my own shell because why not",
        "if you use systemd, do you even Linux?",
        "they see me compiling, they hating",
        "this terminal window is a paid actor",
        "your CPU is about to catch fire",
        "defragging your ext4? why?",
        "Hurd is the future (copium)",
        "real hackers use Plan 9",
        "cp -r / to /dev/null",
        "the only true init is openrc",
        "btw I use Slackware",
        "it’s all fun and games until the kernel panics",
        "patching the kernel, brb",
        "LFS users fear nothing",
        "bootstrapping a distro in my distro",
        "dm-crypt my entire existence",
        "GNU Terry Pratchett",
        "echo 'Welcome to Cryonix' > /etc/motd",
        "su -c 'rm -rf /'",
        "compiling the kernel for fun and profit",
        "Linux is just a kernel, but this distro is life",
        "yes, I'm running it on a ThinkPad",
        "i3 users know no fear",
        "vscode? real hackers use ed",
        "compiling gcc with gcc to compile gcc",
        "your swap is crying",
        "optimizing for size? optimizing for speed?",
        "NVMe: Now Very Much Exploded",
        "why do we need an init system again?",
        "remember to mount /boot",
        "neovim supremacy",
        "just one more reboot",
        "why does this only work on my machine?",
        "zsh is life",
        "I use bash, but I don't talk about it",
        "systemctl enable sanity",
        "i3, dwm, sway, or just tmux?",
        "Linux is an OS? No, it’s just a kernel.",
        "KISS: Keep It Simple, Stupid",
        "terminal > GUI",
        "every keystroke makes it worse",
        "modprobe happiness",
        "dmesg says you're screwed",
        "my uptime is older than your laptop",
        "fastest editor in the west: `echo hello > file`",
        "touch /this/file/does/not/exist",
        "running this on a toaster",
        "not even vim can save this",
        "the UNIX way: everything is a file",
        "sudo mv life /dev/null",
        "Debian stable? More like Debian fossilized",
        "everything is bloat",
        "Xorg still lives... barely",
        "RMS is watching",
        "who needs a mouse anyway?",
        "I replaced my DE with tmux",
        "kernel hacking at 3AM",
        "error: too much coffee",
        "real devs commit directly to main",
        "remember to chmod +x",
        "pro tip: avoid memory leaks",
        "real men debug in production",
        "compiling the kernel with -O3, wish me luck",
        "you forgot a semicolon again",
        "recompiling glibc for fun",
        "install gentoo",
        "make && make install && regret",
        "why does my build take 2 hours?",
        "syscalls are magic",
        "this binary is haunted",
        "malloc(0)? what could go wrong?",
        "SIGKILL solves all problems",
        "yes, I wrote my own text editor",
        "X11 is just a very slow video driver",
        "crash and burn, reboot, repeat",
        "error: no keyboard detected, press F1 to continue",
        "I run my servers on Raspberry Pi",
        "real men use telnet",
        "patching my own libc because why not",
        "cat /dev/random > /dev/sda",
        "grub rescue> _",
        "your RAM is full of tabs, not spaces",
        "Real programmers write self-modifying code",
        "git push --force",
        "Compiling a kernel faster than Chrome loads",
        "Your uptime is a lie",
        "sleep? nah, debugging",
        "Do you even TTY?",
        "Rewriting everything in Assembly",
        "chmod 777 / solves all issues",
        "there are ten types of people in the world, those that understand binary and those who don't",
        "as soon as i could count up to one, i was told i could be a programmer when i grow up"
};

    // Secure random selection
    std::random_device rd;
    std::mt19937 gen(rd()); // Mersenne Twister RNG
    std::uniform_int_distribution<size_t> dist(0, motd_list.size() - 1);
    const std::string& motd = motd_list[dist(gen)];

    const std::vector<std::string> logo_lines = {
    R"( ___                                                   )",
    R"(/\_ \                        __                        )",
    R"(\//\ \    __  __    ___ ___ /\_\    ___      __        )",
    R"(  \ \ \  /\ \/\ \ /' __` __`\/\ \ /' _ `\  /'__`\      )",
    R"(   \_\ \_\ \ \_\ \/\ \/\ \/\ \ \ \/\ \/\ \/\ \L\.\_    )",
    R"(   /\____\\ \____/\ \_\ \_\ \_\ \_\ \_\ \_\ \__/.\_\   )",
    R"(   \/____/ \/___/  \/_/\/_/\/_/\/_/\/_/\/_/\/__/\/_/   )"
    };

    std::string version =
          "                                    powered by linux";


    const std::vector<std::string> color_codes = {
    "\033[38;5;27m",
    "\033[38;5;33m",
    "\033[38;5;39m",
    "\033[38;5;69m",
    "\033[38;5;105m",
    "\033[38;5;141m",
    "\033[38;5;177m",
    };


    const std::vector<std::string> sysinfo = {
        "\033[1;32m \\\\ User       :\033[0m " + runCommand("whoami"),
        "\033[1;32m // Hostname   :\033[0m " + runCommand("hostnamectl hostname"),
        "\033[1;32m \\\\ OS         :\033[0m " + runCommand("cat /etc/os-release | grep '^NAME=' | cut -d'=' -f2 | tr -d '\"'"),
        "\033[1;32m // Kernel     :\033[0m " + runCommand("uname -r"),
        "\033[1;32m \\\\ Arch       :\033[0m " + runCommand("uname -m"),
        "\033[1;32m // Uptime     :\033[0m " + runCommand("uptime -p"),
        "\033[1;32m \\\\ Load Avg   :\033[0m " + runCommand("uptime | awk -F'load average:' '{print $2}' | xargs"),
        "\033[1;32m // CPU        :\033[0m " + runCommand("grep 'model name' /proc/cpuinfo | head -1 | cut -d':' -f2 | xargs"),
        "\033[1;32m \\\\ Memory     :\033[0m " + runCommand("free -h | awk '/^Mem:/ {print $3\"/\"$2}'"),
        "\033[1;32m // Disk       :\033[0m " + runCommand("df -h --output=used,size / | tail -1 | xargs"),
        "\033[1;32m \\\\ Disk Model :\033[0m " + runCommand("lsblk -nd -o model | head -1"),
        "\033[1;32m // Filesystem :\033[0m " + runCommand("findmnt -n -o FSTYPE /"),
        "\033[1;32m \\\\ GPU        :\033[0m " + runCommand("lspci | grep -i 'VGA\\|3D' | cut -d ':' -f3 | xargs"),
        "\033[1;32m // Network    :\033[0m " + runCommand("ip -o -4 addr show | awk '{print $2, $4}' | head -1"),
        "\033[1;32m \\\\ Packages   :\033[0m " + runCommand("gradient count") + " (gradient)",
        "\033[1;32m // Battery    :\033[0m " + runCommand("cat /sys/class/power_supply/BAT0/capacity 2>/dev/null || echo 'No Battery'"),
        "\033[1;32m \\\\ Shell      :\033[0m " + runCommand("echo $SHELL"),
        "\033[1;32m // Terminal   :\033[0m " + runCommand("basename $TERM"),
        "\033[1;32m \\\\ DE         :\033[0m " + runCommand("echo $XDG_CURRENT_DESKTOP"),
        "\033[1;32m // WM         :\033[0m " + runCommand("echo $XDG_SESSION_TYPE"),
        "\033[1;32m \\\\ Timezone   :\033[0m " + runCommand("timedatectl show --property=Timezone --value")
    };

    const std::string user = runCommand("whoami");
    const std::string hostname = runCommand("hostname");

    int ix = 0;

    for (const auto& line: logo_lines) {
        std::cout << color_codes[ix] << line << std::endl;
        ix++;
    }
    std::cout << version << std::endl;
    std::cout << "\033[0m" << std::endl;

    std::cout << "\033[1;96m" << motd << "\033[0m" << std::endl << std::endl;

    for (const auto& string: sysinfo) {
        std::cout << string << std::endl;
    }

}

int main() {
    displaySystemInfo();
    return 0;
}
