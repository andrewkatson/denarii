
"""
Class that emulates a denarii_client for testing.
"""

import os
import pathlib
import pickle as pkl
import random
import requests
import string
import threading
import time

from constants import * 

word_site = "https://www.mit.edu/~ecprice/wordlist.10000"

response = requests.get(word_site)
WORDS = response.content.splitlines()

def generate_phrase(num_words):
    list_of_words = random.choices(WORDS, k=num_words)
    list_of_strings = [word.decode('utf8') for word in list_of_words]
    return ' '.join(list_of_strings)


def generate_address(num_letters):
    list_of_letters = random.choices(string.ascii_letters, k=num_letters)
    return ''.join(list_of_letters)

def store_wallet(wallet):
    path = pathlib.Path(f'{TEST_WALLET_PATH}/{wallet.name}.wallet')
    with open(path, "wb") as output_file:
        pkl.dump(wallet, output_file)

def load_wallet(wallet_path):
    wallet = None
    with open(wallet_path, "rb") as input_file:
        wallet = pkl.load(input_file)
    
    return wallet

def load_all_wallets():
    wallets = {}
    for path in os.listdir(TEST_WALLET_PATH):

        full_path = os.path.join(TEST_WALLET_PATH, path)

        if os.path.isfile(full_path):
            if '.wallet' in path:
                split = path.split('.wallet')
                wallet_name = split[0]
                wallets[wallet_name] = load_wallet(full_path)

    return wallets


class TestingWallet:

    def __init__(self, name, password, seed='', sub_addresses=None):
        self.name = name
        self.password = password
        self.seed = seed
        self.address = generate_address(15)
        # We make the balance 2 so that we can transfer some money.
        self.balance = 2.0 / 0.000000000001
        if sub_addresses is None: 
            sub_addresses = []
        self.sub_addresses = sub_addresses
        
        self.mining_thread = None 
        self.keep_mining = False

        self.opened_wallet = None

class DenariiClient:
    def __init__(self, wallets=None):
        if wallets is None:
            wallets = {}
        self.wallets = wallets

        for name, wallet in load_all_wallets().items():
            self.wallets[name] = wallet

    def create_wallet(self, wallet):
        if wallet.name in self.wallets:
            return False

        self.wallets[wallet.name] = TestingWallet(wallet.name, wallet.password, seed=generate_phrase(4))

        store_wallet(self.wallets[wallet.name])

        self.opened_wallet = self.wallets[wallet.name]
        return True

    def restore_wallet(self, wallet):
        if wallet.name in self.wallets:
            existing_wallet = self.wallets.get(wallet.name)
            if wallet.password == existing_wallet.password:
                if wallet.phrase == existing_wallet.seed:
                    store_wallet(existing_wallet)
                    self.opened_wallet = existing_wallet
                    return True
        return False

    def get_address(self, wallet):

        if wallet.name in self.wallets:
            wallet.address = self.wallets.get(wallet.name).address
            return True

        wallet.address = generate_address(15)
        existing_wallet = self.wallets.get(wallet.name)
        existing_wallet.address = wallet.address
        return True

    def transfer_money(self, amount, sender, receiver):
        if sender.name in self.wallets:
            existing_wallet = self.wallets.get(sender.name)
            if existing_wallet.balance >= amount:
                existing_wallet.balance -= amount
                store_wallet(existing_wallet)
                return True
            return False
        return False

    def get_balance_of_wallet(self, wallet):
        if wallet.name in self.wallets:
            return self.wallets.get(wallet.name).balance
        return 0.0

    def set_current_wallet(self, wallet):
        if wallet.name in self.wallets:
            existing_wallet = self.wallets.get(wallet.name)
            if existing_wallet.password == wallet.password:
                self.opened_wallet = existing_wallet
                store_wallet(self.opened_wallet)
                return True
            return False
        return False

    def query_seed(self, wallet):
        if wallet.name in self.wallets:
            wallet.phrase = self.wallets.get(wallet.name).seed
            return True
        return False
    
    def create_no_label_address(self, wallet):
        if wallet.name in self.wallets:
            new_sub_address = generate_address(15)
            wallet.sub_addresses.append(new_sub_address)

            existing_wallet = self.wallets[wallet.name]
            existing_wallet.sub_addresses.append(new_sub_address)

            store_wallet(existing_wallet)
            return True
        
        return False
    
    def start_mining(self, do_background_mining, ignore_battery, threads):
        self.keep_mining = True
        self.mining_thread = threading.Thread(target=self.mine)
        self.mining_thread.start()
        return True

    def stop_mining(self):
        self.keep_mining = False
        store_wallet(self.opened_wallet)
        self.mining_thread.join()
        return True

    def mine(self):

        while self.keep_mining:
            time.sleep(1)

            self.opened_wallet.balance += random.uniform(1.0, 100.0) / 0.000000000001

            store_wallet(self.opened_wallet)


        