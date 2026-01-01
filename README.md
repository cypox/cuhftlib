# cuhftlib
Cypox' cuda HFT library

Library containing various cuda-accelerated math functions used for HFT strategies


1. Simulator
Simulates a world econoy. It has multiple exchanges, each trades different symbols and product types (deriviates) and processes orders coming from brokers.

Exchange:
* Name
* List of Symbols
* List of products
* List of up to date order books

Broker:
* List of exchanges
* fee structure
* api for external actors to submit orders

Actor:
* list of symbols of interest
* internal actors are simlated within the simulator (simulates other traders/actors and OTC transactions)
* external actors use apis to interact with the economy
* strategy
** buy only (consumer)
** sell only (producer)
** market maker
** arbitrage
** random trader
** buy and hold
** etc

2. Library
Create a list of functions that are used to interact with the simulator and live-test different strategies.
Library implements a client and, either submit orders to a broker or directly to an exchange via a simulator api.
Passing by a broker incur additional fees, submitting directly to a broker bypass the broker and simulate in-premise setup.

