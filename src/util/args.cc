#include <util.hh>

void vmp::util::version() {
    write_console(cmake::VMP::fmt, version_text);
}

void vmp::util::conditions() {
    write_console(
        cmake::VMP::description, '\n',
        cmake::VMP::copyright, "\n\n",
        conditions_text
    );
}

std::span<char*> vmp::util::parse_args(int argc, char ** argv) {
    return { argv, static_cast<std::size_t>(argc) };
}

void vmp::util::check_args(const std::string_view arg) {
    if(arg == "version")
        version();
    else if(arg == "conditions")
        conditions();
}
