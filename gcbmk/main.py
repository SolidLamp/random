#!/usr/bin/env python3

saveSizes = {
    "18-Wheeler American Pro Trucker": 3,
    "2002 FIFA World Cup": 49,
    "4x4 Evo 2": 3,
    "Ace Golf": 10,
    "Aggressive Inline": 57,
    "Animal Crossing": 62,
    "ATV Quad Power Racing 2": 9,
    "Backyard Football": 6,
    "Baldur's Gate: Dark Alliance": 30,
    "Batman Vengeance": 2,
    "Beach Spikers": 3,
    "Big Air Freekstyle": 5,
    "Black  & Bruised": 1,
    "Blood Omen 2": 1,
    "BloodRayne": 1,
    "Bloody Roar: Primal Fury": 3,
    "BMX XXX": 18,
    "Bomberman Generations": 3,
    "Burnout": 4,
    "Capcom Vs. SNK 2: Mark of the Millennium 2001": 9,
    "Casper: Spirit Dimensions": 3,
    "Cel Damage": 2,
    "Crash Bandicoot: The Wrath of Cortex": 2,
    "Crash Tag Team Racing": 2,
    "Crazi Taxi": 8,
    "Cubivore": 13,
    "Dark Summit": 4,
    "Darkened Skye": 6,
    "Dave Mirra Freestyle BMX 2": 28,
    "Dead to Rights": 10,
    "Defender": 1,
    "Die Hard: Vendetta": 6,
    "Disney Sports Football": 41,
    "Disney Sports Skateboarding": 7,
    "Disney Sports Soccer": 15,
    "Disney's Magical Mirror Starring Mickey Mouse": 3,
    "Disney's PK: Out of the Shadows": 5,
    "Donald Duck: Goin' Quackers": 6,
    "Dr. Muto": 3,
    "Dragon's Lair 3D": 19,
    "Driven": 3,
    "Egg Mania: Eggstreme Madness": 4,
    "ESPN International Winter Sports 2002": 3,
    "ESPN MLS Extra Time 2002": 54,
    "Eternal Darkness": 15,
    "Evolution Skateboarding": 27,
    "F1 2002": 5,
    "FIFA Soccer 2002 Major League Soccer": 29,
    "FIFA Soccer 2003": 54,
    "Freekstyle": 8,
    "Frogger Beyond": 3,
    "Gauntlet: Dark Legacy": 8,
    "Godzilla: Destroy All Monsters Melee": 4,
    "Harry Potter and the Chamber of Secrets": 5,
    "Home Run King": 34,
    "Hot Wheels Velocity X": 1,
    "Hunter: The Reckoning": 1,
    "James Bond 007: Agent Under Fire": 3,
    "James Bond 007: Nightfire": 2,
    "Jeremy McGrath Supercross World": 9,
    "Kelly Slater's Pro Surfer": 14,
    "Knockout Kings 2003": 5,
    "Legend of Zelda: Collector's Edition": 36,
    "Legend of Zelda: Ocarina of Time Master Quest": 15,
    "Legend of Zelda: The Wind Waker": 0,
    "Legends of Wrestling": 5,
    "Legends of Wrestling II": 15,
    "Lord of the Rings: The Two Towers": 4,
    "Lost Kingdoms": 8,
    "Luigi's Mansion": 3,
    "Mario Kart: Double Dash": 3,
    "Mario Party 4": 2,
    "Mary-Kate and Ashley Sweet 16: Licensed to Drive": 4,
    "Mat Hoffman's Pro BMX 2": 18,
    "Medal of Honor: Frontline": 4,
    "Metroid Prime": 2,
    "Minority Report: Everybody Runs": 4,
    "MLB Slugfest 20-03": 11,
    "Monsters, Inc.": 4,
    "Mortal Kombat: Deadly Alliance": 1,
    "MX Superfly": 8,
    "Mystic Heroes": 6,
    "Namco Museum": 2,
    "NASCAR: Dirt to Daytona": 28,
    "NASCAR Thunder 2003": 35,
    "NBA 2K2": 50,
    "NBA 2K3": 50,
    "NBA Courtside 2002": 7,
    "NBA Live 2003": 110,
    "NBA Street": 10,
    "NCAA College Basketball 2K3": 50,
    "NCAA College Football 2K3": 51,
    "NCAA Football 2003": 224,
    "Need For Speed: Hot Pursuit 2": 7,
    "NFL 2K3": 56,
    "NFL Blitz 20-02": 17,
    "NFL Blitz 20-03": 17,
    "NHL 2003": 30,
    "NHL 2K3": 125,
    "NHL Hitz 20-02": 8,
    "NHL Hitz 20-03": 49,
    "Pikmin": 19,
    "Pokémon Colosseum": 48,
    "Resident Evil": 8,
    "Resident Evil Zero": 9,
    "Robotech: Battlecry": 1,
    "Shrek 2": 2,
    "Skies of Arcadia Legends": 3,
    "Sonic Adventure 2 Battle": 11,
    "Sonic Mega Collection": 2,
    "SSX Tricky": 5,
    "Star Wars: Bounty Hunter": 2,
    "Star Wars Rogue Squadron II: Rogue Leader": 3,
    "Star Was: The Clone Wars": 3,
    "Super Mario Sunshine": 7,
    "Super Monkey Ball": 6,
    "Super Smash Brothers Melee": 11,
    "Tak and the Power of Juju": 38,
    "Turok: Evolution": 2,
    "Wave Race: Blue Storm": 12,
    "XG3 Extreme G Racing": 6,
    "Turok: Evolution": 1,
    "WarioWare, Inc.: Mega Party Game$!": 4,
}

games = {
    "Pokémon Colosseum": 48,
    "Luigi's Mansion": 3,
    "Mario Kart: Double Dash": 3,
    "Mario Party 4": 2,
    "Animal Crossing": 62,
}

games = saveSizes.copy()

sortedGames = dict(
    sorted(games.items(), key=lambda item: item[1], reverse=True)
)


def nextItem(card: dict, cardSize: int, games: dict, currentItems: list) -> str:
    #print(f"Current Items: {currentItems}")
    usedBlocks = 0
    for item in currentItems:
        usedBlocks += saveSizes[item]
    remainingBlocks = cardSize - usedBlocks
    #print(f"Remaining Blocks: {remainingBlocks}")
    if remainingBlocks == 0:
        return None
    possibleGames = {k: v for k, v in games.items() if v <= remainingBlocks}
    #print(f"Possible Games: {possibleGames}")
    largestGame = next(iter(possibleGames.keys()), None)
    #print(f"Largest Game: {largestGame}")
    return largestGame

def createCard(games: dict, cardSize: int) -> list:
    card = {}
    currentItems = games.keys()
    currentItems = []
    next_item = nextItem(card, cardSize, games, currentItems)
    while next_item != None:
        currentItems.append(next_item)
        games.pop(next_item)
        next_item = nextItem(card, cardSize, games, currentItems)
    #print(currentItems)
    return currentItems

def pack_bin(games: dict, cardSize: int) -> dict:
    remaining_games = games.copy()
    cards = {}
    i = 0
    new_card = createCard(remaining_games, cardSize)
    while remaining_games and new_card:
        i += 1
        cards.update({i: new_card})
        new_card = createCard(remaining_games, cardSize)
    return cards

def print_bin(bins: dict):
    for bin in bins:
        print(bin, '\n', '---')
        for item in bins[bin]:
            print(item, saveSizes[item])
        print('\n')



bins = pack_bin(sortedGames, 59)
print_bin(bins)
