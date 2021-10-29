#pragma once

#include <string>
#include <filesystem>

void setProcName(char *procName);

std::filesystem::path getProcDir();

std::filesystem::path getResourcePath(const char *path);
