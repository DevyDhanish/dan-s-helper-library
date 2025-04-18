/*
    wrapper for all the header files
    so your don't have to include each one manually
    you can do that too if your want
*/
#pragma once

#include "debug/debug.hpp"
#include "encryption/encryption.hpp"
#include "networking/networking.hpp"
#include "networking/node.hpp"
#include "serialize/serialize.hpp"
#include "utils/utils.hpp"

#define DEFAULT_DATA_LEN 1024