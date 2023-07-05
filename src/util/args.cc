#include <util.hh>

void vmp::util::version() {
    write_console(cmake::project_fmt, version_text);
}

void vmp::util::conditions() {
    write_console(
        cmake::project_description, '\n',
        cmake::project_copyright, "\n\n",
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
