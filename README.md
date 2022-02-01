# Butterfly
This is a text-based TBBS with fantasy creatures, projectile weapons, poisonous elixirs, and more.

![Main board](https://github.com/draumaz/butterfly/raw/main/media/btf-main.svg "Game screen")
![Item board](https://github.com/draumaz/butterfly/raw/main/media/btf-item.svg "Item screen")

# Controls

```W, I, UP``` - move up

```S, K, DOWN``` - move down

```ENTER``` - confirm

```CTRL-Q, CTRL-C, Q``` - close game

# Download

## Grab a binary!
  You can find these <a href="https://github.com/draumaz/butterfly/releases/latest">here</a>.

## Build from source! (it won't take long, I promise)

- ```git clone https://github.com/draumaz/butterfly```

- ```cd butterfly```

- ```make```

- ```./butterfly-debug```

### Notes for non-GNU C compilers

- Clang handles Butterfly slightly differently than GCC. To successfuly compile, apply patches/clang_make.patch to the root of the cloned repo.

- ```cd butterfly```

- ```patch -ruN < patches/clang_make.patch```

#### If you encounter anything in your builds that feel like bugs, report them and I'll fix it as soon as possible!

# Acknowledgements

catboy6969 - playtest, game design, armv8 testing

Bryce Cano - character design, inspiration

<a href="https://carbon.now.sh/">Carbon</a> - screenshots
