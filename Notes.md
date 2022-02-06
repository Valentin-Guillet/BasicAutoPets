
- Team:
  + Animal*[5]

- Shop:
  + Animal*[n]

- Actions:
  + BUY_ANIMAL n
    -> team += shop_animal[n]

  + UPGRADE m n
    -> team[n] += shop_animal[m]

  + SELL n
    -> sell team[n]

  + BUY_ITEM m n
    -> team[n] += shop_item[m]

  + ROLL

  + FREEZE_ANIMAL n
    -> freeze shop_animal[n]

  + FREEZE_ITEM n
    -> freeze shop_item[n]

  + END_TURN n1 n2 n3 n4 n5
    -> order team
