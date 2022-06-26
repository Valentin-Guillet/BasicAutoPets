
# Questions

- [Blowfish 3/5] | [Fish 2/3 - Snake 6/6]
  -> Does the blowfish fires ? How many times ? What about when it has 20 hp ?

# ToDo

- Textual UI
  + Test memory leak
- Implement UI play_again()
- Nb of life lost wrt turns

# Order

- Start of battle:
  + Sort by attack, resolve
  + All abilities triggers (even if dead) BUT if dead and change stats (e.g. butterfly), still dies


# Actions

- Team:
  + Pet*[5]

- Shop:
  + Pet*[n]

- Actions:
  + BUY_PET n
    -> team += shop_pet[n]

  + UPGRADE m n
    -> team[n] += shop_pet[m]

  + SELL n
    -> sell team[n]

  + BUY_OBJECT m n
    -> team[n] += shop_object[m]

  + ROLL

  + FREEZE_PET n
    -> freeze shop_pet[n]

  + FREEZE_OBJECT n
    -> freeze shop_object[n]

  + END_TURN n1 n2 n3 n4 n5
    -> order team
