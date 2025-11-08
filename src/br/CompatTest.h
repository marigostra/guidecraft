// SPDX-License-Identifier: GPL-3.0
// Copyright 2024-2025 Michael Pozhidaev <msp@luwrain.org>

#pragma once

namespace GuideCraft {

  class CompatTest
  {
  public:
 virtual ~CompatTest() {}

  public:
    void run();

  private:
    void init();
    void close();
  };

}
