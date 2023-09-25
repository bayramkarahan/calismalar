#include <iostream>
#include <stack>
#include <utility>

#include <filesystem>            // see notes about these two lines at the bottom
namespace fs = std::filesystem;  // -"-

void chmodr(const fs::path& path, fs::perms perm,fs::perm_options permops) {
    std::stack<fs::path> dirs;
    dirs.push(path);

    fs::permissions(path, perm);

    do {
        auto pa = std::move(dirs.top()); // extract the top dir from the stack
        dirs.pop();                      // and remove it

        for(auto& de : fs::directory_iterator(pa)) {
            // save subdirectories for later:
            if(fs::is_directory(de)){

                dirs.push(de);
                fs::permissions(de, perm,permops);
            }
            else {
                fs::permissions(de, perm,permops);
            }
        }
    } while(!dirs.empty());              // loop until there are no dirs left
}

int main() {
    chmodr("deneme", fs::perms::none,fs::perm_options::replace);
    chmodr("deneme", fs::perms::owner_all|fs::perms::group_exec|fs::perms::group_read,fs::perm_options::replace);

   /* std::filesystem::permissions(
        "deneme",std::filesystem::perms::none,
        std::filesystem::perm_options::replace
    );
    std::filesystem::permissions(
        "deneme",
        std::filesystem::perms::owner_all|
                std::filesystem::perms::group_read,
        std::filesystem::perm_options::replace
    );*/
}

