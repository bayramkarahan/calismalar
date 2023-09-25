#include <fstream>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

//function copy files
void cpFile(const fs::path & srcPath,
  const fs::path & dstPath) {

  std::ifstream srcFile(srcPath, std::ios::binary);
  std::ofstream dstFile(dstPath, std::ios::binary);

  if (!srcFile || !dstFile) {
    std::cout << "Failed to get the file." << std::endl;
    return;
  }

  dstFile << srcFile.rdbuf();

  srcFile.close();
  dstFile.close();
}

//function create new directory
void cpDirectory(const fs::path & srcPath,
  const fs::path & dstPath) {

  fs::create_directories(dstPath);

  for (const auto & entry: fs::directory_iterator(srcPath)) {
    const fs::path & srcFilePath = entry.path();
    const fs::path & dstFilePath = dstPath / srcFilePath.filename();
    //if directory then create new folder
    if (fs::is_directory(srcFilePath)) {
      cpDirectory(srcFilePath, dstFilePath);
    } else {
      cpFile(srcFilePath, dstFilePath);
    }
  }
}

int main() {
  const fs::path srcPath = "/etc/skel";
  const fs::path dstPath = "/tmp/abc";

  // Copy only those files which contain "Sub" in their stem.
  cpDirectory(srcPath, dstPath);

  return 0;

}
