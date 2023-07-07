# JumpyCat

Just a cat jumping around collecting stuff and staying out of trouble.

A useful learning exercise, which is also why a lot of stuff is still wonky.

## Features

You play as a cat. No other features needed, really, but I still added a few.

Run around, jump between platforms, avoid touching enemies, collect coins to open the door to the next level.

Keep an eye on the minimap to see the location of coins and the rune power up that unlocks double jumping.

Get achievements by falling from a great height and collecting all the coins in the level.

## Technical stuff

An engine class runs everything with a FSM handling the menu, playing, quitting. It's pretty broken for now, a lot of initialization happens outside the class.

A base game object class based on a few interfaces and components then gets derived to create walls, powerups, enemies and the player character.

Component classes for graphics, collisions.

Observer pattern used for playing sounds, in-game triggers, in-game message system and achievements.

Control is handled by collecting a vector of inputs then sending a vector of commands to the current player state for processing.

FSMs manage game state and player and enemy behavior.

HUD (health bar, high score), minimap (rudimentary, basically the whole scene rendered in a smaller screen area), camera scrolling.

Jumping has a bit of hang time and coyote time to improve the general feel and stops as soon as you bonk your head on a ceiling.

Dev mode feature flags for displaying object bounding boxes, sprite bounding boxes, state transitions, collected input.

Fixed step physics update (60 Hz) so stuff doesn't go through walls by accident during a frame rate drop.

Almost proper animations. Each state (character, enemies) has a different loop assembled from a sprite sheet, but I didn't bother properly aligning everything. Power ups use a sin function to smooth animation and look more interactive.