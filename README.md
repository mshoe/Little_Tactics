# Little-Tactics
info-link: https://mshoe.github.io/LittleTactics

video: https://www.youtube.com/watch?v=JMr3EyeEGjQ

Little Tactics
A game by mshoe
v0.1, June 2016
1. Little Tactics is about manipulating your opponent into a bad position. It is made using C++ and OpenGL.
2. Turns alternate, with black going first. Each turn, you can move a piece and attack a piece (if there are any enemy pieces adjacent to your pieces)
3. Each player controls 6 pieces on an 8x8 board. Each piece has 2 HP (hit points), 1 ATK (attack damage), and 2 MOV (movement radius).
4. Pieces in a chain of two have 3 MOV. Pieces in a chain of three have 2 ATK and 3 MOV. Pieces in chains of length n > 3 have 2 ATK and n MOV.
5. Attacking a piece bumps it in the direction of the attack. This applies to lines of pieces as well. If the edge of the board is in the way, a piece will not be bumped.
6. After a piece is attacked, any ally pieces connected to the attacked piece (after it is possibly bumped) in a chain are also damaged.
tl;dr: your pieces gain ATK and MOV bonuses by grouping together, but damage dealt to any piece in a chain affects all pieces in the chain

Little Tactics was my first OpenGL application. On top of being my first real application of linear algebra, I also used many concepts from computer science such as data structures and algorithms to solve some of the more tricky game mechanics. 
No drawing was done, all graphics are written with code.
