#include <iostream>
#include <fstream>
#include <string>

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
    std::string user = runCommand("whoami");
    std::string hostname = runCommand("hostname");
    std::string os = runCommand("cat /etc/os-release | grep '^NAME=' | cut -d'=' -f2 | tr -d '\"'");
    std::string kernel = runCommand("uname -r");
    std::string uptime = runCommand("uptime -p");
    std::string cpu = runCommand("grep 'model name' /proc/cpuinfo | head -1 | cut -d':' -f2 | xargs");
    std::string memory = runCommand("free -h | awk '/^Mem:/ {print $3"/"$2}'");
    std::string packages = runCommand("anemo count");

    std::cout << "\033[1;32m" << user << "@" << hostname << "\033[0m\n";
    std::cout << "----------------------------\n";
    std::cout << "OS       : " << os << "\n";
    std::cout << "Kernel   : " << kernel << "\n";
    std::cout << "Uptime   : " << uptime << "\n";
    std::cout << "CPU      : " << cpu << "\n";
    std::cout << "Memory   : " << memory << "\n";
    std::cout << "Packages : " << packages << " (anemo)\n";
}

int main() {
    displaySystemInfo();
    return 0;
}
