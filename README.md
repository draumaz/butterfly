# Butterfly
A text-based TBBS with fantasy creatures, projectile weaponry, poisonous elixirs, and more.

```
Butterfly v0.16_03 | KILLS: 0   | DEATHS: 0   | SPARES: 0

PLAYR: Aradi  | HP: 26 | STR: 14

ENEMY: Goblin | HP: 2  | STR: 7

[FIGHT]
[ITEMS] <
[SPARE]
[EXIT ]

[1x POTION]
[0x SPEAR ] <
[1x POISON]
[BACK     ]
```

# Controls

```W, I, UP``` - up

```S, K, DOWN``` - down

```ENTER``` - select

```CTRL-C``` - close game

```Q``` - go back

# Download

## Get it through <a href="https://crates.io/crates/draumaz-butterfly">cargo</a>!

- ```cargo install draumaz-butterfly```
- ```draumaz-butterfly # <- this will generate a save folder, so go somewhere safe!```

## Build from source!

- ```git clone https://github.com/draumaz/butterfly```
- ```cd butterfly```
- ```cargo run```

## If cargo spits an error out about <ncurses.h>...

### Debian/Ubuntu:
```
apt install ncurses-dev
```

### NixOS:
```
nix-shell -p ncurses
```
# Acknowledgements

- <a href="https://github.com/DeltaDove">DeltaDove</a> - ARMv8 testing, potion design, bugtesting, naming
- Bryce Cano - character design

# Licensing

- Butterfly is dual-licensed under both the GPL-v3.0 and MIT licenses.
- The facets of this game covered by the MIT license can be found at <a href="https://github.com/draumaz/butterfly/blob/master/lic/FUNCS_MIT.md">lic/FUNCS_MIT.md</a>. 
- All other parts are licensed under GPL-v3.0.
