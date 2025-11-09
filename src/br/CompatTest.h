// SPDX-License-Identifier: BUSL-1.1
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
