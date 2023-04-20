

- Can `Team::get_pets()` return std::vector<Pet const*> ???

# Questions

- Does Crab copy less than its own life (i.e. 3) ? [Here: no]
- Does Dodo gives to dead pets ? [Here: no]
- Cricket + 2xHedgehog -> H1 kills C and H2 -> does H2 kill ZC or ZC spawns after every thing ? [Here: H2 kills ZC]

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
