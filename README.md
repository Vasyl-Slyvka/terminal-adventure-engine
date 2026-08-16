# Terminal Adventure Engine

[![CI](https://github.com/Vasyl-Slyvka/terminal-adventure-engine/actions/workflows/ci.yml/badge.svg)](https://github.com/Vasyl-Slyvka/terminal-adventure-engine/actions/workflows/ci.yml)
[![C11](https://img.shields.io/badge/C-C11-blue.svg)](https://en.cppreference.com/w/c/11)
[![License: MIT](https://img.shields.io/badge/Code%20License-MIT-yellow.svg)](LICENSE)

A modular terminal-based adventure game written in C. The engine is demonstrated through **Elden Ring TUKE Edition**, an unofficial, non-commercial fan project created for an educational programming assignment at the Technical University of Košice.

The project focuses on explicit ownership of dynamically allocated objects, linked-list containers, a case-insensitive command parser, state-driven game rules, and automated verification of a complete playthrough.

## Highlights

- 17 interconnected rooms with four-direction navigation
- inventory and room-level item management
- item properties for movable, usable, and examinable objects
- case-insensitive, whitespace-tolerant command parsing
- gated progression based on collected items and player state
- 13 collectible runes and multiple story endings
- restart support and a deterministic end-to-end scenario
- strict C11 build with warnings treated as errors
- unit, integration, CLI, sanitizer, and static-analysis verification
- GitHub Actions on both GCC and Clang

## Build and run

Requirements:

- a C11 compiler such as GCC or Clang
- GNU Make

```bash
git clone https://github.com/Vasyl-Slyvka/terminal-adventure-engine.git
cd terminal-adventure-engine
make
./adventure
```

The command interface is primarily in Slovak because the original TUKE assignment was taught in Slovak.

## Commands

| Action | Commands |
| --- | --- |
| Move | `sever` / `s`, `juh` / `j`, `vychod` / `v`, `zapad` / `z` |
| Inspect the room | `rozhliadni sa` |
| List commands | `prikazy`, `help`, `pomoc` |
| Show inventory | `inventar`, `i` |
| Take an item | `vezmi <item>` |
| Drop an item | `poloz <item>` |
| Examine an item | `preskumaj <item>` |
| Use an item | `pouzi <item>` |
| Restart | `restart` |
| Show game information | `o hre`, `about` |
| Quit | `koniec`, `quit`, `exit` |

Commands are case-insensitive and tolerate extra surrounding whitespace.

## Verification

Run the complete test suite:

```bash
make test
```

It verifies the core data structures, parser aliases and arguments, the 17-room world, inventory behavior, movement gates, restart behavior, a complete successful playthrough, and long-input handling.

Run AddressSanitizer and UndefinedBehaviorSanitizer locally:

```bash
make sanitize
```

The local sanitizer target disables LeakSanitizer because some traced/containerized environments cannot inspect `/proc`; GitHub Actions runs the same suite with leak detection enabled.

To run the supplied deterministic playthrough directly:

```bash
make scenario
```

The code has also been checked locally with GCC's static analyzer:

```bash
make clean
make CFLAGS="-std=c11 -Wall -Wextra -Wconversion -Werror -pedantic -fanalyzer -g3"
```

## Project structure

```text
.
├── main.c                  application entry point
├── game.c/.h               game loop, rules, movement, and endings
├── parser.c/.h             command recognition and input history
├── world.c/.h              rooms, connections, and initial items
├── room.c/.h               room operations
├── backpack.c/.h           inventory operations
├── item.c/.h               item model and properties
├── container.c/.h          typed linked-list container
├── command.c/.h            parsed command model
├── tests/                   automated core and CLI tests
├── docs/GAME_DESIGN.md     original game-design document
├── scenario.txt            deterministic full playthrough
└── .github/workflows/      GCC, Clang, and sanitizer CI
```

## Design notes

The code intentionally keeps the engine in small C modules instead of hiding game state behind a framework. This makes allocation, ownership, container mutation, and rule evaluation visible for review.

The parser does not depend on POSIX regular expressions. It normalizes input, recognizes supported command forms and aliases, and stores parsed arguments explicitly, which keeps the build portable across common C11 toolchains.

See [GAME_DESIGN.md](docs/GAME_DESIGN.md) for the room graph, progression rules, item placement, and ending design.

## Intellectual-property notice

This repository is an unofficial, fan-made, non-commercial educational project. It is not affiliated with, endorsed by, or sponsored by FromSoftware or Bandai Namco Entertainment. Elden Ring names, setting, characters, and lore belong to their respective rights holders.

The [MIT License](LICENSE) applies to the original source code in this repository. It does not grant rights to third-party names, settings, characters, or lore. See [NOTICE.md](NOTICE.md).
