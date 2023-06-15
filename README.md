# Ecosystem Simulation

## Introduction

This project aims to simulate an ecosystem composed of creatures that move around in a defined space. Each creature has a particular position and moves with a certain velocity in a given direction. The creatures are only capable of moving and do not perform any other actions.

The spatial occupation of each creature is modeled by an ellipse, with the major axis oriented along its direction of movement. Upon creation, a creature's position, size, velocity, and direction are all initialized randomly.

The creatures are placed in an aquarium filled with a substance, such as water, which serves as their environment. The aquarium contains this environment, which in turn contains the creatures. The creatures perceive their surroundings, including the environment and its boundaries, as well as neighboring creatures.

Collisions with the boundaries of the environment do not result in damage, as the creatures rebound without harm.

## Dependencies

This application has the following dependencies:

- [Random](https://github.com/effolkronium/random) - A header-only C++11 library for generating random numbers.

The Random library is used to generate random numbers in the project. The necessary files have been included in the `ecosystem-simulate/Ecosystem/include` directory, so there is no need to separately download and install the library.

If you want to use the Random library in another C++ project, you can simply include the `random.hpp` file from the `ecosystem-simulate/Ecosystem/include` directory in your project.

## Installation and Usage

To install and run this application, follow the instructions below:

1. Clone the repository to your local machine:

```bash
git clone https://github.com/HoarfrostRaven/ecosystem-simulate.git
```

2. Navigate to the `ecosystem-simulate/Ecosystem` directory:

```bash
cd ecosystem-simulate/Ecosystem
```

3. Run the command `make run` to start the application:

```bash
make run
```

## Examples

### Initializing the program

1. When the program starts running, you will be prompted to enter 5 non-negative integers.
2. If any number is negative, the program will exit.
3. Each number corresponds to the initial quantity of a type of bug.

### Running the program

1. After initializing the program, the simulation will start.
2. You can control the program by pressing the following keys on the keyboard:
   - Pressing keys 1-5 will increase the corresponding type of bug.
   - Pressing the key "A" will increase the quantity of  random bug.
   - Pressing the key "K" will kill the first living bug in the queue.
   - Pressing the "ESC" key will exit the simulation program and return to the control interface.
