// SPDX-License-Identifier: GPL-3.0
// Copyright 2024-2025 Michael Pozhidaev <msp@luwrain.org>

#pragma once

#include<vector>
#include<list>
#include<string>
#include<iostream>
#include<sstream>
#include<memory>
#include<thread>
#include <mutex>
#include <condition_variable>
#include<cstring>
#include<cerrno>
#include<functional>

#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>
#include <unistd.h>
#include<sys/wait.h>
