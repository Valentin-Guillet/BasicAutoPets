#!/usr/bin/env python

import argparse
import os
import random
import subprocess

import sys
sys.path.append("/home/valentin/Documents/Sapai/")

from sapai.pets import Pet
from sapai.teams import Team
from sapai.battle import Battle


SIZE_PROBA = sorted([5-i for x in range(5) for i in range(x+1)])

PETS_CONVERSION = {"zombiecricket": "zombie-cricket"}
PETS_CONVERSION_INV = {v: k for k, v in PETS_CONVERSION.items()}
OBJECTS_CONVERSION = {"none": "none",
                      "honey": "status-honey-bee"}
OBJECTS_CONVERSION_INV = {v: k for k, v in OBJECTS_CONVERSION.items()}

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("-n", "--number", type=int, default=10)
    return parser.parse_args()

def get_all_pets():
    files = os.listdir('../src/Pets/')
    pets = list(filter(lambda fname: fname.endswith('.cpp') and fname[0].isupper(), files))
    pets = list(map(lambda fname: fname[:-4].lower(), pets))
    return pets

def get_all_items():
    files = os.listdir('../src/Objects/Items/')
    items = list(filter(lambda fname: fname.endswith('.cpp'), files))
    items = list(map(lambda fname: fname[:-4].lower(), items))
    return items

def create_team(pet_list, item_list):
    n = random.choice(SIZE_PROBA)
    team = []
    for i in range(n):
        pet = random.choice(pet_list)
        attack = max(1, min(50, int(random.normalvariate(25, 10))))
        life = max(1, min(50, int(random.normalvariate(25, 10))))
        xp = random.randint(1, 5)
        item = random.choice(item_list) if random.random() < 0.3 else "none"

        team.append(f"{pet} {attack} {life} {xp} {item}")

    return '1 (' + ') ('.join(team) + ')'

def debug_battle_cpp(team_str1, team_str2):
    output = subprocess.run(["./main_test", "--debug", team_str1, team_str2], capture_output=True)
    return output.stdout.decode()

def test_battle_cpp(team_str1, team_str2):
    output = subprocess.run(["./main_test", team_str1, team_str2], capture_output=True)
    win, after_team1, after_team2 = output.stdout.decode()[:-1].split('\n')
    return int(win), after_team1, after_team2

def create_sapai_pet(pet_str):
    name, attack, health, xp, object_name = pet_str.split()
    xp = int(xp)
    name = PETS_CONVERSION.get(name, name)
    pet = Pet(name)
    pet._attack = int(attack)
    pet._health = int(health)
    if xp == 5:
        pet.level = 3
        pet.experience = 0
    elif xp >= 2:
        pet.level = 2
        pet.experience = xp - 2
    else:
        pet.level = 1
        pet.experience = xp
    pet.status = OBJECTS_CONVERSION[object_name]
    return pet

def create_sapai_team(team_str):
    team_str = team_str[2:]
    team = []
    while team_str:
        index = team_str.find(')')
        team.append(create_sapai_pet(team_str[1:index]))
        team_str = team_str[index+2:]
    return Team(team)

def convert_team2str(team):
    team_str = []
    for slot in team:
        pet = slot.pet
        if pet.name == 'pet-none':
            continue

        name = pet.name[4:]
        name = PETS_CONVERSION_INV.get(name, name)
        if pet.level == 1:
            xp = 0
        elif pet.level == 2:
            xp = 2
        else:
            xp = 5
        xp += pet.experience
        obj = OBJECTS_CONVERSION_INV[pet.status]
        team_str.append(f"({name} {pet.attack} {pet.health} {xp} {obj})")

    return "1" + (" " if team_str else "") + " ".join(team_str)

def test_battle_py(team1, team2, debug=False):
    team1 = create_sapai_team(team1)
    team2 = create_sapai_team(team2)
    battle = Battle(team1, team2)
    winner = battle.battle()

    win = (winner + 2) % 3 - 1
    after_team1 = convert_team2str(battle.t0)
    after_team2 = convert_team2str(battle.t1)
    if debug:
        breakpoint()

    return win, after_team1, after_team2


def main():
    args = parse_args()

    pet_list = get_all_pets()
    item_list = get_all_items()

    for i in range(args.number):
        team1 = create_team(pet_list, item_list)
        team2 = create_team(pet_list, item_list)

        out_cpp = test_battle_cpp(team1, team2)

        for j in range(100):
            out_py = test_battle_py(team1, team2)
            if out_cpp == out_py:
                break
        else:
            print("ERROR!")
            breakpoint()


if __name__ == '__main__':
    main()
