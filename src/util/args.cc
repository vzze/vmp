#include <util.hh>

void vmp::util::version() {
    std::cout << "VMP Copyright (C) 2023 vzze\n";
    std::cout << "This program comes with ABSOLUTELY NO WARRANTY.\n";
    std::cout << "This is free software, and you are welcome to redistribute it\n";
    std::cout << "under certain conditions; type `vmp conditions` for details.\n\n";
    std::cout << "Version 0.0.2\n";
}

void vmp::util::conditions() {
    std::cout << "VMP Music Player\n";
    std::cout << "Copyright (C) 2023 vzze\n\n";

    std::cout << "This program is free software: you can redistribute it and/or modify\n";
    std::cout << "it under the terms of the GNU General Public License as published by\n";
    std::cout << "the Free Software Foundation, either version 3 of the License, or\n";
    std::cout << "(at your option) any later version.\n\n";

    std::cout << "This program is distributed in the hope that it will be useful,\n";
    std::cout << "but WITHOUT ANY WARRANTY; without even the implied warranty of\n";
    std::cout << "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n";
    std::cout << "GNU General Public License for more details.\n\n";

    std::cout << "You should have received a copy of the GNU General Public License\n";
    std::cout << "along with this program.  If not, see <https://www.gnu.org/licenses/>.\n";
}

int vmp::util::check_args(const std::string & arg) {
    if(arg == "version")
        version();
    else if(arg == "conditions")
        conditions();

    return 0;
}
