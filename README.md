# Butterfly

![Screenie](https://github.com/draumaz/butterfly/raw/main/media/btf-main.svg "Game screen")

  A randomly-generated, turn-based TUI battle game. Fantasy elements, buff dragons, in your terminal today!
![Weapon](https://github.com/draumaz/butterfly/raw/main/media/btf-item.svg "Item screen")

  Play as a strange creature, and fight off endless hordes of equally odd beings!

# Controls

```W, I, UP``` - move up

```S, K, DOWN``` - move down

```ENTER``` - confirm

```CTRL-Q, CTRL-C, Q``` - close game

# Download

## Grab a binary!
  You can find these <a href="https://github.com/draumaz/butterfly/releases/latest">here</a>.

## Build from source! (it won't take long, I promise)

```git clone https://github.com/draumaz/butterfly; cd butterfly```

```make```

```./butterfly-debug```

### Compile notes

- If you're compiling on macOS or musl-based Linux, remove the ```-ltinfo``` line from the Makefile.

#### If you encounter anything in your builds that feel like bugs, report them and I'll fix it as soon as possible!

```
real    0m0.345s
user    0m0.268s
sys     0m0.076s
```

# Acknowledgments

catboy6969 - playtest, game design, armv8 testing

Bryce Cano - character design, inspiration

<a href="https://carbon.now.sh/">Carbon</a> - text displays
