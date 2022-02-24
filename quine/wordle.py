
'''
Instructions:
Use the Run/Stop button in the top right to start/stop/restart the program.
The information given after a guess is of the following form:
current_pattern previous_guesses non_occurring_letters remaining_letters_by_frequency number_of_remaining_valid_words
'''

import os
import random
from collections import defaultdict as dd

def guess_fits_previous_guesses(past_guess_state, guess, random_word, none_set):
    letter_count_guess = dd(int)
    letter_count_random_word = dd(int)
    for i in range(len(random_word)):
        letter_count_guess[guess[i]] += 1
        letter_count_random_word[random_word[i]] += 1
    # Check if there letters in the guess that we already know can't be guessed
    # from previous information
    if any(
        x in none_set and letter_count_guess[x] > letter_count_random_word[x]
        for x in guess
    ):
        return False
    # Check if a previous guess gave a correctly placed letter that the guess isn't using
    # in that place
    if any(
        i in past_guess_state[random_word[i]] and guess[i] != random_word[i]
        for i in range(len(random_word))
    ):
        return False
    # Check if a previous guess gave an incorrectly placed letter and the guess is using
    # the letter in that incorrect place
    if any(
        guess[i] in past_guess_state and i in past_guess_state[guess[i]] 
            and guess[i] != random_word[i] 
        for i in range(len(random_word))
    ):
        return False
    # Check if a previous guess gave an incorrectly placed letter that the guess isn't using
    # at all    
    if any(
        len(past_guess_state[letter]) > 0 and letter not in guess 
        for letter in past_guess_state
        ):
        return False
    return True

def update_from_guess(guess, random_word, past_guess_state, none_set, all_letters):
    for i in range(len(guess)):
        if guess[i] in past_guess_state:
            past_guess_state[guess[i]].add(i)
    letter_count_guess = dd(int)
    letter_count_random_word = dd(int)
    for i in range(len(random_word)):
        letter_count_guess[guess[i]] += 1
        letter_count_random_word[random_word[i]] += 1
    for letter in letter_count_guess:
        if letter_count_guess[letter] > letter_count_random_word[letter] and letter.isalpha():
            none_set.add(letter)
            if letter in all_letters:
                all_letters.remove(letter)

def print_result(guess, random_word, past_guess_state, none_set, all_letters, words):
    result_to_show = []
    guess_list = list(guess)
    random_word_list = list(random_word)
    for i in range(len(guess)):
        if guess[i] == random_word[i]:
            result_to_show.append(guess[i])
            guess_list[i] = None
            random_word_list[i] = None
        else:
            result_to_show.append(".")
    for i in range(len(guess)):
        if guess_list[i] != None and guess_list[i] in random_word_list:
            result_to_show[i] = guess_list[i].lower()
            random_word_list[random_word_list.index(guess_list[i])] = None

    past_guess_state_str = [
        letter + ": " + ",".join([str(x + 1) 
        for x in past_guess_state[letter]]) 
        for letter in past_guess_state 
        if len(past_guess_state[letter]) > 0 and letter not in none_set
    ]
    print(
        "".join(result_to_show) + " \t" + 
        " ".join(past_guess_state_str) + " \t" + 
        "".join(sorted([x for x in none_set])) + " \t" + 
        "".join(all_letters) + " \t" + 
        str(len(words)) + "\n"
    )


all_letters = list("ETAOINSHRDLUCWMFYGPBVKXJQZ")

scrabble_words_file = open('scrabble_dictionary.txt')
common_words_file = open('words_5k.dat')

scrabble_words = scrabble_words_file.readlines()
common_words = common_words_file.readlines()
print("Select a length for the target word: ", end='')
word_len = int(input())
scrabble_words = [
    x.strip().upper() 
    for x in scrabble_words 
    if len(x.strip()) == word_len and x.strip().isalpha()
]
common_words = [
    x.strip().upper() 
    for x in common_words 
    if len(x.strip()) == word_len and x.strip().isalpha()
]
scrabble_words_set = set(scrabble_words)
common_scrabble_words = [x for x in common_words if x in scrabble_words_set]
# Pick the word to guess only from options that are both scrabble words and common words
random_word = random.choice(common_scrabble_words)
words = list(set(scrabble_words + common_words))
words_orig = set([x for x in words])
# Uncomment if you want to enforce max guesses
# print("Select a number of guesses: ", end='')
# max_guesses = int(input())

max_guesses = 1000
guess = ""
past_guess_state = {}
for x in random_word:
    past_guess_state[x] = set()
none_set = set()
print("Type your guess (or ? to get a hint)")
for _ in range(max_guesses):
    guess = input().strip().upper()
    while guess.upper() not in words or guess == '?':
        if guess == '?':
            forced_guess = [
                random_word[i] if i in past_guess_state[random_word[i]] else "*" 
                for i in range(word_len)
            ]
            if "".join(forced_guess) == random_word:
                print("No more hints are possible.")
            else:
                break
        elif len(guess) != word_len:
            print("Incorrect word length, try again")
        elif guess not in words_orig:
            print("Unrecognized word, try again")
        else:
            print("Invalid guess, try again")
        guess = input().strip().upper()
    if guess == random_word:
        break
    if guess == "?":
        guess = [
            random_word[i] if i in past_guess_state[random_word[i]] else "*" 
            for i in range(word_len)
        ]
        while True:
            # Pick a random letter to reveal
            i = random.choice(range(word_len))
            if i not in past_guess_state[random_word[i]]:
                guess = [
                    random_word[i] if i in past_guess_state[random_word[i]] else "*" 
                    for i in range(word_len)
                ]
                guess[i] = random_word[i]
                update_from_guess("".join(guess), random_word, past_guess_state, none_set, all_letters)
                break
    else:
        update_from_guess(guess, random_word, past_guess_state, none_set, all_letters)
    words = [
        x for x in words 
        if guess_fits_previous_guesses(past_guess_state, x, random_word, none_set)
    ]
    print_result(guess, random_word, past_guess_state, none_set, all_letters, words)
if guess == random_word:
    print("Congratulations! You won!")
else:
    print("The word was " + random_word + ". Better luck next time :(")

