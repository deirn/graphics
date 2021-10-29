#include "paths.h"

#include <filesystem>

using namespace std;
using namespace filesystem;

namespace procPathContainer {
    path procPath;
}

using namespace procPathContainer;

void setProcName(char *procName) {
    procPath = weakly_canonical(path(procName));
}

path getProcDir() {
    return procPath.parent_path();
}

path getResourcePath(const char *path) {
    return getProcDir() / "res" / path;
}
