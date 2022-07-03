
# Questions

- Does Crab copy less than its own life (i.e. 3) ?
- Does Dodo gives to dead pets ?

- [Blowfish 3/5] | [Fish 2/3 - Snake 6/6]
  -> Does the blowfish fires ? How many times ? What about when it has 20 hp ?

# ToDo

- Env
  + Compute mask
- Agents
  + Agent::save_action() -> saves pair (state, action) in buffer
  + Agent::write_to_file() -> saves this buffer to a file for debug purposes
- RandomAgent
  + Option to be totally random or categorically random
- Memory leak check
- Rule-based Agent

# Order

- Start of battle:
  + Sort by attack, resolve
  + All abilities triggers (even if dead) BUT if dead and change stats (e.g. butterfly), still dies
