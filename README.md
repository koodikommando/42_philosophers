# Philosophers

The "Philosophers" project from the 42 curriculum is a simulation of the classic Dining Philosophers problem. The objective of this project is to understand threading, process synchronization, and handling deadlock and starvation.

## **Overview**

In this project, multiple philosophers are seated around a table with a for between each pair. Philosophers alternate between eating, thinking, and sleeping. To eat, a philosopher needs two forks — one on the left and one on the right. This scenario creates a challenge in avoiding deadlock and ensuring that each philosopher gets a chance to eat.


## **Usage**

### 1. Clone the Repository

```bash
git clone git@github.com:koodikommando/42_philosophers.git
cd philosophers
```

### 2. Compilation

Compile the project using the provided Makefile:

```bash
make
```

### 3. Running the Simulation

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- **`number_of_philosophers`**: Number of philosophers and forks.
- **`time_to_die`**: Maximum time (in ms) a philosopher can go without eating before starving.
- **`time_to_eat`**: Time (in ms) it takes for a philosopher to finish eating.
- **`time_to_sleep`**: Time (in ms) a philosopher spends sleeping after eating.
- **`[number_of_times_each_philosopher_must_eat]`**: Optional parameter; if provided, the simulation ends once each philosopher has eaten this many times.

### 4. Example Usage

```bash
./philo 5 800 200 200
```

This command initiates a simulation with 5 philosophers who need to eat within 800ms to avoid starving, take 200ms to eat, and 200ms to sleep.
