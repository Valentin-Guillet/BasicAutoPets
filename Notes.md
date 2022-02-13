
# Questions

# ToDo

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
