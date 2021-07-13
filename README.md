# Binary-search tree

==============

## Introduction

- Binary-search tree data-structure written in c++ modern`smart-pointers and iterators`

## Requirement

- c++17 or later

  - Tested on:
    - g++-9 -std=c++1z
    - g++10 -std=c++1z
    - g++-11 -std=c++1z
    - clang++-11 -std=c++1z
    - clang++-10 -std=c++1z

### Everything inside `bst.hpp`

![Screenshot-20210713120223-567x266](https://user-images.githubusercontent.com/62993724/125424430-f933b0d1-32c8-4dd0-b023-e7c8840873b5.png)

## Usage

- simply download this library then copy `lib` folder to your working directory then include it like this: `#include "lib/bst.hpp"`!

- if you're on ubuntu you can do this:

  - open terminal then do `sudo apt install nautilus-admin` then when it's done do `nautilus -q`
  - open `usr/include` folder as administrator
  - add `lib` folder into `usr/include`, you may rename library into `bst` after you're done!, this is how you include it without copying it every time into your directory!

  - ```cpp
    #include <lib/bst.hpp>
    #include <iostream>

    auto main()
        -> int
    {
      bst_<int> nums {1, 2, 3, 5};
      nums.print(1);
    }
    ```
